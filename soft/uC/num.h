#pragma once

#include <string>
#include "token.h"

class Num : public Token {
 public:
  Num(int v);
  virtual ~Num() {}

  std::string toString() override;

 private:
  int value_ {0};
};
