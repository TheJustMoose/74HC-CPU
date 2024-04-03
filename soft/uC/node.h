#pragma once

#include <iostream>
#include <string>
#include <stdexcept>

#include "lexer.h"

class Node {
 public:
  Node() { lexline = Lexer::line(); }

  int newlabel() { return ++labels; }
  void emitlabel(int i) { std::cout << "L" << i << ":"; }
  void emit(std::string s) { std::cout << "\t" << s << std::endl; }

 private:
  int lexline = 0;

  void error(std::string s) {
    throw new std::runtime_error("near line " + std::to_string(lexline) + ": " + s);
  }

  static int labels;
};
