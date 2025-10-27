del unit_tests.exe
"C:\Program Files\LLVM\bin\clang.exe" -std=c++17 -I doctest\doctest assm.cc file_reader.cc preprocessor.cc str_util.cc unit_tests.cc -o unit_tests.exe 2>err.txt
