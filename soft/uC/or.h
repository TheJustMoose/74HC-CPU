#pragma once

#include "logical.h"

class Or: public Logical {
 public:
  Or(Token* tok, Expr* x1, Expr* x2)
   : Logical(tok, x1, x2) {}
};
