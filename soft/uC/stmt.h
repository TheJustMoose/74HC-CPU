#pragma once

#include "node.h"

#include "lexer.h"

class Stmt: public Node {
 public:
  Stmt() {}

  static Stmt* Null() {
    return new Stmt();
  }

  static Stmt* Enclosing() {
    return Stmt::Null();    // used for break stmts
  }

  void gen(int b, int a) {} // called with labels begin and after

 private:
  int after_ {0};           // saves label after
};

class If: public Stmt {
 public:
  If(Expr* x, Stmt* s)
    : expr_(x), stmt_(s) {
    if (expr_->type() != Lexer::get_word("bool"))
      error("boolean required in if");
  }

  void gen(int b, int a) {
    int label = newlabel(); // label for the code for stmt
    expr_->jumping(0, a);     // fall through on true, goto a on false
    emitlabel(label);
    stmt_->gen(label, a);
  }

 private:
  Expr* expr_ {nullptr};
  Stmt* stmt_ {nullptr};
};
