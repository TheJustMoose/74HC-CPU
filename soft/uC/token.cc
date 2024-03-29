#include "token.h"

#include <string>

using namespace std;

Token::Token(Tag t)
  : tag_(t) {}

Token::Token(char c)
  : tag_((Tag)c) {}

string Token::toString() {
  return to_string((int)tag_);
}

Num::Num(int v)
  : Token(Tag::tNUM), value_(v) {}

string Num::toString() {
  string res = to_string(value_);
  return res;
}

Real::Real(float v)
  : Token(Tag::tREAL), value_(v) {}

string Real::toString() {
  return to_string(value_);
}
