import sys
import os

glabels = []
verbose = False

# available command
# name | code | ctype | args
cmds = {
# binary
"AND": {"COP": 0, "TP": 0, "ARGS": 2},
"OR": {"COP": 1, "TP": 0, "ARGS": 2},
"XOR": {"COP": 2, "TP": 0, "ARGS": 2},
"MUL": {"COP": 3, "TP": 0, "ARGS": 2},
"ADD": {"COP": 4, "TP": 0, "ARGS": 2},
"ADDC": {"COP": 5, "TP": 0, "ARGS": 2},
"CMP": {"COP": 6, "TP": 0, "ARGS": 2},
"CMPC": {"COP": 7, "TP": 0, "ARGS": 2},
# unary
# example: NEG R1     | R1 := NEG R1
"CLR": {"COP": 8, "TP": 0, "ARGS": 1},
"INV": {"COP": 9, "TP": 0, "ARGS": 1},
"LSL": {"COP": 10, "TP": 0, "ARGS": 1},
"LSR": {"COP": 11, "TP": 0, "ARGS": 1},
"MIR": {"COP": 12, "TP": 0, "ARGS": 1},
"MOV": {"COP": 13, "TP": 0, "ARGS": 2},
"SWAB": {"COP": 14, "TP": 0, "ARGS": 1},
"SET": {"COP": 15, "TP": 0, "ARGS": 1},
# unary2 - same as unary, but we can use different SRC and DST
# example: NEG R2, R1     | R2 := NEG R1
# some pointless operations was removed
"INV2": {"COP": 9, "TP": 0, "ARGS": 2},
"LSL2": {"COP": 10, "TP": 0, "ARGS": 2},
"LSR2": {"COP": 11, "TP": 0, "ARGS": 2},
"MIR2": {"COP": 12, "TP": 0, "ARGS": 2},
"SWAB2": {"COP": 14, "TP": 0, "ARGS": 2},
# jump
"JZ": {"COP": 0, "TP": 1, "ARGS": 1},
"JNZ": {"COP": 1, "TP": 1, "ARGS": 1},
"JE": {"COP": 2, "TP": 1, "ARGS": 1},
"JG": {"COP": 3, "TP": 1, "ARGS": 1},
"JL": {"COP": 4, "TP": 1, "ARGS": 1},
"JC": {"COP": 5, "TP": 1, "ARGS": 1},
"JNC": {"COP": 6, "TP": 1, "ARGS": 1},
"JS": {"COP": 7, "TP": 1, "ARGS": 1},
"JMP": {"COP": 8, "TP": 1, "ARGS": 1},
"CALL": {"COP": 9, "TP": 1, "ARGS": 1},
"RET": {"COP": 10, "TP": 1, "ARGS": 0},
"IRET": {"COP": 11, "TP": 1, "ARGS": 0},
"SPE": {"COP": 12, "TP": 1, "ARGS": 0},
# control
"CLRF": {"COP": 0, "TP": 2, "ARGS": 0},
"NOP": {"COP": 1, "TP": 2, "ARGS": 0},
"DI": {"COP": 2, "TP": 2, "ARGS": 0},
"EI": {"COP": 3, "TP": 2, "ARGS": 0},
"RESET": {"COP": 4, "TP": 2, "ARGS": 0},
# transfer
"LOAD": {"COP": 0, "TP": 3, "ARGS": 1},
"STORE": {"COP": 1, "TP": 3, "ARGS": 1},
"IN": {"COP": 2, "TP": 3, "ARGS": 2},
"OUT": {"COP": 3, "TP": 3, "ARGS": 2},
"XOUT": {"COP": 4, "TP": 3, "ARGS": 2},
"CFG": {"COP": 5, "TP": 3, "ARGS": 2},
}

src_regs = {
"R0": 0,
"R1": 1,
"R2": 2,
"R3": 3,
"CONST": 4,
"PIN0": 5,
"PIN1": 6,
"PORT0": 7,
}

