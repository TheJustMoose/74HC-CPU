#pragma once

#include "expr.h"

class Constant: public Expr {
 public:
  Constant(Token* tok, Type* p)
    : Expr(tok, p) {}

  Constant(int i)
    : Expr(new Num(i), Type::Int()) {}
};
