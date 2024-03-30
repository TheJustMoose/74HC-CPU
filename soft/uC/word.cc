#include "word.h"

using namespace std;

Word::Word(std::string s, Tag tag)
  : Token(tag), lexeme_(s) {
}

string Word::toString() {
  return lexeme_;
}
