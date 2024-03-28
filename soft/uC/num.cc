#include "num.h"

#include "tag.h"

using namespace std;

Num::Num(int v)
  : Token(Tag::tNUM), value_(v) {}

string Num::toString() {
  return to_string(value_);
}
