import sys
import os

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

class Instruction:
  name = ""
  dst = ""
  src = ""

  ctype = 0
  cop = 0
  label = ""

  error = ""

  def __init__(self, parts):
    if len(parts) == 0:
      self.error = "No instruction found in: " + text
      return
    self.name = parts[0]
    try:
      cmd = cmds[self.name]
    except KeyError:
      self.error = "Error. Unknown command: " + self.name
      return

    if cmd["ARGS"] != len(parts) - 1:
      self.error = "Error. Wait for %d args in %s" % (cmd["ARGS"], self.name)
      return

    self.ctype = cmd["TP"]
    self.cop = cmd["COP"]
    self.dst = parts[1] if len(parts) > 1 else ""
    self.src = parts[2] if len(parts) > 2 else ""

  def cut(self, s):
    return s if len(s) <= 5 else s[:4] + "~"

  def log(self):
    common = "%5s %-5s %5s" % (self.name, self.cut(self.dst), self.cut(self.src))
    if self.error:
      print("%s | -  -  | %s" % (common, self.error))
    else:
      print("%s | %2d %2d | %s" % (common, self.ctype, self.cop, self.label))
    return

  def is_valid():
    return len(self.error) == 0

  def get_size():
    return 1

class ArithmInstruction(Instruction):
  def __init__(self, parts):
    super().__init__(parts)

  def log(self):
    super().log()

def CreateInstruction(parts):
  ctype = -1
  try:
    cmd = cmds[parts[0]]
    ctype = cmd["TP"]
  except KeyError:
    #print("Key error: " + parts[0])
    pass

  if ctype == 0:
    return ArithmInstruction(parts)
  else:
    return Instruction(parts)


label_to_line = {}
label_to_addr = {}
line_to_label = {}
parsed_cmd = []
have_errors = False
res_bin = []

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

def cmd_ok(parts):
  name = parts[0]
  dst = parts[1] if len(parts) > 1 else ""
  src = parts[2] if len(parts) > 2 else ""

  cmd = cmds[name]
  args = cmd["ARGS"]
  ct = cmd["TP"]  # command type
  if len(parts) - 1 != args:
    print("Error. Wait for %d args in %s" % (args, name))
    return False

  if ct == 0:  # arithm
    if args > 0:
      if dst not in dst_regs:
        print("Unknown register %s in '%s'" % (dst, " ".join(parts)))
        print(" Plz use this registers: %s" % (" ".join(dst_regs)))
        return False
      if args == 1 and len(parts) == 2:  # unary command with 1 arg
        if dst not in src_regs:
          print("Plz use this registers R0, R1, R2, R3 or use cmd with suffix 2")
          return False
    if args > 1:
      if src in src_regs or is_num(src):
        # src is ok
        if is_num(src) and get_num(src) > 255:
          print("Too big value %s in '%s'" % (src, " ".join(parts)))
          return False
      elif src not in src_regs:
        print("Unknown register %s in '%s'" % (src, " ".join(parts)))
        print(" Plz use this registers: %s" % (" ".join(src_regs)))
        return False
      elif not is_num(src):
        print("Unknown value %s in '%s'" % (src, " ".join(parts)))
        return False
  elif ct == 1:  # jumps
    if args > 0:
      if dst in label_to_line or is_num(dst):
        if is_num(dst) and get_num(dst) > 65535:
          print("Too big address %s in '%s'" % (dst, " ".join(parts)))
          return False
      elif dst not in label_to_line:
        print("Unknown label %s in '%s'" % (dst, " ".join(parts)))
        print(" Plz use address or label")
        return False
      elif not is_num(dst):
        print("Unknown value %s in '%s'" % (dst, " ".join(parts)))
        return False
  elif ct == 3:  # transfer
    if name == "LOAD" or name == "STORE":
      if dst not in dst_regs:
        print("Memory command require register. Here: %s" % (" ".join(parts)))

  return True

def cmd_size(parts):
  name = parts[0]
  dst = parts[1] if len(parts) > 1 else ""
  src = parts[2] if len(parts) > 2 else ""

  cmd = cmds[name]
  ct = cmd["TP"]

  if ct == 0:  # arithm
    if is_num(src):
      return 2
    else:
      return 1
  elif ct == 1:  # jump
    if name == "RET" or name == "IRET" or name == "SPE":
      return 1
    else:
      return 2  # cmd + address constant
  elif ct == 2:  # control
    return 1
  elif ct == 3:  # transfer
    if name == "LOAD" or name == "STORE" or name == "IN":
      return 1
    elif name == "CFG":
      return 2
    elif is_num(src):  # check args for OUT|XOUT
      return 2
    else:
      return 1

  return 0

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
      if label in label_to_line:
        print("Error. Label %s already exist." % label)
      else:
        last_label = label
    elif len(line) > 0:
      i = CreateInstruction(line.split())
      if len(last_label):
        i.label = last_label
        last_label = ""
      res.append(i)

  return res

def calc_addr():
  addr = 0
  for idx, p in enumerate(parsed_cmd):
    if idx in line_to_label:
      lab = line_to_label[idx]
      label_to_addr[lab] = addr
    addr += cmd_size(p)

def first(lines):
  for l in lines:
    p = l.split()
    if p[0] not in cmds:
      print("Error. Unknown command: " + p[0])
    elif cmd_ok(p):
      parsed_cmd.append(p)
    else:
      have_errors = True
  return

def second():
  line_index = 0
  for c in parsed_cmd:
    if line_index in line_to_label:
      lab = line_to_label[line_index]
      print(lab, c)
    else:
      print(c)
    line_index += 1
  return

def to_bin(val, dig):
  fmt = '0' + str(dig) + 'b'
  return format(val, fmt)

def out(code):
  print("     " + to_bin(code, 12))
  res_bin.append(to_bin(code, 12))
  return

def make_command(ctype, cop, dst, src):
  res = 0
  res |= ctype << 10
  res |= dst << 7
  res |= src << 4
  res |= cop
  out(res)

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
  for i in instructions:
    i.log()

  #first(lines)
  #calc_addr()
  #print("label_to_addr: ", label_to_addr)
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

  #print("labels: ", label_to_line)
  #print("line_to_label: ", line_to_label)

main()
