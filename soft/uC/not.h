#pragma once

#include "logical.h"

class Not: public Logical {
 public:
  Not(Token* tok, Expr* x2);
};
