#pragma once

#include <string>

using namespace std;

// TODO: extract some methods into Assembler class
class FileReader {
 public:
  int process(string fname);
  int read_file(string fname);
  void out_src();

 protected:
  void handle_char(const char& c);
  string trim_right(string);
  void merge_code_with_labels();
  void pass1();

 private:
  map<int, string> lines_ {};
  string line_ {};
  bool skip_space_ {true};
  bool skip_comment_ {false};
  int line_num_ {1};
};
