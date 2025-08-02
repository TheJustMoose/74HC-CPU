#pragma once

#include <string>

#include "tag.h"
#include "type.h"

class Array: public Type {
 public:
  Type* of {nullptr};    // array *of* type
  int size = 1;          // number of elements

  Array(int sz, Type* p)
    : Type("[]", Tag::tINDEX, sz*p->width()), size(sz), of(p) {}

  std::string toString() {
    return std::string("[") + std::to_string(size) + std::string("] ") + of->toString();
  }
};
