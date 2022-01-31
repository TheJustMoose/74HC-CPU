import sys
import os

glabels = []

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
"CLR": {"COP": 8, "TP": 0, "ARGS": 1},
"NEG": {"COP": 9, "TP": 0, "ARGS": 1},
"LSL": {"COP": 10, "TP": 0, "ARGS": 1},
"LSR": {"COP": 11, "TP": 0, "ARGS": 1},
"MIR": {"COP": 12, "TP": 0, "ARGS": 1},
"MOV": {"COP": 13, "TP": 0, "ARGS": 2},
"SWAB": {"COP": 14, "TP": 0, "ARGS": 1},
"SET": {"COP": 15, "TP": 0, "ARGS": 1},
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

def to_num(val):
  res = 0
  if val.find("0X") == 0 and len(val) > 2:
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
    print("%s -> %d" % (val, res))
    return res
  except ValueError:
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

  def is_valid(self):
    return len(self.error) == 0

  def err(self, e):
    if self.error:
      self.error += " / "
    self.error += e

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
    print("     " + to_bin(code, 12))

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

  def make_command(self):
    res = 0
    res |= ctype << 10
    res |= dst << 7
    res |= src << 4
    res |= cop
    out(res)

class JumpInstruction(Instruction):
  def __init__(self, parts):
    super().__init__(parts)
    if self.arg_num > 0:
      if is_num(self.dst) and get_num(self.dst) > 65535:
        self.set_err("Too big address %s in '%s'" % (self.dst, self.get_cmd()))

  def is_valid(self):
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

class ControlInstruction(Instruction):
  def __init__(self, parts):
    super().__init__(parts)

  def get_size(self):
    return 1

class TransferInstruction(Instruction):
  def __init__(self, parts):
    super().__init__(parts)
    if self.name == "LOAD" or self.name == "STORE":
      if self.dst not in dst_regs:
        self.err("Memory command require register. Here: %s" % (get_cmd()))
    elif self.name == "CFG":
      if self.src not in src_regs:
        self.err("Unknown register %s in '%s'" % (src, get_cmd()))
        self.err("Plz use this registers: %s" % (" ".join(src_regs)))

  def get_size(self):
    if self.name == "LOAD" or self.name == "STORE" or self.name == "IN":
      return 1
    elif self.name == "CFG":
      return 2
    elif is_num(self.src):  # check args for OUT|XOUT
      return 2
    else:
      return 1

class UnknownInstruction(Instruction):
  def __init__(self, parts):
    super().__init__(parts)
    self.err("Error. Unknown command: " + self.name)

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

def make_jump(ctype, cop, addr):
  res = 0
  res |= ctype << 10
  res |= (addr & 0xF000) >> 6
  res |= cop
  out(res)
  out(addr & 0x0FFF)

def assemble():
  print("")
  print("Parsed commands:")
  print("ADDR TP      COP")
  addr = 0
  for p in parsed_cmd:
    cmd = cmds[p[0]]
    ctype = cmd["TP"]
    cop = cmd["COP"]
    args = cmd["ARGS"]
    print("%04X %s      %s ; %s %d" % (addr, to_bin(ctype, 2), to_bin(cop, 4), p, cmd_size(p)))
    if ctype == 0:
      if args == 2:
        dst = p[1]
        src = p[2]
        if is_num(src):
          make_command(ctype, cop, dst_regs[dst], src_regs["CONST"])
          out(get_num(src))
        else:
          make_command(ctype, cop, dst_regs[dst], src_regs[src])
        print("     CTdstSRCcope")
    elif ctype == 1:
      if args == 1:
        param = p[1]
        tgt_addr = get_num(param) if is_num(param) else label_to_addr[param]
        make_jump(ctype, cop, tgt_addr)
        print("     CTcnst..cope")
      else:
        make_command(ctype, cop, 0, 0)
        print("     CTcnst..cope")
    else:
      make_command(ctype, cop, 0, 0)

    #machine_code = make_command(cmd["TP"], cmd["COP"], 0, 0)
    #print("     " + to_bin(machine_code, 12))
    addr += cmd_size(p)

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
    i.log(addr)
    addr += i.get_size()

  for l in glabels:
    print("%04X %s" % (glabels[l], l))

  #assemble()

  #print("Machine code:")
  #addr = 0
  #for b in res_bin:
  #  print("%04X %s" %(addr, b))
  #  addr += 1

def main():
  if len(sys.argv) != 2:
    print("To use type:\nasm.py your_source.asm\n")
    return
  asm(sys.argv[1])

main()
