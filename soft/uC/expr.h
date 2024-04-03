#pragma once

#include <string>

#include "node.h"
#include "token.h"

class Expr: public Node {
 public:
  Token op;
  Type type;

  Expr(Token tok, Type p)
    : op(tok), type(p) {}

  Expr* gen() { return this; }
  Expr* reduce() { return this; }

  void jumping(int t, int f) {
    emitjumps(toString(), t, f);
  }

  void emitjumps(std::string test, int t, int f) {
    if (t != 0 && f != 0) {
      emit("if " + test + " goto L" + std::to_string(t));
      emit("goto L" + std::to_string(f));
    }
    else if( t != 0 )
      emit("if " + test + " goto L" + std::to_string(t));
    else if( f != 0 )
      emit("iffalse " + test + " goto L" + std::to_string(f));
    else
      ; // nothing since both t and f fall through
   }

  std::string toString() { return op.toString(); }
};
