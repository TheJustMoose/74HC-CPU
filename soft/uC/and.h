#pragma once

#include "logical.h"

class And: public Logical {
 public:
  And(Token* tok, Expr* x1, Expr* x2)
   : Logical(tok, x1, x2) {}
};
