#pragma once

#include <string>

#include "access.h"
#include "expr.h"
#include "id.h"
#include "stmt.h"
#include "type.h"

class Lexer;

class Parser {
 public:
  Parser(Lexer* l);

  void move();
  void error(std::string s);
  void match(int t);
  void program();
  Stmt block();
  void decls();
  Type type();
  Type dims(Type p);
  Stmt stmts();
  Stmt stmt();
  Stmt assign();
  Expr boolean();
  Expr join();
  Expr equality();
  Expr rel();
  Expr expr();
  Expr term();
  Expr unary();
  Expr factor();
  Access offset(Id a);

 private:
  Lexer* lex_ {nullptr};   // lexical analyzer for this parser
  Token* look_ {nullptr};  // lookahead token
};
