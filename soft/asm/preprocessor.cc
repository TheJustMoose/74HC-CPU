#include <algorithm>
#include <iostream>

#include "preprocessor.h"
#include "trim.h"

using namespace std;

bool Preprocessor::Preprocess(map<int, string> *lines) {
  if (!lines) {
    cout << "lines is NULL" << endl;
    return false;
  }

  // remove spaces
  map<int, string>::iterator it;
  for (it = lines->begin(); it != lines->end(); it++)
    it->second = StripLine(it->second);

  // extract defines to another map
  for (it = lines->begin(); it != lines->end();) {
    if (it->second.find(".def") == 0) {
      defines_[it->first] = it->second;
      it = lines->erase(it);
    } else
      it++;
  }

  return true;
}

string Preprocessor::StripLine(string line) {
  string res;

  bool skip_space {true};
  for (size_t i = 0; i < line.size(); i++) {
    if (line[i] == ';')
      break;

    if (IsSpace(line[i])) {
      if (skip_space)
        continue;
      else
        skip_space = true;
    }
    else
      skip_space = false;

    res += line[i];
  }

  if (res.size() && IsSpace(*res.rbegin()))
    res.resize(res.size() - 1);

  return res;
}

bool Preprocessor::IsSpace(char ch) {
  return ch == ' ' || ch == '\t' || ch == '\n' || ch == '\r';
}

vector<string> Preprocessor::Split(string line) {
  vector<string> res;

  string str;
  for (char ch : line)
    if (IsSpace(ch) || ch == ',') {
      if (str.size())
        res.push_back(str);
      str = "";
    } else {
      str += ch;
    }

  if (str.size())
    res.push_back(str);

  return res;
}
