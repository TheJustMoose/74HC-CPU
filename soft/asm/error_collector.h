#pragma once

#include <iostream>
#include <map>
#include <string>

class ErrorCollector {
 public:
  void rep(std::string msg, int line) {
    errors_[line] = msg;
  }

  void clr(int line) {
    if (errors_.find(line) != errors_.end())
      errors_[line] = "";
  }

  std::map<int, std::string> get() {
    return errors_;
  }

  std::string get(int line) {
    if (errors_.find(line) != errors_.end())
      return errors_[line];
    else
      return "";
  }

  bool have_errors() {
    return errors_.size() > 0;
  }

 private:
  std::map<int, std::string> errors_;
};

class Singleton {
 public:
  static ErrorCollector& GetInstance();
};
