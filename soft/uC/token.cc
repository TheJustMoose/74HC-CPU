#include "token.h"

#include <string>

Token::Token(int t)
  : tag_(t) {}

string Token::toString() {
  return to_string(tag_);
}
