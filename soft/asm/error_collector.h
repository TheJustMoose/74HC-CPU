#pragma once

#include <iostream>
#include <map>
#include <string>
#include <vector>

class ErrorCollector {
 public:
  static void rep(std::string msg) {
    std::cout << msg << std::endl;
    ErrorCollector::errors_.push_back(msg);
  }
  static void clr() {
    ErrorCollector::errors_.clear();
  }
  static std::vector<std::string> get() {
    return ErrorCollector::errors_;
  }

 private:
  static std::vector<std::string> errors_;
};