dst_regs = {
"R0": 0,
"R1": 1,
"R2": 2,
"R3": 3,
"R4": 4,
"R5": 5,
"R6": 6,
"R7": 7,
}

src_ports = {
"PIN0": 0,
"PIN1": 1,
"PIN2": 2,
"PIN3": 3,
"PIN4": 4,
"PIN5": 5,
"PIN6": 6,
"PIN7": 7,
}

dst_ports = {
"PORT0": 0,
"PORT1": 1,
"PORT2": 2,
"PORT3": 3,
"PORT4": 4,
"PORT5": 5,
"PORT6": 6,
"PORT7": 7,
}

def to_num(val):
  res = 0
  if val.upper().find("0X") == 0 and len(val) > 2:
    val = val[2:]
    res = int(val, 16)
  elif val.find("0") == 0 and len(val) > 1:
    val = val[1:]
    res = int(val, 8)
  elif val.isdigit():
    res = int(val)
  else:
    raise ValueError
  return res

def is_num(val):
  try:
    to_num(val)
    return True
  except ValueError:
    return False

def get_num(val):
  try:
    res = to_num(val)
    if verbose:
      print("%s -> %d" % (val, res))
    return res
  except ValueError:
    if verbose:
      print("Not a valid number: %s" % val)
    return 0


class Instruction:
  name = ""
  dst = ""
  src = ""

  ctype = 0
  cop = 0
  arg_num = 0

  label = ""
  error = ""

  def __init__(self, parts):
    if len(parts) == 0:
      self.err("No instruction found in: " + text)
      return

    self.name = parts[0]
    self.dst = parts[1] if len(parts) > 1 else ""
    self.src = parts[2] if len(parts) > 2 else ""
    try:
      cmd = cmds[self.name]
    except:
      return

    if cmd["ARGS"] != len(parts) - 1:
      self.err("Error. Wait for %d args in %s" % (cmd["ARGS"], self.name))
      return

    self.ctype = cmd["TP"]
    self.cop = cmd["COP"]
    self.arg_num = cmd["ARGS"]

  def cut(self, s):
    return s if len(s) <= 5 else s[:4] + "~"

  def log(self, addr = None):
    addr_str = "%04X:" % addr if addr else "     "
    common = "%s %5s %-5s %5s" % (addr_str, self.name, self.cut(self.dst), self.cut(self.src))
    need_align = "need align" if self.need_align(addr) else ""
    if self.is_valid():
      print("%s | %2d %2d | %d | %s %s" % \
            (common, self.ctype, self.cop, self.get_size(), self.label, need_align))
    else:
      print("%s |  -  - | 0 | %s" % (common, self.error))
    return

  def check(self):
    return

  def is_valid(self):
    return len(self.error) == 0

  def err(self, e):
    if self.error:
      self.error += " / "
    self.error += e
    return

  def get_size(self):
    return 1

  def get_cmd(self):
    res = self.name
    if self.dst:
      res += " " + self.dst
    if self.src:
      res += " " + self.src
    return res

  def need_align(self, addr):
    return (self.get_size() == 2) and (addr % 2)

  def to_bin(self, val, dig):
    fmt = '0' + str(dig) + 'b'
    return format(val, fmt)

  def out(self, code):
    print("     " + self.to_bin(code, 12))
    return

  def base_mcode(self):
    res = self.ctype << 10
    res |= self.cop
    return res

  def mcode1(self):
    return self.base_mcode()

  def mcode2(self):
    return 0

  def make_command(self, addr):
    self.out(self.mcode1())
    if self.get_size() == 2:
      self.out(self.mcode1())

