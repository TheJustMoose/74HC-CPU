#include "parser.h"

#include <stdexcept>

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

void Parser::error(string s) {
  throw runtime_error("near line " + to_string(lex_->line()) + ": " + s);
}

void Parser::match(Tag t)  {
  if (look_->tag() == t)
    move();
  else
    error("syntax error");
}

void Parser::program() {
  Stmt s = block();
  int begin = s.newlabel();
  int after = s.newlabel();
  s.emitlabel(begin);
  s.gen(begin, after);
  s.emitlabel(after);
}

Stmt Parser::block() {  // block -> { decls stmts }
  match('{');
  Env savedEnv = top;
  top = new Env(top);
  decls();
  Stmt s = stmts();
  match('}');
  top = savedEnv;
  return s;
}

void Parser::decls() {
  while (look_->tag == Tag.BASIC) {   // D -> type ID ;
    Type p = type();
    Token tok = look_;
    match(Tag.ID);
    match(';');

    Id id = new Id((Word)tok, p, used);
    top.put( tok, id);
    used = used + p.width;
  }
}

Type Parser::type() {
  Type p = (Type)look_;   // expect look_->tag == Tag.BASIC 
  match(Tag.BASIC);
  if (look_->tag != '[')
    return p;            // T -> basic
  else
    return dims(p);   // return array type
}

Type Parser::dims(Type p) {
  match('[');
  Token tok = look_;
  match(Tag.NUM);
  match(']');
  if (look_->tag == '[')
    p = dims(p);
  return new Array(((Num)tok).value, p);
}

Stmt stmts() {
  if (look_->tag == '}')
    return Stmt.Null;
  else
    return new Seq(stmt(), stmts());
}

Stmt stmt() {
  Expr x;
  Stmt s, s1, s2;
  Stmt savedStmt;         // save enclosing loop for breaks

  switch (look_->tag()) {
    case ';':
      move();
      return Stmt.Null;

    case Tag.IF:
      match(Tag.IF); match('('); x = boolean(); match(')');
      s1 = stmt();
      if (look_->tag != Tag.ELSE) return new If(x, s1);
      match(Tag.ELSE);
      s2 = stmt();
      return new Else(x, s1, s2);

    case Tag.WHILE:
      While whilenode = new While();
      savedStmt = Stmt.Enclosing; Stmt.Enclosing = whilenode;
      match(Tag.WHILE); match('('); x = boolean(); match(')');
      s1 = stmt();
      whilenode.init(x, s1);
      Stmt.Enclosing = savedStmt;  // reset Stmt.Enclosing
      return whilenode;

    case Tag.DO:
      Do donode = new Do();
      savedStmt = Stmt.Enclosing; Stmt.Enclosing = donode;
      match(Tag.DO);
      s1 = stmt();
      match(Tag.WHILE); match('('); x = boolean(); match(')'); match(';');
      donode.init(s1, x);
      Stmt.Enclosing = savedStmt;  // reset Stmt.Enclosing
      return donode;

    case Tag.BREAK:
      match(Tag.BREAK); match(';');
      return new Break();

    case '{':
      return block();

    default:
      return assign();
    }
}

Stmt assign() {
  Stmt stmt;  Token t = look_;
  match(Tag.ID);
  Id id = top.get(t);
  if (id == null) error(t.toString() + " undeclared");

  if (look_->tag == '=') {       // S -> id = E ;
    move();  stmt = new Set(id, boolean());
  }
  else {                        // S -> L = E ;
    Access x = offset(id);
    match('=');  stmt = new SetElem(x, boolean());
  }
  match(';');
  return stmt;
}

Expr boolean() {
  Expr x = join();
  while (look_->tag == Tag.OR) {
    Token tok = look_;  move();  x = new Or(tok, x, join());
  }

  return x;
}

Expr join() {
  Expr x = equality();
  while (look_->tag == Tag.AND) {
    Token tok = look_;  move();  x = new And(tok, x, equality());
  }

  return x;
}

Expr equality() {
  Expr x = rel();
  while (look_->tag == Tag.EQ || look_->tag == Tag.NE) {
    Token tok = look_;  move();  x = new Rel(tok, x, rel());
  }

  return x;
}

Expr rel() {
  Expr x = expr();
  switch (look_->tag) {
  case '<': case Tag.LE: case Tag.GE: case '>':
    Token tok = look_;  move();  return new Rel(tok, x, expr());
  default:
    return x;
  }
}

Expr expr() {
  Expr x = term();
  while (look_->tag == '+' || look_->tag == '-') {
    Token tok = look_;  move();  x = new Arith(tok, x, term());
  }

  return x;
}

Expr term() {
  Expr x = unary();
  while (look_->tag == '*' || look_->tag == '/') {
    Token tok = look_;  move();   x = new Arith(tok, x, unary());
  }

  return x;
}

Expr unary() {
  if (look_->tag == '-') {
    move();  return new Unary(Word.minus, unary());
  }
  else if (look_->tag == '!') {
    Token tok = look_;  move();  return new Not(tok, unary());
  }
  else
    return factor();
}

Expr factor() {
  Expr x = null;
  switch (look_->tag) {
  case '(':
    move();
    x = boolean();
    match(')');
    return x;
  case Tag.NUM:
    x = new Constant(look_, Type.Int);    move(); return x;
  case Tag.REAL:
    x = new Constant(look_, Type.Float);  move(); return x;
  case Tag.TRUE:
    x = Constant.True;                   move(); return x;
  case Tag.FALSE:
    x = Constant.False;                  move(); return x;
  default:
    error("syntax error");
  return x;
    case Tag.ID:
  String s = look_->toString();
    Id id = top.get(look_);
    if (id == null)
      error(look_->toString() + " undeclared");
    move();
    if (look_->tag != '[')
      return id;
    else
      return offset(id);
  }
}

Access offset(Id a) {   // I -> [E] | [E] I
  Expr i; Expr w; Expr t1, t2; Expr loc;  // inherit id

  Type type = a.type;
  match('['); i = boolean(); match(']');     // first index, I -> [ E ]
  type = ((Array)type).of;
  w = new Constant(type.width);
  t1 = new Arith(new Token('*'), i, w);
  loc = t1;
  while (look_->tag == '[') {      // multi-dimensional I -> [ E ] I
    match('['); i = boolean(); match(']');
    type = ((Array)type).of;
    w = new Constant(type.width);
    t1 = new Arith(new Token('*'), i, w);
    t2 = new Arith(new Token('+'), loc, t1);
    loc = t2;
  }

  return new Access(a, loc, type);
}
