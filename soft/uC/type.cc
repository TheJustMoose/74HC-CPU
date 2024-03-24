#include "type.h"

#include <memory>

using namespace std;

Type* Type::Int() {
  static unique_ptr<Type> ptr = make_unique<Type>( "int", Tag::BASIC, 4 );
  return ptr.get();
}

Type* Type::Float() {
  static unique_ptr<Type> ptr = make_unique<Type>( "float", Tag::BASIC, 8 );
  return ptr.get();
}

Type* Type::Char() {
  static unique_ptr<Type> ptr = make_unique<Type>( "char", Tag::BASIC, 1 );
  return ptr.get();
}

Type* Type::Bool() {
  static unique_ptr<Type> ptr = make_unique<Type>( "bool", Tag::BASIC,1 );
  return ptr.get();
}
