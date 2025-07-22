#pragma once

#include "expr.h"

class Logical: public Expr {
 public:
  Logical(Token* tok, Expr* x1, Expr* x2);
};
