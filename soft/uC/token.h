#pragma once

#include <string>

class Token {
 public:
  Token(int t);
  std::string toString();

 private:
  int tag_ {};
};
