#pragma once

#include <string>
#include "tag.h"

class Token {
 public:
  Token(Tag t)
    : tag_(t) {}

  Token(char c)
    : tag_((Tag)c) {}

  virtual ~Token() {}

  virtual std::string toString();

  Tag tag() { return tag_; }
  char ctag() { return (static_cast<int>(tag_) < 256) ? static_cast<char>(tag_) : 0; }

 private:
  Tag tag_ {};
};

class Num : public Token {
 public:
  Num(int v)
    : Token(Tag::tNUM), value_(v) {}

  std::string toString() override;

 private:
  int value_ {0};
};

class Real : public Token {
 public:
  Real(float v)
    : Token(Tag::tREAL), value_(v) {}

  std::string toString() override;

 private:
  float value_ {0};
};

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

  int width() { return width_; }

  static bool numeric(Type* p);
  static Type* max(Type* p1, Type* p2);

 private:
  int width_ {0};
};

bool IsType(Token* t);
