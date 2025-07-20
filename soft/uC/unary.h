#pragma once

#include "op.h"

class Unary: public Op {
 public:
  Expr* expr;

  Unary(Token* tok, Expr* x): Op(tok, nullptr) {  // handles minus, for ! see Not
    expr = x;
    type_ = Type::max(Type::Int(), expr->type());
    if (type_ == nullptr)
      error("type error");
   }

  Expr* gen() {
    return new Unary(op_, expr->reduce());
  }

  std::string toString() {
    return op_->toString() + " " + expr->toString();
  }
};
