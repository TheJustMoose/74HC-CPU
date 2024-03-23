#pragma once

#include "token.h"
#include "word.h"

class Lexer {
 public:
  Lexer();
  void reserve(Word w);
  void readch();
  bool readch(char c);
  Token scan();

 private:
  char peek_ {' '};
};
