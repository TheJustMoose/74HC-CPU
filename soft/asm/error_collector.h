#pragma once

#include <iostream>
#include <map>
#include <string>

class ErrorCollector {
 public:
  static void rep(std::string msg, int line = 0) {
    std::cout << msg << std::endl;
    static int dummy = 1;
    ErrorCollector::errors_[dummy++] = msg;
  }
  static void clr() {
    ErrorCollector::errors_.clear();
  }
  static std::map<int, std::string> get() {
    return ErrorCollector::errors_;
  }

 private:
  static std::map<int, std::string> errors_;
};
