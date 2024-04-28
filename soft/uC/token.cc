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

// static
bool Type::numeric(Type p) {
  if (p == Type.Char || p == Type.Int || p == Type.Float) return true;
    else return false;
}

// static
Type* Type::max(Type* p1, Type* p2) {
  if ( ! Type::numeric(p1) || ! Type::numeric(p2) )
    return nullptr;
  else if (p1 == Type.Float || p2 == Type.Float)
    return Type.Float;
  else if (p1 == Type.Int || p2 == Type.Int)
    return Type.Int;
  else
    return Type.Char;
}
