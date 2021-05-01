#include <iostream>
#include <vector>
#include <sstream>
#include <tuple>
#include <algorithm>

std::string GetAmountFilesInPath(const std::string& path);
uint32_t CountSubString(const std::string& str, const std::string& sub);
std::string GetShellResponse(const char *command);
std::vector<std::string> Split(std::string const &str, char delimiter);
std::string RepeatSpaces(uint8_t amount);
bool SortDesc(const std::tuple<uint32_t, std::string>& a,
              const std::tuple<uint32_t, std::string>& b);

int main() {
  std::string reg_ex = "\"[A-Za-z]{3,4}\"";
  std::string path = "/home/kay/CLionProjects/shellDo/*";

  std::string command = "grep -Eo '" + reg_ex + "' " + path + " -r";

  auto strings_in_files = GetShellResponse(command.c_str());
  auto lines_of_strings_in_files = Split(strings_in_files, '\n');

  uint32_t amount_files = 0;
  std::string file_paths;

  uint32_t amount_strings = 0;
  std::string found_strings;
  uint8_t len_max_string = 0;

  for (auto const &line : lines_of_strings_in_files) {
    auto offset_colon = line.find(':');

    if (offset_colon == std::string::npos) continue;

    std::string path_file = line.substr(0, offset_colon);
    std::string found_string = line.substr(offset_colon + 1);

    if (file_paths.find(path_file) == std::string::npos) {
      file_paths += path_file + "\n";
      ++amount_files;
    }

    if (found_strings.find(found_string) == std::string::npos) {
      found_strings += found_string + "\n";
      ++amount_strings;

      unsigned long len = found_string.length();

      if (len > len_max_string) len_max_string = len;
    }
  }

  const std::string &amount_files_in_path = GetAmountFilesInPath(path);

  std::cout << "\nFound " + std::to_string(lines_of_strings_in_files.size())
      + " matches in " << std::to_string(amount_files)
      << (amount_files_in_path == "1"
          ? "file\n"
          : " out of " + amount_files_in_path + " files.\n");

  std::cout << "There are " + std::to_string(amount_strings)
      + " different matching strings:\n" << std::endl;

  std::vector<std::tuple<uint32_t, std::string>> amount_per_string;
  auto strings = Split(found_strings, '\n');

  for (std::string const& string : strings) {
    uint32_t amount = CountSubString(strings_in_files, string);

    amount_per_string// NOLINT(performance-inefficient-vector-operation)
        .emplace_back(std::make_tuple(amount, string));
  }

  std::sort(amount_per_string.begin(), amount_per_string.end(), SortDesc);

  for (std::tuple<uint32_t, std::string> const &tuple_amount_string :
      amount_per_string) {
    auto str = std::get<1>(tuple_amount_string);
    auto amount = std::get<0>(tuple_amount_string);

    std::cout << str
              << RepeatSpaces(len_max_string - str.length())
              << " - " << std::to_string(amount)
              << " occurrences.\n";
  }

  return 0;
}

std::string GetAmountFilesInPath(const std::string& path) {
  std::string command = "ls -1q " + path + " | wc -l";

  auto amount = GetShellResponse(command.c_str());

  return amount.substr(0, amount.length() - 1);
}

uint32_t CountSubString(const std::string& str, const std::string& sub) {
  unsigned long sub_len = sub.length();

  if (sub_len == 0) return 0;

  int count = 0;

  for (size_t offset = str.find(sub); offset != std::string::npos;
       offset = str.find(sub, offset + sub_len))
    ++count;

  return count;
}

std::string GetShellResponse(const char *command) {
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
              const std::tuple<uint32_t, std::string>& b)
{
  return (std::get<0>(a) > std::get<0>(b));
}
