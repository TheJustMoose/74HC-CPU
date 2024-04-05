del unit_tests.exe
"C:\Program Files\LLVM\bin\clang.exe" -std=c++17 -I doctest\doctest ^
 unit_tests.cc lexer.cc node.cc parser.cc token.cc word_fab.cc -o unit_tests.exe 2>err.txt
