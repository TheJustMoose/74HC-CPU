#pragma once

#include <string>
#include "word.h"

class Type: public Word {
 public:
  Type(std::string s, Tag tag, int w)
    : Word(s, tag), width_(w) {}

  static Type* Int();
  static Type* Float();
  static Type* Char();
  static Type* Bool();

 private:
  int width_ {0};
};
