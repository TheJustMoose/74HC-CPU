#pragma once

#include <map>
#include <string>

class FileReader {
 public:
  FileReader() = default;

  int read_file(std::string fname, std::map<int, std::string> *result);

  void handle_char(const char& c);

 private:
  std::string line_ {};
  bool skip_space_ {true};
  bool skip_comment_ {false};
  int line_num_ {1};
  std::map<int, std::string> lines_ {};
};
