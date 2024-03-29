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
  reserve( new Word( "if", Tag::tIF ) );
  reserve( new Word( "else", Tag::tELSE ) );
  reserve( new Word( "while", Tag::tWHILE ) );
  reserve( new Word( "do", Tag::tDO ) );
  reserve( new Word( "break", Tag::tBREAK ) );

  reserve( new Word( "true", Tag::tTRUE ) );
  reserve( new Word( "false", Tag::tFALSE ) );

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

  if (words_.find(w->lexeme()) != words_.end()) {
    delete w;  // no good, but work
    return;
  }

  words_[w->lexeme()] = w;
  words_holder_.emplace_back(unique_ptr<Word>(w));  // Okay, we will own this object
}

void Lexer::readch() {
  if (!is_.get(peek_))
    peek_ = 0;
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
    else if (peek_ == 0)
      return nullptr;
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
    } while(peek_ && isdigit(peek_) );

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

  if (peek_ == 0)
    return nullptr;

  Token* tok = new Token(peek_);
  peek_ = ' ';
  return tok;
}
