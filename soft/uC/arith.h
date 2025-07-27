#pragma once

#include "op.h"
#include "type.h"

class Arith: public Op {
 public:
  Arith(Token* tok, Expr* x1, Expr* x2)
   : Op(tok, nullptr) {
    expr1_ = x1;
    expr2_ = x2;
    type_ = Type::max(expr1_->type(), expr2_->type());
    if (type_ == nullptr)
      error("type error");
  }

 public:
  Expr* expr1_ { nullptr };
  Expr* expr2_ { nullptr };
};
