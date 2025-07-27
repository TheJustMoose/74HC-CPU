del unit_tests.exe
"C:\Program Files\LLVM\bin\clang.exe" -std=c++17 -I doctest\doctest ^
 unit_tests.cc lexer.cc node.cc parser.cc temp.cc token.cc const.cc -o unit_tests.exe >err.txt 2>&1
