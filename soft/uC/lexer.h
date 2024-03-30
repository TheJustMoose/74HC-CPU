#pragma once

#include <map>
#include <memory>
#include <string>
#include <vector>
#include "token.h"

class Word;

namespace str {
class istream;
}

class Lexer {
 public:
  Lexer(std::istream& is);
  std::shared_ptr<Token> scan();

 protected:
  void reserve(std::shared_ptr<Word> w);
  void readch();
  bool readch(char c);

 private:
  char peek_ {' '};
  int line_ {1};

  std::istream& is_;

  // only one Lexer can work now
  static std::map<std::string, std::shared_ptr<Token>> words_;
};
