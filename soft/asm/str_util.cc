#include <algorithm>
#include <stdexcept>
#include <string>

#include "str_util.h"

using namespace std;

string ToUpper(string s) {
  std::transform(s.begin(), s.end(), s.begin(), ::toupper);
  return s;
}

// will remove leading spaces
// also remove more than one space in a row
string NormalizeLine(string s) {
  string res;
  bool skip_space {true};
  bool in_string {false};
  for (size_t i = 0; i < s.size(); i++) {
    if (s[i] == '"')
      in_string = !in_string;

    if (!in_string) {
      if (s[i] == ' ') {
        if (skip_space)
          continue;
        else
          skip_space = true;
      } else {
        skip_space = false;
      }
    }
    res += s[i];
  }

  return res;
}

string RemoveQuotes(string s) {
  if (s.size() <= 2)
    return s;
  return s.substr(1, s.size() - 2);
}

bool StrToInt(string val, int* pout, string* err) {
  int res = 0;
  try {
    if (val.find("0X") == 0)
      res = stoi(&val[2], nullptr, 16);
    else if (*val.rbegin() == 'h')
      res = stoi(&val[0], nullptr, 16);
    else if (val.find("0O") == 0)
      res = stoi(&val[2], nullptr, 8);
    else if (val.find("0B") == 0)
      res = stoi(&val[2], nullptr, 2);
    else {
      res = stoi(val, nullptr, 10);
    }
  } catch(std::invalid_argument& e) {
    if (err) {
      *err += e.what();
      *err += "\n";
      *err += "arg: ";
      *err += val;
    }
    return false;
  }

  if (pout)
    *pout = res;
  return true;
}
