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
  bool IsDelimeter(char);

  std::vector<std::string> Split(std::string);
  void AddDefineIntoMap(std::vector<std::string> parts);

 private:
  std::map<std::string, std::vector<std::string>> defines_ {};
};
