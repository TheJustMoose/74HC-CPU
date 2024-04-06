#include "parser.h"

#include <stdexcept>

#include "env.h"
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

void Parser::match(char c) {
  match(static_cast<Tag>(c));
}

void Parser::program() {
  Stmt* s = block();
  int begin = s->newlabel();
  int after = s->newlabel();
  s->emitlabel(begin);
  s->gen(begin, after);
  s->emitlabel(after);
}

Stmt* Parser::block() {  // block -> { decls stmts }
  match('{');
  Env* savedEnv = top_;
  top_ = new Env(top_);
  decls();
  //Stmt s = stmts();
  match('}');
  if (top_)
    delete top_;
  top_ = savedEnv;
  return 0; //s;
}

void Parser::decls() {
  while (look_->tag() == Tag::tBASIC) {   // D -> type ID ;
    Type* p = type();
    Token* tok = look_;
    match(Tag::tID);
    match(';');

    Id* id = new Id(static_cast<Word*>(tok), p, used_);  // check it: who own this var?
    top_->put(tok, id);  // check it: who own this var?
    used_ += p->width();
  }
}

Type* Parser::type() {
  //Type p = (Type)look_;   // expect look_->tag == Tag::tBASIC 
  match(Tag::tBASIC);
  //if (look_->tag != '[')
    return IsType(look_) ? static_cast<Type*>(look_) : nullptr;            // T -> basic
  //else
  //  return dims(p);   // return array type
}

/*
Type Parser::dims(Type p) {
  match('[');
  Token tok = look_;
  match(Tag::tNUM);
  match(']');
  if (look_->tag == '[')
    p = dims(p);
  return new Array(((Num)tok).value, p);
}

Stmt Parser::stmts() {
  if (look_->tag == '}')
    return Stmt.Null;
  else
    return new Seq(stmt(), stmts());
}

Stmt Parser::stmt() {
  Expr x;
  Stmt s, s1, s2;
  Stmt savedStmt;         // save enclosing loop for breaks

  switch (look_->tag()) {
    case ';':
      move();
      return Stmt.Null;

    case Tag::tIF:
      match(Tag::tIF); match('('); x = boolean(); match(')');
      s1 = stmt();
      if (look_->tag != Tag::tELSE) return new If(x, s1);
      match(Tag::tELSE);
      s2 = stmt();
      return new Else(x, s1, s2);

    case Tag::tWHILE:
      While whilenode = new While();
      savedStmt = Stmt.Enclosing; Stmt.Enclosing = whilenode;
      match(Tag::tWHILE); match('('); x = boolean(); match(')');
      s1 = stmt();
      whilenode.init(x, s1);
      Stmt.Enclosing = savedStmt;  // reset Stmt.Enclosing
      return whilenode;

    case Tag::tDO:
      Do donode = new Do();
      savedStmt = Stmt.Enclosing; Stmt.Enclosing = donode;
      match(Tag::tDO);
      s1 = stmt();
      match(Tag::tWHILE); match('('); x = boolean(); match(')'); match(';');
      donode.init(s1, x);
      Stmt.Enclosing = savedStmt;  // reset Stmt.Enclosing
      return donode;

    case Tag::tBREAK:
      match(Tag::tBREAK); match(';');
      return new Break();

    case '{':
      return block();

    default:
      return assign();
    }
}

Stmt Parser::assign() {
  Stmt stmt;  Token t = look_;
  match(Tag::tID);
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

Expr Parser::boolean() {
  Expr x = join();
  while (look_->tag == Tag::tOR) {
    Token tok = look_;  move();  x = new Or(tok, x, join());
  }

  return x;
}

Expr Parser::join() {
  Expr x = equality();
  while (look_->tag == Tag::tAND) {
    Token tok = look_;  move();  x = new And(tok, x, equality());
  }

  return x;
}

Expr Parser::equality() {
  Expr x = rel();
  while (look_->tag == Tag::tEQ || look_->tag == Tag::tNE) {
    Token tok = look_;  move();  x = new Rel(tok, x, rel());
  }

  return x;
}

Expr Parser::rel() {
  Expr x = expr();
  switch (look_->tag) {
  case '<': case Tag::tLE: case Tag::tGE: case '>':
    Token tok = look_;  move();  return new Rel(tok, x, expr());
  default:
    return x;
  }
}

Expr Parser::expr() {
  Expr x = term();
  while (look_->tag == '+' || look_->tag == '-') {
    Token tok = look_;  move();  x = new Arith(tok, x, term());
  }

  return x;
}

Expr Parser::term() {
  Expr x = unary();
  while (look_->tag == '*' || look_->tag == '/') {
    Token tok = look_;  move();   x = new Arith(tok, x, unary());
  }

  return x;
}

Expr Parser::unary() {
  if (look_->tag == '-') {
    move();  return new Unary(Word.minus, unary());
  }
  else if (look_->tag == '!') {
    Token tok = look_;  move();  return new Not(tok, unary());
  }
  else
    return factor();
}

Expr Parser::factor() {
  Expr x = null;
  switch (look_->tag) {
  case '(':
    move();
    x = boolean();
    match(')');
    return x;
  case Tag::tNUM:
    x = new Constant(look_, Type.Int);    move(); return x;
  case Tag::tREAL:
    x = new Constant(look_, Type.Float);  move(); return x;
  case Tag::tTRUE:
    x = Constant.True;                   move(); return x;
  case Tag::tFALSE:
    x = Constant.False;                  move(); return x;
  default:
    error("syntax error");
  return x;
    case Tag::tID:
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

Access Parser::offset(Id a) {   // I -> [E] | [E] I
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
*/
