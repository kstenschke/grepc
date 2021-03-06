/* grepc
 * Copyright 2021 Kay Stenschke <info@stenschke.com>
 *
 * License GPLv3+: GNU GPL version 3 or later
 * <http://gnu.org/licenses/gpl.html>.
 *
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 *
 * Written by Kay Stenschke, see <https://github.com/kstenschke/grepc>.
 */

#include <sys/stat.h>
#include <algorithm>
#include <cstring>
#include <iostream>
#include <sstream>
#include <tuple>
#include <vector>

void ParseArguments(int argc,
                    char *const *argv,
                    std::string *reg_ex,
                    std::string *path,
                    bool *verbose,
                    uint32_t *min_occurrences,
                    bool *print_version);

void PrintVersionAndExit();

uint32_t NumPlaces(uint32_t n);

std::string GetAmountFilesInPath(const std::string& path);

uint32_t CountSubString(const std::string& str, const std::string& sub);

std::string GetCliCommandOutput(const char *command);

std::vector<std::string> Split(std::string const &str, char delimiter);

std::string RepeatSpaces(uint32_t amount);

bool SortDesc(const std::tuple<uint32_t, std::string>& a,
              const std::tuple<uint32_t, std::string>& b);

void PrintSummary(const std::vector<std::string> &lines_of_strings_in_files,
                  const std::string &amount_files_in_path,
                  uint32_t amount_strings);

bool IsDir(const std::string& path);

void EnsureRecursionIfPathIsDirectory(std::string *path, bool *path_is_dir);

int main(int argc, char **argv) {
  std::string pattern;
  std::string path;
  bool verbose = false;
  bool print_version = false;
  uint32_t min_occurrences = 0;

  if (argc > 1)
    ParseArguments(argc, argv, &pattern, &path, &verbose, &min_occurrences,
                   &print_version);

  if (print_version) PrintVersionAndExit();

  if (pattern.empty()) {
    std::cerr << "No pattern given.\n";
    exit(1);
  }

  bool path_is_dir = false;
  EnsureRecursionIfPathIsDirectory(&path, &path_is_dir);

  std::string command = "grep -Eo '" + pattern + "' " + path;

  if (path_is_dir) command += " -r";

  auto strings_in_files = GetCliCommandOutput(command.c_str());
  auto lines_of_strings_in_files = Split(strings_in_files, '\n');
  std::string found_strings;

  for (auto const &line : lines_of_strings_in_files) {
    std::string found_string = line;

    if (path_is_dir) {
      auto offset_colon = line.find(':');
      if (offset_colon != std::string::npos)
        found_string = line.substr(offset_colon + 1);
    }

    if (found_string.rfind("Binary file ", 0) == 0) continue;

    if (found_strings.find(found_string + "\n") == std::string::npos) {
      found_strings += found_string + "\n";
    }
  }

  const std::string &amount_files_in_path = GetAmountFilesInPath(path);

  std::vector<std::tuple<uint32_t, std::string>> amount_per_string;
  auto strings = Split(found_strings, '\n');
  uint32_t max_occurrences = 0;

  for (std::string const& string : strings) {
    uint32_t amount_occurrences =
        CountSubString(strings_in_files, string + "\n");

    if (amount_occurrences > min_occurrences) {
      amount_per_string.emplace_back(std::make_tuple(amount_occurrences,
                                                     string));

      if (amount_occurrences > max_occurrences)
        max_occurrences = amount_occurrences;
    }
  }

  std::sort(amount_per_string.begin(), amount_per_string.end(), SortDesc);

  if (verbose)
    PrintSummary(lines_of_strings_in_files,
        amount_files_in_path,
        amount_per_string.size());

  uint32_t max_places = NumPlaces(max_occurrences);

  for (std::tuple<uint32_t, std::string> const &tuple_amount_string :
      amount_per_string) {
    const auto& str = std::get<1>(tuple_amount_string);
    uint32_t amount = std::get<0>(tuple_amount_string);

    std::cout << amount
      << RepeatSpaces(max_places - NumPlaces(amount))
      << " " << str << "\n";
  }

  return 0;
}

void EnsureRecursionIfPathIsDirectory(std::string *path, bool *path_is_dir) {
  if ((*path).empty()) {
    *path = "./*";
    *path_is_dir = true;

    return;
  }

  if (IsDir(*path)) {
    auto path_len = (*path).length();

    if ((*path)[path_len - 1] != '*')
      *path += (*path)[path_len - 1] == '/' ? "*" : "/*";

    *path_is_dir = true;
  }
}

