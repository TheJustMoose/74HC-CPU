#pragma once

#include <string>
#include "tag.h"

class Token {
 public:
  Token(Tag t);
  Token(char c);
  virtual ~Token() {}

  std::string toString();

  Tag tag() { return tag_; }

 private:
  Tag tag_ {};
};
