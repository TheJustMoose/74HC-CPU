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
