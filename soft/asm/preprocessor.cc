#include <iostream>

#include "preprocessor.h"
#include "trim.h"

using namespace std;

bool Preprocessor::Preprocess(map<int, string> *lines) {
  if (!lines) {
    cout << "lines is NULL" << endl;
    return false;
  }

  map<int, string>::iterator it;
  for (it = lines->begin(); it != lines->end(); it++)
    it->second = StripLine(it->second);

  return false;
}

string Preprocessor::StripLine(string line) {
  string res;

  bool skip_space {true};
  for (size_t i = 0; i < line.size(); i++) {
    if (line[i] == ';')
      break;

    if (line[i] == ' ') {
      if (skip_space)
        continue;
      else
        skip_space = true;
    }
    else
      skip_space = false;

    res += line[i];
  }

  if (res.size() && *res.rbegin() == ' ')
    res.resize(res.size() - 1);

  return res;
}


/*
  if (c == ' ' && skip_space_)
    return;

  skip_space_ = false;

  if (c == '\n') {
    string t = trim_right(line_);
    if (!t.empty())
      lines_[line_num_] = std::move(t);
    line_ = "";  // not sure about line state after move
    skip_space_ = true;
    skip_comment_ = false;
    line_num_++;
    return;
  }

  if (c == ';')
    skip_comment_ = true;

  if (!skip_comment_)
    line_ += c;
*/
