#pragma once

#include "op.h"

class Arith: public Op {
 public:
  Arith(Token* tok, Expr* x1, Expr* x2);
};
