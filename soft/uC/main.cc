#include <iostream>
#include <memory>

#include "lexer.h"
#include "parser.h"

using namespace std;

int main(int argc, char* argv[]) {
  unique_ptr<Lexer> lex = make_unique<Lexer>();
  unique_ptr<Parser> parse = make_unique<Parser>(lex.get());
  parse->program();
  cout << endl;
}
