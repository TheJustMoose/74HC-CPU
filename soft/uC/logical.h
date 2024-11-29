#pragma once

#include "expr.h"

class Logical: public Expr {
 public:
  Logical(Token* tok, Expr* x1, Expr* x2);
};

class And: public Logical {
 public:
  And(Token* tok, Expr* x1, Expr* x2);
};

class Or: public Logical {
 public:
  Or(Token* tok, Expr* x1, Expr* x2);
};

class Not: public Logical {
};

class Rel: public Logical {
 public:
  Rel(Token* tok, Expr* x1, Expr* x2);
};
