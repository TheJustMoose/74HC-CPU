#pragma once

#include "logical.h"

class Rel: public Logical {
 public:
  Rel(Token* tok, Expr* x1, Expr* x2)
   : Logical(tok, x1, x2) {}
};
