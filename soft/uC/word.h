#pragma once

#include "token.h"

class Word: public Token {
 public:
  Word(std::string s, Tag tag)
    : Token(tag), lexeme_(s) {}

  std::string toString() override {
    return lexeme_;
  }

  std::string lexeme() {
    return lexeme_;
  }

  static Word* temp();

 private:
  void Init();

  std::string lexeme_ {};
};
