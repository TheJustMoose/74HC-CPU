#include <algorithm>
#include <iostream>

#include "preprocessor.h"
#include "trim.h"

using namespace std;

string join(vector<string> v, char del = '|') {
  string res {};
  for (size_t i = 0; i < v.size(); i++) {
    res += v[i];
    if (i < v.size() - 1)
      res += del;
  }
  return res;
}

string Define::body() {
  return join(body_, ' ');
}

bool Preprocessor::Preprocess(map<int, string> *lines) {
  if (!lines) {
    cout << "lines is NULL" << endl;
    return false;
  }

  // remove spaces & comments
  map<int, string>::iterator it;
  for (it = lines->begin(); it != lines->end(); it++)
    it->second = StripLine(it->second);

  // extract defines to another map
  for (it = lines->begin(); it != lines->end();) {
    vector<string> parts = Split(it->second);
    if (parts[0] != ".def") {  // TODO: change ne to eq
      it++;
      continue;
    }

    // remove define from source code
    it = lines->erase(it);
    AddDefineIntoMap(std::move(parts));
  }

  cout << "DEFINE LIST:" << endl;
  map<string, Define>::iterator it2;
  for (it2 = defines_.begin(); it2 != defines_.end(); it2++)
    cout << it2->first << " == " << it2->second.body() << endl;

  ApplyDefines(lines);

  return true;
}

void Preprocessor::AddDefineIntoMap(std::vector<std::string> parts) {
  if (parts.size() <= 2) {
    cout << ".def directive have to contain at least 3 items: .def from to" << endl;
    return;
  }

  // remove first word - .def directive
  parts.erase(parts.begin());

  // move define to map
  string def_name = parts[0];
  parts.erase(parts.begin());
  defines_[def_name] = Define(def_name, parts);
}

void Preprocessor::ApplyDefines(map<int, string> *lines) {
  map<int, string>::iterator it;
  for (it = lines->begin(); it != lines->end(); it++) {
    vector<string> parts = Split(it->second);
    cout << "process: " << join(parts) << endl;

    for (string &p : parts)
      if (defines_.find(p) != defines_.end()) {
        vector<string>& body = defines_[p].body_;
        p = body.size() ? body[0] : string{};
      }

    it->second = join(parts, ' ');
  }
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

bool Preprocessor::IsDelimeter(char ch) {
  return ch == ',' || ch == '(' || ch == ')' || ch == '+' || ch == '-';
}

vector<string> Preprocessor::Split(string line) {
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
