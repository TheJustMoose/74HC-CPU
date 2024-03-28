#include "lexer.h"

#include <iostream>
#include <cctype>
#include "num.h"
#include "real.h"
#include "tag.h"
#include "type.h"
#include "word.h"

using namespace std;

// static
map<string, Word*> Lexer::words_ {};
vector<unique_ptr<Word>> Lexer::words_holder_ {};

Lexer::Lexer(istream& is)
  : is_(is) {
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
  is_ >> peek_;
}

bool Lexer::readch(char c) {
  readch();
  if( peek_ != c )
   return false;

  peek_ = ' ';
  return true;
}

Token* Lexer::scan() {
  for( ; ; readch() ) {
    if (peek_ == ' ' || peek_ == '\t' || peek_ == '\r')
      continue;
    else if (peek_ == '\n')
      line_++;
    else
      break;
  }

  switch( peek_ ) {
    case '&':
      if( readch('&') ) return Word::And();  else return new Token('&');
    case '|':
      if( readch('|') ) return Word::Or();   else return new Token('|');
    case '=':
      if( readch('=') ) return Word::Eq();   else return new Token('=');
    case '!':
      if( readch('=') ) return Word::Ne();   else return new Token('!');
    case '<':
      if( readch('=') ) return Word::Le();   else return new Token('<');
    case '>':
      if( readch('=') ) return Word::Ge();   else return new Token('>');
  }

  if (isdigit(peek_)) {
    int v = 0;
    do {
      v = 10*v + int(peek_ - '0');
      readch();
    } while( isdigit(peek_) );

    if( peek_ != '.' )
      return new Num(v);

    float x = v;
    float d = 10;
    for (;;) {
      readch();
      if (! isdigit(peek_))
        break;
      x = x + int(peek_ - '0') / d;
      d *= 10;
    }
    return new Real(x);
  }

  if (isalpha(peek_)) {
    string b;
    do {
      b += peek_;
      readch();
    } while (isalpha(peek_));

    if (words_.find(b) != words_.end())
      return words_[b];

    Word* w = new Word(b, Tag::tID);
    words_[b] = w;
    words_holder_.emplace_back(unique_ptr<Word>(w));
    return w;
  } 

  Token* tok = new Token(peek_);
  peek_ = ' ';
  return tok;
}

Word* Lexer::If() {
  static unique_ptr<Word> ptr = make_unique<Word>( "if", Tag::tIF );
  return ptr.get();
}

Word* Lexer::Else() {
  static unique_ptr<Word> ptr = make_unique<Word>( "else", Tag::tELSE );
  return ptr.get();
}

Word* Lexer::While() {
  static unique_ptr<Word> ptr = make_unique<Word>( "while", Tag::tWHILE );
  return ptr.get();
}

Word* Lexer::Do() {
  static unique_ptr<Word> ptr = make_unique<Word>( "do", Tag::tDO );
  return ptr.get();
}

Word* Lexer::Break() {
  static unique_ptr<Word> ptr = make_unique<Word>( "break", Tag::tBREAK );
  return ptr.get();
}
