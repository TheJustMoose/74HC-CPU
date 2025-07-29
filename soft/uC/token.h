#pragma once

#include <string>
#include "tag.h"

class Temp;

class Token {
 public:
  Token(Tag t)
    : tag_(t) {}

  Token(char c)
    : tag_((Tag)c) {}

  virtual ~Token() {}

  virtual std::string toString();

  Tag tag() { return tag_; }

  bool isChar() { return static_cast<int>(tag_) < 256; }
  char cTag() { return (static_cast<int>(tag_) < 256) ? static_cast<char>(tag_) : 0; }
  int  rawTag() { return static_cast<int>(tag_); }

 private:
  Tag tag_ {};
};
