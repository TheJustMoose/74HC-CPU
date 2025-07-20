#pragma once

#include "expr.h"
#include "temp.h"

class Op: public Expr {
 public:
  Op(Token* tok, Type* p)
    : Expr(tok, p) {}

  Expr* reduce() {
    Expr* x = gen();
    Temp* t = new Temp(type());
    emit(t->toString() + " = " + x->toString());
    return t;
  }
};
