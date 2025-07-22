#pragma once

#include "expr.h"
#include "word.h"

class Type;

class Id: public Expr {
 public:
  Id(Word* id, Type* t, int off)
    : Expr(id, t), offset_(off) {}

 private:
  int offset_ {0};     // relative address
};
