#pragma once

#include <string>
#include "tag.h"

class Token {
 public:
  Token(Tag t);
  Token(char c);
  virtual ~Token() {}

  virtual std::string toString();

  Tag tag() { return tag_; }

 private:
  Tag tag_ {};
};

class Num : public Token {
 public:
  Num(int v);
  virtual ~Num() {}

  std::string toString() override;

 private:
  int value_ {0};
};

class Real : public Token {
 public:
  Real(float v);
  virtual ~Real() {}

  std::string toString() override;

 private:
  float value_ {0};
};