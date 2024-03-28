#include "type.h"

#include <memory>

using namespace std;

Type* Type::Int() {
  static unique_ptr<Type> ptr = make_unique<Type>( "int", Tag::tBASIC, 4 );
  return ptr.get();
}

Type* Type::Float() {
  static unique_ptr<Type> ptr = make_unique<Type>( "float", Tag::tBASIC, 8 );
  return ptr.get();
}

Type* Type::Char() {
  static unique_ptr<Type> ptr = make_unique<Type>( "char", Tag::tBASIC, 1 );
  return ptr.get();
}

Type* Type::Bool() {
  static unique_ptr<Type> ptr = make_unique<Type>( "bool", Tag::tBASIC,1 );
  return ptr.get();
}
