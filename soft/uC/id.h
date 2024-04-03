#pragma once

#include "expr.h"

class Id: public Expr {
 public:
  Id(Word id, Type p, int off)
    : Expr(id, p), offset_(off) {}

 private:
  int offset_ {0};     // relative address
};
