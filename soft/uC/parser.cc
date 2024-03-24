#include "parser.h"

#include "lexer.h"
#include "tag.h"

Parser::Parser(Lexer* l)
  : lex_(l) {
  move();
}

void Parser::move() {
  look_ = lex_->scan();
}

void Parser::program() {
}
