#include <iostream>
#include <fstream>
#include <memory>

#include "lexer.h"
#include "parser.h"

/*

Данный компилятор имеет два места, которые владеют объектами:

 * словарь внутри лексера, в котором накапливаются идентификаторы,
     и который удаляется в его деструкторе
 * собственно дерево разбора, вершина которого хранится в парсере, а остальные узлы крепятся к вершине
     и которые удаляются в его деструкторе

Все остальные места просто хранят указатели на эти объекты, но не удаляют их.

*/

using namespace std;

int main(int argc, char* argv[]) {
  if (argc != 2) {
    cout << "To use type: 74hc-uC.exe <source file name>" << endl;
    return 1;
  }

  string name(argv[1]);
  cout << "Processing: " << name << endl;

  ifstream f;
  f.open(name, ios::in);
  if (!f) {
    cout << "Error. Can't open file: " << name << endl;
    return 1;
  }

  Lexer lex(f);
  Parser parse(&lex);
  parse.program();

  cout << endl;

  return 0;
}
