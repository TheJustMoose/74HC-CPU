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
    else if (*val.rbegin() == 'H')
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

bool IsSpace(char ch) {
  return ch == ' ' || ch == '\t' || ch == '\n' || ch == '\r';
}

bool IsDelimeter(char ch) {
  return ch == ',' || ch == '(' || ch == ')' || ch == '+' || ch == '-';
}

vector<string> Split(string line) {
  vector<string> res;

  string str;
  for (char ch : line) {
    bool delim = IsDelimeter(ch);
    if (IsSpace(ch) || delim) {
      if (str.size()) {
        res.push_back(str);
        str = "";
      }
      if (delim) {
        string dstr {ch};
        res.push_back(dstr);
      }
    } else {
      str += ch;
    }
  }

  if (str.size())
    res.push_back(str);

  return res;
}

vector<string> SplitToCmdParts(string text) {
  vector<string> parts = Split(ToUpper(text));
  // first part is operation name
  // and it has only one word
  string op_name;
  if (parts.size() >= 1)
    op_name = parts[0];

  size_t i = 1;

  string left;
  for (; i < parts.size() && parts[i] != ","; i++) {
    left += parts[i];  // R0 or XI or XI+5
  }

  if (parts[i] == ",")
    i++;

  string right;
  for (; i < parts.size(); i++)
    right += parts[i];  // R0 or XI or XI+5

  return { op_name, left, right };
}
