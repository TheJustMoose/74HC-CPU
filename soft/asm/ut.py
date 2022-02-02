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

def V(p):
  i = CreateInstruction(p)
  i.check()
  if not i.is_valid():
    print("Instruction %s is not valid. Error:\n%s" % (p[0], i.error))

def NV(p):
  i = CreateInstruction(p)
  i.check()
  if i.is_valid():
    print("Instruction %s SHOULD NOT be valid." % (p[0]))

def CLR(v):
  res = ""
  for i in v:
    if i == '0' or i == '1':
      res += i
  return res

def B2(v):
  return int(CLR(v), 2)

def S(p, s):
  i = CreateInstruction(p)
  if i.get_size() != s:
    print("Instruction %s should have size %d" % (p[0], s))

def M1(p, m1):
  i = CreateInstruction(p)
  if i.mcode1() != B2(m1):
    print("%s machine word 1 should have val: %s" % (p[0], m1))
    print("But it have: {0:12b}".format(i.mcode1()))

def M2(p, m2):
  i = CreateInstruction(p)
  if i.mcode2() != B2(m2):
    print("%s machine word 2 should have val: %s" % (p[0], m2))
    print("But it have: {0:8b}".format(i.mcode2()))

A(CLR("0"), "0")
A(CLR("1010"), "1010")
A(CLR("a"), "")
A(CLR("|001|1000.1000|*"), "00110001000")

A(B2("1111"), 15)
A(B2("|001|1000.1000|*"), 392)

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
A(to_num("0xFFFF"), 65535)

A(is_num("123"), True)
A(is_num("abc"), False)

A(get_num("123"), 123)
A(get_num("abc"), 0)

T(["UNK", "R1"], -1)

T(["MOV", "R1", "R2"], 0)
T(["ADD", "R1", "R2"], 0)
T(["CLR", "R1"], 0)
T(["INV", "R1"], 0)

T(["INV", "R3"], 0)
V(["INV", "R3"])

T(["INV2", "R1", "R2"], 0)

T(["JZ", "R1"], 1)

# have to use CAPS, see asm.py
T(["JMP", "M1"], 1)
glabels.append("M1")
V(["JMP", "M1"])

T(["CALL", "0xFFFF"], 1)
V(["CALL", "0xFFFF"])

T(["CLRF"], 2)
T(["LOAD", "R1"], 3)

# arithmetic operation
M1(["AND", "R0", "R0"], "00|000|000|0000")
V(["AND", "R0", "R0"])
M1(["AND", "R0", "R1"], "00|000|001|0000")
M1(["AND", "R1", "R0"], "00|001|000|0000")
M1(["AND", "R7", "R0"], "00|111|000|0000")

M1(["AND", "R4", "99"], "00|100|100|0000")
M2(["AND", "R4", "99"], "0110.0011")

M1(["CMP", "R1", "16"], "00|001|100|0110")
M2(["CMP", "R2", "16"], "0001|0000")

M1(["CLR", "R0"], "00|000|000|1000")
M1(["CLR", "R7"], "00|111|111|1000")

M1(["INV", "R3"], "00|011|011|1001")
M1(["INV2", "R5", "R3"], "00|101|011|1001")

M1(["MOV", "R7", "R0"], "00|111|000|1101")
V(["MOV", "R7", "R0"])

M1(["MOV", "R0", "R1"], "00|000|001|1101")
V(["MOV", "R0", "R1"])

# only R0-R3 allowed in this instructions
NV(["INV", "R5"])
V(["INV", "R3"])
# but dst may be R0-R7
NV(["INV", "R5", "R3"])
V(["INV2", "R5", "R3"])

# jump operation
M1(["JZ", "100"], "01|000000|0000")
M2(["JZ", "100"], "0000|0110|0100")

M1(["JNZ", "100"], "01|000000|0001")
M2(["JNZ", "100"], "0000|0110|0100")

M1(["JE", "200"], "01|000000|0010")
M2(["JE", "200"], "0000|1100|1000")

M1(["JG", "200"], "01|000000|0011")
M1(["JL", "200"], "01|000000|0100")
M1(["JC", "200"], "01|000000|0101")
M1(["JNC", "200"], "01|000000|0110")
M1(["JS", "200"], "01|000000|0111")

M1(["JMP", "100"], "01|000000|1000")
M2(["JMP", "100"], "0000|0110|0100")

M1(["JMP", "0xAAAA"], "01|1010|00|1000")
M2(["JMP", "0xAAAA"], "1010|1010|1010")
S(["JMP", "0xAAAA"], 2)

M1(["CALL", "0xAAAA"], "01|1010|00|1001")
M2(["CALL", "0xAAAA"], "1010|1010|1010")
S(["CALL", "0xAAAA"], 2)

M1(["RET"], "01|000000|1010")
S(["RET"], 1)
M1(["IRET"], "01|000000|1011")

# control operation
M1(["CLRF"], "10|000000|0000")
M1(["NOP"], "10|000000|0001")
S(["NOP"], 1)
M1(["DI"], "10|000000|0010")
M1(["EI"], "10|000000|0011")
M1(["RESET"], "10|000000|0100")

# transfer operation
M1(["LOAD", "R0"], "11|000000|0000")
S(["LOAD", "R0"], 1)
M1(["LOAD", "R5"], "11|101000|0000")

M1(["STORE", "R0"], "11|000000|0001")
S(["STORE", "R0"], 1)

M1(["STORE", "R3"], "11|000011|0001")

M1(["STORE", "10"], "11|000100|0001")
S(["STORE", "10"], 2)
M2(["STORE", "10"], "0000|0000|1010")

M1(["IN", "R0", "PIN0"], "11|000000|0010")
S(["IN", "R0", "PIN0"], 1)

M1(["OUT", "PORT1", "R0"], "11|001000|0011")
S(["OUT", "PORT1", "R0"], 1)

M1(["OUT", "PORT7", "R0"], "11|111000|0011")
S(["OUT", "PORT7", "R0"], 1)

M1(["OUT", "PORT5", "PIN0"], "11|101101|0011")
S(["OUT", "PORT5", "PIN0"], 1)

M1(["OUT", "PORT1", "64"], "11|001100|0011")
M2(["OUT", "PORT1", "64"], "0000|0100|0000")
S(["OUT", "PORT1", "64"], 2)

M1(["XOUT", "PORT2", "R0"], "11|010000|0100")
S(["XOUT", "PORT2", "R0"], 1)

M1(["XOUT", "PORT2", "255"], "11|010100|0100")
S(["XOUT", "PORT2", "255"], 2)

M1(["CFG", "1000", "R0"], "11|000000|0101")
M2(["CFG", "1000", "R0"], "0011|1110|1000")
S(["CFG", "1000", "R0"], 2)

print("Finished")
