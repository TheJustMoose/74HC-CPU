#include "token.h"

#include <string>

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
