#pragma once

#include "tag.h"
#include "token.h"

class Word: public Token {
 public:
  Word(std::string s, Tag tag);

  std::string toString() override;

  std::string lexeme() {
    return lexeme_;
  }

  // Singleton inside And/Or/... own this words
  static Word* And();
  static Word* Or();
  static Word* Eq();
  static Word* Ne();
  static Word* Le();
  static Word* Ge();
  static Word* Minus();
  static Word* True();
  static Word* False();
  static Word* Temp();

 private:
  void Init();

  std::string lexeme_ {};
};
