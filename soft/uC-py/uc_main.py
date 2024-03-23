from uc_inter import *
from uc_lexer import *
from uc_token import *
#from uc_tag import *
from uc_parse import *
import traceback

Word.Init()
Type.Init()
Constant.Init()
Stmt.Init()

try:
  lex = Lexer()
  parse = Parser(lex)
  parse.program();
  print("used: %d" % parse.used)
except Exception as e:
  traceback.print_exc()
  print(e)
