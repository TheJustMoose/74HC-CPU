#include "real.h"

#include "tag.h"

using namespace std;

Real::Real(float v)
  : Token(Tag::tREAL), value_(v) {}

string Real::toString() {
  return to_string(value_);
}
