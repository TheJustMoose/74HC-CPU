#pragma once

#include "token.h"

class Word: public Token {
 public:
  Word(std::string s, int tag);

  std::string toString();

 private:
  std::string lexeme_ {};
};
