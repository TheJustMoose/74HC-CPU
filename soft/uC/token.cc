#include "token.h"

#include <string>
#include <iostream>

#include "tag.h"

using namespace std;

string Token::toString() {
  return to_string((int)tag_);
}

string Num::toString() {
  return to_string(value_);
}

string Real::toString() {
  return to_string(value_);
}

bool IsType(Token* t) {
  return t->tag() == Tag::tBASIC;
}