class ArithmInstruction(Instruction):
  def __init__(self, parts):
    super().__init__(parts)
    if self.arg_num > 0:
      if self.dst not in dst_regs:
        self.err("Unknown register %s in '%s'" % (self.dst, self.get_cmd()))
        self.err("Plz use this registers: %s" % (" ".join(dst_regs)))
      if self.arg_num == 1 and not self.src:  # unary command with 1 arg
        if self.dst not in src_regs:
          self.err("Plz use this registers R0, R1, R2, R3 or use cmd with suffix 2")

    if self.arg_num > 1:
      if self.src in src_regs or is_num(self.src):
        # src is ok
        if is_num(self.src) and get_num(self.src) > 255:
          self.err("Too big value %s in '%s'" % (self.src, self.get_cmd()))
      elif self.src not in src_regs:
        self.err("Unknown register %s in '%s'" % (self.src, self.get_cmd()))
        self.err(" Plz use this registers: %s" % (" ".join(src_regs)))
      elif not is_num(src):
        self.err("Unknown value %s in '%s'" % (self.src, self.get_cmd()))

  def get_size(self):
    if is_num(self.src):
      return 2
    else:
      return 1

  def mcode1(self):
    dst_val = dst_regs[self.dst]
    if self.arg_num == 2:
      src_val = src_regs["CONST" if is_num(self.src) else self.src]
    else:  # default arg for unary instruction
      src_val = dst_val
    res = self.base_mcode()
    res |= dst_val << 7
    res |= src_val << 4
    return res

  def mcode2(self):
    if is_num(self.src):
      return get_num(self.src)
    return 0

class JumpInstruction(Instruction):
  def __init__(self, parts):
    super().__init__(parts)
    if self.arg_num > 0:
      if is_num(self.dst) and get_num(self.dst) > 65535:
        self.set_err("Too big address %s in '%s'" % (self.dst, self.get_cmd()))

  def check(self):
    if self.arg_num == 1:
      if not is_num(self.dst) and self.dst not in glabels:
        self.err("Unknown label %s in '%s'" % (self.dst, self.get_cmd()))
        self.err("Plz use address or label")
        return False
    return True

  def get_size(self):
    if self.name == "RET" or self.name == "IRET" or self.name == "SPE":
      return 1
    else:
      return 2  # cmd + address constant

  def target_addr(self):
    return get_num(self.dst) if is_num(self.dst) else glabels[self.dst]

  def mcode1(self):
    res = self.base_mcode()
    if self.arg_num == 1:
      res |= (self.target_addr() & 0xF000) >> 6
    return res

  def mcode2(self):
    if self.arg_num == 1:
      return self.target_addr() & 0x0FFF
    else:
      return 0

class ControlInstruction(Instruction):
  def __init__(self, parts):
    super().__init__(parts)

  def get_size(self):
    return 1

class TransferInstruction(Instruction):
  def __init__(self, parts):
    super().__init__(parts)
    if self.name == "LOAD":
      if self.dst not in dst_regs:
        self.err("Load command require DST register. Here: %s" % (self.get_cmd()))
    elif self.name == "STORE":  # STORE cmd has only one argument. It's left and dst
      if self.dst not in src_regs: # but we should use src regs
        self.err("Store command require SRC register. Here: %s" % (self.get_cmd()))
    elif self.name == "CFG":
      if is_num(self.src):
        self.err("CFG command use const as port address, so you should use only r0-r3, PORT0, PIN0, PIN1 as source")
      if self.src not in src_regs:
        self.err("Unknown register %s in '%s'" % (self.src, self.get_cmd()))
        self.err("Plz use this registers: %s" % (" ".join(src_regs)))

  def get_size(self):
    if self.name == "LOAD" or self.name == "STORE" or self.name == "IN":
      return 1
    elif self.name == "CFG":
      return 2
    elif self.name == "OUT" or self.name == "XOUT":
      if is_num(self.src):
        return 2
      else:
        return 1
    else:
      return 1

  def mcode1(self):
    res = self.base_mcode()
    if self.name == "LOAD":
      res |= dst_regs[self.dst] << 7
    elif self.name == "STORE":
      res |= src_regs[self.dst] << 4
    elif self.name == "OUT" or self.name == "XOUT":
      src_reg = src_regs["CONST" if is_num(self.src) else self.src]
      res |= src_reg << 4
      res |= dst_ports[self.dst] << 7
    elif self.name == "CFG":
      res |= src_regs[self.src] << 4
    return res

  def mcode2(self):
    if self.name == "OUT" or self.name == "XOUT":
      return get_num(self.src) & 0xFF  # OUT PORT0, 20
    if self.name == "CFG":
      return get_num(self.dst)  # CFG 20, R0
    else:
      return 0

