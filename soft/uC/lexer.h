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

  static int line() {
    return line_;
  }

  static std::shared_ptr<Word> GetWord(std::string word);

 protected:
  void reserve(std::shared_ptr<Word> w);
  void readch();
  bool readch(char c);

 private:
  char peek_ {' '};
  static int line_;

  std::istream& is_;

  // only one Lexer can work now
  static std::map<std::string, std::shared_ptr<Word>> words_;
};
