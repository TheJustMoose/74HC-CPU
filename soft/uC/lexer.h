#pragma once

#include <map>
#include <string>
#include "token.h"

class Word;

class Lexer {
 public:
  Lexer();
  void reserve(Word* w);
  void readch();
  bool readch(char c);
  Token scan();

  static Word* If();
  static Word* Else();
  static Word* While();
  static Word* Do();
  static Word* Break();

 private:
  char peek_ {' '};
  std::map<std::string, Word*> words_ {};
};
