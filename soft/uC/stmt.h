#pragma once

#include "node.h"

class Stmt: public Node {
 public:
  Stmt() {}

  static Stmt* Null() {
    static Stmt* inst = new Stmt();
    return inst;
  }

  static Stmt* Enclosing() {
    return Stmt::Null();     // used for break stmts
  }

  void gen(int b, int a) {} // called with labels begin and after

 private:
  int after_ = 0;           // saves label after
};
