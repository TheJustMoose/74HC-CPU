#pragma once

#include <string>
#include "token.h"

class Real : public Token {
 public:
  Real(float v);
  virtual ~Real() {}

  std::string toString();

 private:
  float value_ {0};
};
