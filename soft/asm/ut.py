from asm import *

def A(l, r):
  if l != r:
    print("should be equal: ")
    print(l)
    print(r)

def T(p, t):
  i = CreateInstruction(p)
  if i.ctype != t:
    print("Instruction %s should have type: %d" % (p[0], t))

A(to_num("0"), 0)
A(to_num("1"), 1)
A(to_num("255"), 255)
A(to_num("65535"), 65535)
A(to_num("1000000"), 1000000)

A(to_num("01"), 1)
A(to_num("010"), 8)
A(to_num("0177777"), 65535)

A(to_num("0X1"), 1)
A(to_num("0X10"), 16)
A(to_num("0XFFFF"), 65535)

A(is_num("123"), True)
A(is_num("abc"), False)

A(get_num("123"), 123)
A(get_num("abc"), 0)

T(["MOV", "R1", "R2"], 0)
T(["ADD", "R1", "R2"], 0)
T(["CLR", "R1"], 0)
T(["NEG", "R1"], 0)

T(["JZ", "R1"], 1)

T(["CLRF"], 2)
T(["LOAD", "R1"], 3)

#i.make_command(0)

print("Finished")
