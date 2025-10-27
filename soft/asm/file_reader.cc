#include <algorithm>
#include <fstream>
#include <iostream>

#include "file_reader.h"
#include "str_util.h"

using namespace std;

int FileReader::read_file(string fname, map<int, string> *result) {
  if (!result) {
    cout << "Error: no output array";
    return 1;
  }

  ifstream f;
  f.open(fname, ios::binary);
  if (!f) {
    cout << "Error. Can't open file " << fname << endl;
    return 1;
  }

  cout << "Processing " << fname << "..." << endl;
  for_each(istreambuf_iterator<char>(f),
           istreambuf_iterator<char>(),
           [this](const char& c) { handle_char(c); });

  handle_char('\n');  // probably there is no EOL on the last line of code
  f.close();

  *result = std::move(lines_);

  return 0;
}

void FileReader::handle_char(const char& c) {
  if (c == '\r')
    return;

  if (c == '\n') {
    if (!line_.empty())
      lines_[line_num_] = std::move(line_);
    line_ = "";  // not sure about line state after move
    line_num_++;
    return;
  }

  line_ += c;
}
