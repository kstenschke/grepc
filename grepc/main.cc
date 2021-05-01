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
                    bool *print_version);

void PrintVersion();

uint32_t NumPlaces(uint32_t n);

std::string GetAmountFilesInPath(const std::string& path);

uint32_t CountSubString(const std::string& str, const std::string& sub);

std::string GetCliCommandOutput(const char *command);

std::vector<std::string> Split(std::string const &str, char delimiter);

std::string RepeatSpaces(uint8_t amount);

bool SortDesc(const std::tuple<uint32_t, std::string>& a,
              const std::tuple<uint32_t, std::string>& b);

void PrintSummary(const std::vector<std::string> &lines_of_strings_in_files,
                  uint32_t amount_files,
                  const std::string &amount_files_in_path,
                  uint32_t amount_strings);

int main(int argc, char **argv) {
  std::string pattern;
  std::string path;
  bool verbose = false;
  bool print_version = false;
  ParseArguments(argc, argv, &pattern, &path, &verbose, &print_version);

  if (print_version) {
    PrintVersion();
    exit(0);
  }

  if (pattern.empty()) {
    std::cerr << "No pattern given.\n";
    exit(0);
  }

  if (path.empty()) {
    path = argv[0];
    path = path.substr(0, path.length() - 5) + "*";
  }

  std::string command = "grep -Eo '" + pattern + "' " + path + " -r";

  auto strings_in_files = GetCliCommandOutput(command.c_str());
  auto lines_of_strings_in_files = Split(strings_in_files, '\n');

  uint32_t amount_files = 0;
  std::string file_paths;

  uint32_t amount_strings = 0;
  std::string found_strings;
  uint32_t max_occurrences = 0;

  for (auto const &line : lines_of_strings_in_files) {
    auto offset_colon = line.find(':');

    if (offset_colon == std::string::npos) continue;

    std::string path_file = line.substr(0, offset_colon);
    std::string found_string = line.substr(offset_colon + 1);

    if (verbose && file_paths.find(path_file) == std::string::npos) {
      file_paths += path_file + "\n";
      ++amount_files;
    }

    if (found_strings.find(found_string) == std::string::npos) {
      found_strings += found_string + "\n";
      ++amount_strings;
    }
  }

  const std::string &amount_files_in_path = GetAmountFilesInPath(path);

  std::vector<std::tuple<uint32_t, std::string>> amount_per_string;
  auto strings = Split(found_strings, '\n');

  for (std::string const& string : strings) {
    uint32_t amount = CountSubString(strings_in_files, string);
    amount_per_string.emplace_back(std::make_tuple(amount, string));

    if (amount > max_occurrences) max_occurrences = amount;
  }

  std::sort(amount_per_string.begin(), amount_per_string.end(), SortDesc);

  if (verbose)
    PrintSummary(lines_of_strings_in_files,
        amount_files,
        amount_files_in_path,
        amount_strings);

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

void ParseArguments(int argc,
                    char *const *argv,
                    std::string *reg_ex,
                    std::string *path,
                    bool *verbose,
                    bool *print_version) {
  bool reg_ex_set = false;

  for (uint64_t i = 1; i < argc; ++i) {
    if (strcmp(argv[i], "-v") == 0 || strcmp(argv[i], "--verbose") == 0) {
      *verbose = true;
      continue;
    }

    if (strcmp(argv[i], "-V") == 0 || strcmp(argv[i], "--version") == 0) {
      *print_version = true;
      break;
    }

    if (!reg_ex_set) {
      *reg_ex = argv[i];
      reg_ex_set = true;
    } else {
      *path = argv[i];
    }
  }
}

void PrintVersion() {
  std::cout <<
  "grepc 0.0.1\n"
  "License GPLv3+: GNU GPL version 3 or later "
  "<http://gnu.org/licenses/gpl.html>.\n"
  "This is free software: you are free to change and redistribute it.\n"
  "There is NO WARRANTY, to the extent permitted by law.\n"
  "\n"
  "Written by Kay Stenschke, see <https://github.com/kstenschke/grepc>.\n";
}

void PrintSummary(const std::vector<std::string> &lines_of_strings_in_files,
                  uint32_t amount_files,
                  const std::string &amount_files_in_path,
                  uint32_t amount_strings) {
  std::cout << "\nFound " + std::to_string(lines_of_strings_in_files.size())
      + " matches in " << std::to_string(amount_files)
          << (amount_files_in_path == "1"
                ? "file\n"
                : " out of " + amount_files_in_path + " files.\n");

  std::cout << "There are " + std::to_string(amount_strings)
      + " different matching strings:\n" << std::endl;
}

uint32_t NumPlaces(uint32_t n) {
  if (n < 0) return NumPlaces(n == 0 ? UINT32_MAX: -n);
  if (n < 10) return 1;
  return static_cast<int32_t>(1 + NumPlaces(n / 10));
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

std::string RepeatSpaces(uint8_t amount) {
  std::string out;

  for (uint8_t i = 0; i < amount; ++i) out += " ";

  return out;
}

bool SortDesc(const std::tuple<uint32_t, std::string>& a,
              const std::tuple<uint32_t, std::string>& b) {
  return std::get<0>(a) > std::get<0>(b);
}
