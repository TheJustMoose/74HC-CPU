#pragma once

#include <string>

#include "expr.h"

class Type;

class Temp: public Expr {
 public:
  Temp(Type* p);

  std::string toString() {
    return "t" + std::to_string(number_);
  }

 private:
  static int count_;
  int number_ {0};
};
