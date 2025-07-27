#pragma once

#include "expr.h"

class Logical: public Expr {
 public:
  Logical(Token* tok, Expr* x1, Expr* x2)
   : Expr(tok, nullptr) {                      // null type to start
    expr1_ = x1;
    expr2_ = x2;
    type_ = check(expr1_->type(), expr2_->type());
    if (type_ == nullptr)
      error("type error");
  }

  Type* check(Type* p1, Type* p2) {
    if (p1 == Type::Bool() && p2 == Type::Bool())
      return Type::Bool();
    else
      return nullptr;
  }


 public:
  Expr* expr1_ { nullptr };
  Expr* expr2_ { nullptr };
};
