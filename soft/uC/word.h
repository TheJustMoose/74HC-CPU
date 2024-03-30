#pragma once

#include <memory>

#include "tag.h"
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

 private:
  void Init();

  std::string lexeme_ {};
};

class Type: public Word {
 public:
  Type(std::string s, Tag tag, int w)
    : Word(s, tag), width_(w) {}

 private:
  int width_ {0};
};
