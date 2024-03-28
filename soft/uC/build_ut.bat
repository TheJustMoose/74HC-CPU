del unit_tests.exe
"C:\Program Files\LLVM\bin\clang.exe" -std=c++17 -I doctest\doctest ^
 unit_tests.cc lexer.cc num.cc real.cc token.cc type.cc word.cc -o unit_tests.exe 2>err.txt
