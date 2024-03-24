#include "parser.h"

#include "lexer.h"
#include "tag.h"

using namespace std;

Parser::Parser(Lexer* l)
  : lex_(l) {
  move();
}

void Parser::move() {
  look_ = lex_->scan();
}

void Parser::program() {
}
