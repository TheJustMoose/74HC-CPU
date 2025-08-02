#pragma once

#include "id.h"
#include "op.h"
#include "tag.h"

class Access: public Op {
 public:
  Id* array {nullptr};
  Expr* index {nullptr};

  Access(Id* a, Expr* i, Type* p)       // p is element type after
    : Op(new Word("[]", Tag::tINDEX), p), // flattening the array
    array(a), index(i) {}
};
