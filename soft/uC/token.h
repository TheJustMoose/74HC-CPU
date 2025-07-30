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

 private:
  Tag tag_ { Tag::tEMPTY };
};
