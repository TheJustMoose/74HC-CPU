#include "lexer.h"

#include <iostream>
#include <cctype>
#include "tag.h"
#include "type.h"
#include "word.h"

using namespace std;

// static
map<string, Word*> Lexer::words_ {};
vector<unique_ptr<Word>> words_holder_ {};

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

  if (is_digit(peek_)) {
    int v = 0;
    do {
      v = 10*v + int(peek_ - '0');
      readch();
    } while( is_digit(peek_) );

    if( peek_ != '.' )
      return new Num(v);

    float x = v;
    float d = 10;
    for (;;) {
      readch();
      if (! is_digit(peek_))
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

    Word* w = new Word(s, Tag.ID);
    words_[s] = w;
    words_holder_.emplace_back(make_unique<Word>(w));
    return w;
  } 

  Token tok = new Token(peek_);
  peek_ = ' ';
  return tok;
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
