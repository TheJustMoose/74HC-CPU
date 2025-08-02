#pragma once

#include "stmt.h"

class Seq: public Stmt {
 public:
  Seq(Stmt* s1, Stmt* s2)
    : stmt1_(s1), stmt2_(s2) {}

 public:
  Stmt* stmt1_ {nullptr};
  Stmt* stmt2_ {nullptr};
};
