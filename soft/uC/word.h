#pragma once

#include <memory>

#include "tag.h"
#include "token.h"

class Word: public Token {
 public:
  Word(std::string s, Tag tag);

  std::string toString() override;

  std::string lexeme() {
    return lexeme_;
  }

  static std::shared_ptr<Word> And();
  static std::shared_ptr<Word> Or();
  static std::shared_ptr<Word> Eq();
  static std::shared_ptr<Word> Ne();
  static std::shared_ptr<Word> Le();
  static std::shared_ptr<Word> Ge();
  static std::shared_ptr<Word> Minus();
  static std::shared_ptr<Word> Temp();

 private:
  void Init();

  std::string lexeme_ {};
};
