from lexer import *
from token import *
from tag import *

t = Token(Tag.EQ)
print(t.toString())

n = Num(123)
print(n.toString())

w = Word("test", Tag.ID)
print(w.toString())

Word.Init()
Type.Init()

print(Word.AND.toString())
print(Word.OR.toString())
print(Word.TRUE.toString())

r = Real(1.33)
print(r.toString())

l = Lexer()
print("if in list", l.word_in_words("if"))
print("none in list", l.word_in_words("none"))

#print
l.log()

print("CHAR is numeric? ", Type.Numeric(Type.CHAR))
print("INT is numeric? ", Type.Numeric(Type.INT))

while True:
  t = l.scan()
  if t == None:
    break;
  print("numeric? ", Type.Numeric(t))
  print(t.toString())

l.log()