void ParseArguments(int argc,
                    char *const *argv,
                    std::string *reg_ex,
                    std::string *path,
                    bool *verbose,
                    uint32_t *min_occurrences,
                    bool *print_version) {
  bool reg_ex_set = false;

  std::string arg_str = argv[1];

  if (argv[1][0] == '-') {
    if (strcmp(argv[1], "-v") != 0
        && strcmp(argv[1], "--verbose") != 0
        && strcmp(argv[1], "-V") != 0
        && strcmp(argv[1], "--version") != 0
        && arg_str.rfind("-m=", 0) != 0
        && arg_str.rfind("--min=", 0) != 0) {
      std::cerr << "Unknown option: " << argv[1] << "\n";
      exit(1);
    }
  }

  for (uint64_t i = 1; i < argc; ++i) {
    if (strcmp(argv[i], "-v") == 0 || strcmp(argv[i], "--verbose") == 0) {
      *verbose = true;
      continue;
    }

    if (strcmp(argv[i], "-V") == 0 || strcmp(argv[i], "--version") == 0) {
      *print_version = true;
      break;
    }

    arg_str = argv[i];

    if (arg_str.rfind("-m=", 0) == 0) {
      *min_occurrences = std::stoi(arg_str.substr(3));
      continue;
    }

    if (arg_str.rfind("--min=", 0) == 0) {
      *min_occurrences = std::stoi(arg_str.substr(6));
      continue;
    }

    if (!reg_ex_set) {
      *reg_ex = argv[i];
      reg_ex_set = true;
    } else {
      *path = argv[i];
    }
  }
}

void PrintVersionAndExit() {
  std::cout <<
  "grepc 0.0.2\n"
  "License GPLv3+: GNU GPL version 3 or later "
  "<http://gnu.org/licenses/gpl.html>.\n"
  "This is free software: you are free to change and redistribute it.\n"
  "There is NO WARRANTY, to the extent permitted by law.\n"
  "\n"
  "Written by Kay Stenschke, see <https://github.com/kstenschke/grepc>.\n";

  exit(0);
}

void PrintSummary(const std::vector<std::string> &lines_of_strings_in_files,
                  const std::string &amount_files_in_path,
                  uint32_t amount_strings) {
  std::cout << "\nFound " + std::to_string(lines_of_strings_in_files.size())
      + " matches in " << amount_files_in_path << " files.\n";
  std::cout << "There are " + std::to_string(amount_strings)
      + " different matching strings:\n" << std::endl;
}

uint32_t NumPlaces(uint32_t n) {
  int count = 0;

  while (n != 0) {
    n /= 10;
    ++count;
  }

  return count;
}

std::string GetAmountFilesInPath(const std::string& path) {
  std::string command = "ls -1q " + path + " | wc -l";

  auto amount = GetCliCommandOutput(command.c_str());

  return amount.substr(0, amount.length() - 1);
}

uint32_t CountSubString(const std::string& str, const std::string& sub) {
  auto sub_len = sub.length();

  if (sub_len == 0) return 0;

  int count = 0;

  for (size_t offset = str.find(sub); offset != std::string::npos;
       offset = str.find(sub, offset + sub_len))
    ++count;

  return static_cast<uint32_t>(count);
}

std::string GetCliCommandOutput(const char *command) {
  FILE *fp;
  char path[1035];

  fp = popen(command, "r");

  if (fp ==nullptr) return "Failed to run command";

  std::string result;

  while (fgets(path, sizeof(path), fp) !=nullptr) result += path;

  pclose(fp);

  return result;
}

std::vector<std::string> Split(std::string const &str, char delimiter) {
  std::vector<std::string> result;
  std::istringstream iss(str);

  for (std::string token; std::getline(iss, token, delimiter);)
    result.push_back(std::move(token));

  return result;
}

std::string RepeatSpaces(uint32_t amount) {
  std::string out;

  for (uint32_t i = 0; i < amount; ++i) out += " ";

  return out;
}

bool SortDesc(const std::tuple<uint32_t, std::string>& a,
              const std::tuple<uint32_t, std::string>& b) {
  auto amount_a = std::get<0>(a);
  auto amount_b = std::get<0>(b);

  return amount_a != amount_b
    ? amount_a > amount_b  // amount descending
    : std::get<1>(a) < std::get<1>(b);  // string ascending
}

// TODO(kay): replace w/ std::filesystem::is_directory() when switching to c++17
bool IsDir(const std::string& path) {
  struct stat buffer;

  stat(path.c_str(), &buffer);

  return S_ISDIR(buffer.st_mode);
}
