#pragma once

#include <string>
#include "tag.h"

class Token {
 public:
  Token(Tag t);
  virtual ~Token() {}

  std::string toString();

 private:
  Tag tag_ {};
};
