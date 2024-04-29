#include "temp.h"

#include "token.h"

// static
int Temp::count_ {0};

Temp::Temp(Type* p)
  : Expr(Word::temp(), p) {
  number_ = ++count_;
}
