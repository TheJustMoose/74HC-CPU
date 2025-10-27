#include <algorithm>
#include <iostream>

#include "preprocessor.h"
#include "str_util.h"

using namespace std;

string join(vector<string> v, char del) {
  string res {};
  for (size_t i = 0; i < v.size(); i++) {
    res += v[i];
    if (i < v.size() - 1)
      res += del;
  }
  return res;
}

string Define::Body() {
  return join(body_, ' ');
}

vector<string> Define::BodyParts() {
  return body_;
}

string Define::BodyWoParams() {
  return join(BodyPartsWoParam(), ' ');
}

vector<string> Define::BodyPartsWoParam() {
  if (!HasParams() || !IsValid())
    return BodyParts();

  vector<string>::iterator it = find(body_.begin(), body_.end(), ")");
  it++;  // the next word after ")"
  if (it == body_.end())
    return {};

  vector<string> res;
  copy(it, body_.end(), back_inserter(res));
  return res;
}

bool Define::HasParams() {
  return (body_.size() > 0) && (body_[0] == "(");
}

bool Define::IsValid() {
  if (!HasParams())
    return true;

  // Define with param should have next parts:
  // name ( param ) body parts
  // So minimum size is 3: ( param )
  // Name is stored in name_
  if (body_.size() < 3) {
    cout << "Define is too small. It should contain at least: name ( param )" << endl;
    return false;
  }

  if (body_[2] != ")") {  // no define name in body_
    cout << "Can't find closing parenthesis in: " << Body();
    return false;
  }

  return true;
}

string Define::ParamName() {
  if (!HasParams() || !IsValid())
    return {};

  return body_[1];
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
    if (parts.size() && parts[0] == ".def") {
      // remove define from source code
      it = lines->erase(it);
      AddDefineIntoMap(std::move(parts));
    }
    else
      it++;

  }

  cout << "DEFINE LIST:" << endl;
  map<string, Define>::iterator it2;
  for (it2 = defines_.begin(); it2 != defines_.end(); it2++)
    cout << it2->first << " == " << it2->second.Body() << endl;

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
    if (parts.empty())
      continue;
    if (parts[0] == ".str")
      continue;

    size_t colon_pos = parts[0].rfind(':');
    string labels {};
    if (colon_pos != string::npos) {
      labels = parts[0].substr(0, colon_pos + 1);  // +1 will convert pos to prefix length
      parts[0].erase(0, colon_pos + 1);
    }

    // process all parts of cmd for simple define
    for (string &p : parts) {
      map<string, Define>::iterator pit = defines_.find(p);
      if (pit == defines_.end()) {
        continue;
      }
      if (pit->second.HasParams()) {
        continue;
      }

      string np = pit->second.Body();
      cout << "replace: " << p << " <-- " << np << endl;
      p = np;
    }

    // process only first parts of cmd for define with param
    map<string, Define>::iterator pit = defines_.find(parts[0]);
    if (pit != defines_.end())
      if (pit->second.HasParams() && pit->second.IsValid() && parts.size() > 1) {
        vector<string> np = pit->second.BodyPartsWoParam();
        cout << "replace: " << join(parts) << " <-- " << join(np) << endl;
        string param = parts[1];
        parts = np;
        for (size_t i = 0; i < parts.size(); i++)
          if (parts[i] == pit->second.ParamName())
            parts[i] = param;
      }

    if (labels.size())  // return label back to string
      parts[0] = labels + parts[0];

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
