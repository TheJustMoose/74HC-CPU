#include "lexer.h"

#include <iostream>
#include "tag.h"
#include "type.h"
#include "word.h"

using namespace std;

Lexer::Lexer() {
  reserve( Lexer::If() );
  reserve( Lexer::Else() );
  reserve( Lexer::While() );
  reserve( Lexer::Do() );
  reserve( Lexer::Break() );

  reserve( Word::True() );
  reserve( Word::False() );

  reserve( Type::Int()  );
  reserve( Type::Char()  );
  reserve( Type::Bool() );
  reserve( Type::Float() );
}

void Lexer::reserve(Word* w) {
  if (!w) {
    cerr << "Word is NULL" << endl;
    return;
  }

  words_[w->lexeme()] = w;
}

void Lexer::readch() {
  cin >> peek_;
}

bool Lexer::readch(char c) {
  readch();
  if( peek_ != c )
   return false;

  peek_ = ' ';
  return true;
}

Token Lexer::scan() {
}

Word* Lexer::If() {
  static unique_ptr<Word> ptr = make_unique<Word>( "if", Tag::IF );
  return ptr.get();
}

Word* Lexer::Else() {
  static unique_ptr<Word> ptr = make_unique<Word>( "else", Tag::ELSE );
  return ptr.get();
}

Word* Lexer::While() {
  static unique_ptr<Word> ptr = make_unique<Word>( "while", Tag::WHILE );
  return ptr.get();
}

Word* Lexer::Do() {
  static unique_ptr<Word> ptr = make_unique<Word>( "do", Tag::DO );
  return ptr.get();
}

Word* Lexer::Break() {
  static unique_ptr<Word> ptr = make_unique<Word>( "break", Tag::BREAK );
  return ptr.get();
}
