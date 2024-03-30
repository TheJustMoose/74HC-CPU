#include "lexer.h"

#include <iostream>
#include <cctype>
#include "tag.h"
#include "type.h"
#include "word.h"

using namespace std;

// static
map<string, shared_ptr<Token>> Lexer::words_ {};

Lexer::Lexer(istream& is)
  : is_(is) {
  reserve( shared_ptr<Word>(new Word( "if", Tag::tIF )) );
  reserve( shared_ptr<Word>(new Word( "else", Tag::tELSE )) );
  reserve( shared_ptr<Word>(new Word( "while", Tag::tWHILE )) );
  reserve( shared_ptr<Word>(new Word( "do", Tag::tDO )) );
  reserve( shared_ptr<Word>(new Word( "break", Tag::tBREAK )) );

  reserve( shared_ptr<Word>(new Word( "true", Tag::tTRUE )) );
  reserve( shared_ptr<Word>(new Word( "false", Tag::tFALSE )) );

  reserve( shared_ptr<Word>(Type::Int()) );
  reserve( shared_ptr<Word>(Type::Char()) );
  reserve( shared_ptr<Word>(Type::Bool()) );
  reserve( shared_ptr<Word>(Type::Float()) );
}

void Lexer::reserve(shared_ptr<Word> w) {
  if (!w) {
    cerr << "Word is NULL" << endl;
    return;
  }

  // w will be removed during return cause ref count will become zero
  if (words_.find(w->lexeme()) != words_.end())
    return;

  words_[w->lexeme()] = w;
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

shared_ptr<Token> Lexer::scan() {
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
      if( readch('&') ) return Word::And();  else return shared_ptr<Token>(new Token('&'));
    case '|':
      if( readch('|') ) return Word::Or();   else return shared_ptr<Token>(new Token('|'));
    case '=':
      if( readch('=') ) return Word::Eq();   else return shared_ptr<Token>(new Token('='));
    case '!':
      if( readch('=') ) return Word::Ne();   else return shared_ptr<Token>(new Token('!'));
    case '<':
      if( readch('=') ) return Word::Le();   else return shared_ptr<Token>(new Token('<'));
    case '>':
      if( readch('=') ) return Word::Ge();   else return shared_ptr<Token>(new Token('>'));
  }

  if (isdigit(peek_)) {
    int v = 0;
    do {
      v = 10*v + int(peek_ - '0');
      readch();
    } while(peek_ && isdigit(peek_) );

    if( peek_ != '.' )
      return shared_ptr<Token>(new Num(v));

    float x = v;
    float d = 10;
    for (;;) {
      readch();
      if (! isdigit(peek_))
        break;
      x = x + int(peek_ - '0') / d;
      d *= 10;
    }
    return shared_ptr<Token>(new Real(x));
  }

  if (isalpha(peek_)) {
    string b;
    do {
      b += peek_;
      readch();
    } while (isalpha(peek_));

    if (words_.find(b) != words_.end())
      return words_[b];

    shared_ptr<Word> w(new Word(b, Tag::tID));
    words_[b] = w;
    return w;
  } 

  if (peek_ == 0)
    return shared_ptr<Token>();

  shared_ptr<Token> tok(new Token(peek_));
  peek_ = ' ';
  return tok;
}
