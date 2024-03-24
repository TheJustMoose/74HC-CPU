#pragma once

#include <string>
#include "tag.h"

class Token {
 public:
  Token(Tag t);
  std::string toString();

 private:
  Tag tag_ {};
};
