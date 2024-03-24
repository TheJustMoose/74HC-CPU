#pragma once

#include <map>
#include <memory>
#include <string>
#include "token.h"

class Word;

class Lexer {
 public:
  Lexer();
  void reserve(Word* w);
  void readch();
  bool readch(char c);
  std::shared_ptr<Token> scan();

  static Word* If();
  static Word* Else();
  static Word* While();
  static Word* Do();
  static Word* Break();

 private:
  char peek_ {' '};
  int line_ {1};
  static std::map<std::string, std::shared_ptr<Token>> words_;
};
