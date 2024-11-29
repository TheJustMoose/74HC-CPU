#include "parser.h"

#include <stdexcept>

#include "arith.h"
#include "const.h"
#include "env.h"
#include "lexer.h"
#include "logical.h"
#include "tag.h"

using namespace std;

Parser::Parser(Lexer* l)
  : lex_(l) {
  move();
}

void Parser::move() {
  look_ = lex_->scan();
  if (look_)
    cout << "look_: " << look_->toString() << endl;
  else
    cout << "look_: nullptr" << endl;
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
  if (look_->ctag() == c)
    move();
  else
    error("syntax error");
}

void Parser::program() {
  Stmt* s = block();
  if (!s)
    return;

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
  Stmt* s = stmts();
  match('}');
  delete top_;
  top_ = savedEnv;
  return s;
}

void Parser::decls() {
  while (look_ && (look_->tag() == Tag::tBASIC)) {   // D -> type ID ;
    Type* p = type();
    if (!p)
      cout << "p is null" << endl;
    Token* tok = look_;
    match(Tag::tID);
    match(';');

    Id* id = new Id(static_cast<Word*>(tok), p, used_);  // check it: who own this var?
    top_->put(tok, id);  // check it: who own this var?
    used_ += p->width();
  }
}

Type* Parser::type() {
  Type* p = IsType(look_) ? static_cast<Type*>(look_) : nullptr;  // expect look_->tag == Tag::tBASIC
  match(Tag::tBASIC);
  if (look_->ctag() != '[')
    return p;            // T -> basic
  else
    return nullptr; //dims(p);   // return array type
}

/*
Type Parser::dims(Type p) {
  match('[');
  Token tok = look_;
  match(Tag::tNUM);
  match(']');
  if (look_->ctag() == '[')
    p = dims(p);
  return new Array(((Num)tok).value, p);
}
*/
Stmt* Parser::stmts() {
  if (look_->ctag() == '}')
    return Stmt::Null();
  else
    return nullptr;//new Seq(stmt(), stmts());
}

Stmt* Parser::stmt() {
  Expr* x {nullptr};
  Stmt* s {nullptr};
  Stmt* s1 {nullptr};
  Stmt* s2 {nullptr};
  Stmt* savedStmt {nullptr};  // save enclosing loop for breaks

  switch (look_->tag()) {
    case Tag::tSEMI: {
      move();
      return Stmt::Null();
    }

    case Tag::tIF: {
      match(Tag::tIF); match('('); x = boolean(); match(')');
      s1 = stmt();
      if (look_->tag() != Tag::tELSE)
        return new If(x, s1);
      match(Tag::tELSE);
      s2 = stmt();
      return new Else(x, s1, s2);
    }

    case Tag::tWHILE: {
      While* whilenode = new While();
      savedStmt = Stmt::Enclosing;
      Stmt::Enclosing = whilenode;
      match(Tag::tWHILE); match('('); x = boolean(); match(')');
      s1 = stmt();
      whilenode->init(x, s1);
      Stmt::Enclosing = savedStmt;  // reset Stmt.Enclosing
      return whilenode;
    }

    case Tag::tDO: {
      Do* donode = new Do();
      savedStmt = Stmt::Enclosing;
      Stmt::Enclosing = donode;
      match(Tag::tDO);
      s1 = stmt();
      match(Tag::tWHILE); match('('); x = boolean(); match(')'); match(';');
      donode->init(s1, x);
      Stmt::Enclosing = savedStmt;  // reset Stmt.Enclosing
      return donode;
    }

    case Tag::tBREAK: {
      match(Tag::tBREAK); match(';');
      return new Break();
    }

    case Tag::tLBRACE: {
      return block();
    }

    default: {
      return assign();
    }
  }
}

Stmt* Parser::assign() {
  Stmt* stmt;
  Token* t {look_};
  match(Tag::tID);
  Id* id = top_->get(t);
  if (id == nullptr)
    error(t->toString() + " undeclared");

  if (look_->ctag() == '=') {       // S -> id = E ;
    move();
    stmt = new Set(id, boolean());
  } else {                        // S -> L = E ;
    Access* x = nullptr; // offset(id);
    match('=');
    stmt = new SetElem(x, boolean());
  }
  match(';');
  return stmt;
}

Expr* Parser::boolean() {
  Expr* x = join();
  while (look_->tag() == Tag::tOR) {
    Token* tok {look_};
    move();
    x = new Or(tok, x, join());
  }

  return x;
}

Expr* Parser::join() {
  Expr* x = equality();
  while (look_->tag() == Tag::tAND) {
    Token* tok {look_};
    move();
    x = new And(tok, x, equality());
  }

  return x;
}

Expr* Parser::equality() {
  Expr* x = rel();
  while (look_->tag() == Tag::tEQ || look_->tag() == Tag::tNE) {
    Token* tok {look_};
    move();
    x = new Rel(tok, x, rel());
  }

  return x;
}

Expr* Parser::rel() {
  Expr* x = expr();
  switch (look_->tag()) {
    case Tag::tLess:
    case Tag::tLE:
    case Tag::tGE:
    case Tag::tMore: {
      Token* tok {look_};
      move();
      return new Rel(tok, x, expr());
    }
    default:
      return x;
  }
}

Expr* Parser::expr() {
  Expr* x = term();
  while (look_->ctag() == '+' || look_->ctag() == '-') {
    Token* tok {look_};
    move();
    x = new Arith(tok, x, term());
  }

  return x;
}

Expr* Parser::term() {
  Expr* x = unary();
  while (look_->ctag() == '*' || look_->ctag() == '/') {
    Token* tok {look_};
    move();
    x = new Arith(tok, x, unary());
  }

  return x;
}

Expr* Parser::unary() {
  if (look_->ctag() == '-') {
    move();
    return new Unary(Tag::tMINUS, unary());
  } else if (look_->ctag() == '!') {
    Token* tok {look_};
    move();
    return new Not(tok, unary());
  }
  else
    return factor();
}

Expr* Parser::factor() {
  Expr* x {nullptr};
  switch (look_->tag()) {
    case '(':
      move();
      x = boolean();
      match(')');
      return x;
    case Tag::tNUM:
      x = new Constant(look_, Type::Int());
      move();
      return x;
    case Tag::tREAL:
      x = new Constant(look_, Type::Float());
      move();
      return x;
    case Tag::tTRUE:
      x = Constant.True;
      move();
      return x;
    case Tag::tFALSE:
      x = Constant.False;
      move();
      return x;
    case Tag::tID:
      //string s = look_->toString();
      Id* id = top.get(look_);
      if (id == nullptr)
        error(look_->toString() + " undeclared");
      move();
      if (look_->ctag() != '[')
        return id;
      else
        return nullptr; //offset(id);
    default:
      error("syntax error");
      return x;
  }
}
/*
Access Parser::offset(Id a) {   // I -> [E] | [E] I
  Expr i; Expr w; Expr t1, t2; Expr loc;  // inherit id

  Type type = a.type;
  match('['); i = boolean(); match(']');     // first index, I -> [ E ]
  type = ((Array)type).of;
  w = new Constant(type.width);
  t1 = new Arith(new Token('*'), i, w);
  loc = t1;
  while (look_->ctag() == '[') {      // multi-dimensional I -> [ E ] I
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
