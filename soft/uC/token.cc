#include "token.h"

#include <cassert>
#include <iostream>
#include <string>

#include "lexer.h"
#include "num.h"
#include "real.h"
#include "tag.h"
#include "type.h"
#include "word.h"

using namespace std;

string Token::toString() {
  return tag::toString(tag_);
}

bool IsType(Token* t) {
  return t->tag() == Tag::tBASIC;
}

// static
Word* Word::temp() {
  return Lexer::get_word("#t");
}

// static
bool Type::numeric(Type* p) {
  if (p == Type::Char() || p == Type::Int() || p == Type::Float())
    return true;
  else
    return false;
}

// static
Type* Type::max(Type* p1, Type* p2) {
  if ( !Type::numeric(p1) || !Type::numeric(p2) )
    return nullptr;
  else if (p1 == Type::Float() || p2 == Type::Float())
    return Type::Float();
  else if (p1 == Type::Int() || p2 == Type::Int())
    return Type::Int();
  else
    return Type::Char();
}

// static
Type* Type::Bool() {
  Word* w = Lexer::get_word("bool");
  assert(w);
  assert(IsType(w));
  return static_cast<Type*>(w);
}

// static
Type* Type::Char() {
  Word* w = Lexer::get_word("char");
  assert(w);
  assert(IsType(w));
  return static_cast<Type*>(w);
}

// static
Type* Type::Int() {
  Word* w = Lexer::get_word("int");
  assert(w);
  assert(IsType(w));
  return static_cast<Type*>(w);
}

// static
Type* Type::Float() {
  Word* w = Lexer::get_word("float");
  assert(w);
  assert(IsType(w));
  return static_cast<Type*>(w);
}