class UnknownInstruction(Instruction):
  def __init__(self, parts):
    super().__init__(parts)
    self.ctype = -1
    self.cop = 0
    self.err("Error. Unknown command: " + self.name)

  def make_command(self, addr):
    return

def CreateInstruction(parts):
  ctype = -1
  try:
    cmd = cmds[parts[0]]
    ctype = cmd["TP"]
  except KeyError:
    pass

  if ctype == 0:
    return ArithmInstruction(parts)
  elif ctype == 1:
    return JumpInstruction(parts)
  elif ctype == 2:
    return ControlInstruction(parts)
  elif ctype == 3:
    return TransferInstruction(parts)
  else:
    return UnknownInstruction(parts)

def read_and_prepare(fname):
  res = []
  with open(fname) as f:
    lines = f.readlines()
    for l in lines:
      pos = l.find(';')
      if pos != -1:  # remove comments
        l = l[:pos]
      l = l.strip()  # remove spaces
      l = l.upper()
      pos = l.find(':')
      if pos != -1: # split comments into two lines
        label = l[:pos+1]
        res.append(label)
        l = l[pos+1:].strip()
      if len(l) > 0:
        l = l.replace(',', ' ')
        res.append(l)
  return res

def extract_labels_and_code(lines):
  res = []
  if lines[-1].find(':') != -1:
    print("Error. Labels in last line is not allowed.")
    return res
  for idx, line in enumerate(lines):
    if idx + 1 < len(lines) and \
       line.find(':') != -1 and \
       lines[idx + 1].find(':') != -1:
      print("Error. Only one label per code line allowed. See %s" % line)
      return res

  last_label = ""
  for line in lines:
    if line.find(':') != -1:
      label = line[0:-1]  # remove colon
      if label in glabels:
        print("Error. Label %s already exist." % label)
      else:
        last_label = label
    elif len(line) > 0:
      i = CreateInstruction(line.split())
      if len(last_label):
        i.label = last_label
        glabels.append(last_label)
        last_label = ""
      res.append(i)

  return res

def fix_alignment(instructions):
  res = []
  addr = 0
  for i in instructions:
    if i.need_align(addr):
      res.append(CreateInstruction(["NOP"]))
      addr +=1
      if i.need_align(addr):
        print("ASSEMBLER ERROR! HALT!!")
        return
    addr += i.get_size()
    res.append(i)
  return res

def calc_labels_addr(instructions):
  res = {}
  addr = 0
  for i in instructions:
    if i.label:
      res[i.label] = addr
    addr += i.get_size()
  return res

def assemble(instructions):
  print("")
  print("Parsed commands:")
  print("ADDR TP      COP")
  addr = 0
  for i in instructions:
    i.make_command(addr)
    i.log(addr)
    addr += i.get_size()

def asm(fname):
  print("Assembling: " + fname)
  if not os.path.isfile(fname):
    print("Error. File not exist.")
    return

  lines = read_and_prepare(fname)
  if len(lines) == 0:
    print("No useful code in file!")
    return

  instructions = extract_labels_and_code(lines)
  global glabels
  instructions = fix_alignment(instructions)
  glabels = calc_labels_addr(instructions)
  addr = 0
  for i in instructions:
    i.check()
    i.log(addr)
    addr += i.get_size()

  print("")
  for l in glabels:
    print("%04X %s" % (glabels[l], l))

  code = assemble(instructions)

  #print("Machine code:")
  #addr = 0
  #for b in res_bin:
  #  print("%04X %s" %(addr, b))
  #  addr += 1

def main():
  if __name__ == "__main__":
    if len(sys.argv) < 2:
      print("To use type:\nasm.py your_source.asm\n")
      return
    if len(sys.argv) == 3:
      if sys.argv[2] == "-v":
        verbose = True
    asm(sys.argv[1])

main()
