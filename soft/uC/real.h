#pragma once

#include "token.h"

class Real: public Token {
 public:
  Real(float v)
    : Token(Tag::tREAL), value_(v) {}

  std::string toString() override;

 private:
  float value_ {0};
};
