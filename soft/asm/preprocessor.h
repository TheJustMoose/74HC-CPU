#pragma once

#include <map>
#include <string>
#include <vector>

class Preprocessor {
 public:
  Preprocessor() = default;

  bool Preprocess(std::map<int, std::string> *lines);
  std::string StripLine(std::string);

  bool IsSpace(char);

  std::vector<std::string> Split(std::string);

 private:
  std::map<int, std::string> defines_ {};
};
