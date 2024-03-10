#pragma once

#include <map>
#include <string>

class Preprocessor {
 public:
  Preprocessor() = default;

  bool Preprocess(std::map<int, std::string> *lines);
  std::string StripLine(std::string);

  bool IsSpace(char);
};
