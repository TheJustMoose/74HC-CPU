#include <iostream>
#include <memory>

#include "lexer.h"
#include "parser.h"

using namespace std;

int main(int argc, char* argv[]) {
  Lexer lex(cin);
  Parser parse(&lex);
  parse.program();
  cout << endl;
}
