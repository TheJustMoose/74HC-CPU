#pragma once

#include "tag.h"
#include "token.h"

class Word: public Token {
 public:
  Word(std::string s, Tag tag);

  std::string toString();

  std::string lexeme() {
    return lexeme_;
  }

  static std::shared_ptr<Token> And();
  static std::shared_ptr<Token> Or();
  static std::shared_ptr<Token> Eq();
  static std::shared_ptr<Token> Ne();
  static std::shared_ptr<Token> Le();
  static std::shared_ptr<Token> Ge();
  static std::shared_ptr<Token> Minus();
  static std::shared_ptr<Token> True();
  static std::shared_ptr<Token> False();
  static std::shared_ptr<Token> Temp();

 private:
  void Init();

  std::string lexeme_ {};
};
