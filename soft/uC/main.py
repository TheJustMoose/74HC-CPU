from inter import *
from lexer import *
from token import *
from tag import *
from parse import *

Word.Init()
Type.Init()
Constant.Init()
Stmt.Init()

lex = Lexer()
parse = Parser(lex)
parse.program();
