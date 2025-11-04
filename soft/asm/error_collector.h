#pragma once

#include <iostream>
#include <map>
#include <string>

class ErrorCollector {
 public:
  static void rep(std::string msg, int line) {
    ErrorCollector::errors_[line] = msg;
  }

  static void clr(int line) {
    if (ErrorCollector::errors_.find(line) !=
        ErrorCollector::errors_.end())
      ErrorCollector::errors_[line] = "";
  }

  static std::map<int, std::string> get() {
    return ErrorCollector::errors_;
  }

  static std::string get(int line) {
    if (ErrorCollector::errors_.find(line) !=
        ErrorCollector::errors_.end())
      return ErrorCollector::errors_[line];
    else
      return "";
  }

 private:
  static std::map<int, std::string> errors_;
};
