import sys
import os

from cpu import *

gmacro = {}
glabels = []
verbose = False
have_errors = False

machine_code = []

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
    addr_str = "%04X:" % addr if addr != None else "     "
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
    print("     %s   %03X" % (self.to_bin(code, 12), code))
    machine_code.append(code)
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
      self.out(self.mcode2())

class ArithmInstruction(Instruction):
  def __init__(self, parts):
    super().__init__(parts)
    if self.arg_num > 0:
      if self.dst not in dst_regs:
        self.err("Unknown register %s in '%s'" % (self.dst, self.get_cmd()))
        self.err("Plz use this registers: %s" % (" ".join(dst_regs)))
      if self.arg_num == 1 and not self.src:  # unary command with 1 arg
        if self.name == "CLR" or self.name == "SET":
          self.src = "R0"
        elif self.dst not in src_regs:
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
    elif self.name == "CLR" or self.name == "SET":
      src_val = src_regs[self.src]  # will use r0 in CLR/SET, cause it let us do clr r7
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
    if self.name == "RET" or self.name == "IRET" or self.name == "SIE" or self.name == "SIZ":
      return 1
    else:
      return 2  # cmd + address constant

  def target_addr(self):
    if self.dst in glabels:
      return glabels[self.dst]
    if is_num(self.dst):
      return get_num(self.dst)
    self.err("Unknown target %s" % self.dst)
    return 0

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
      if self.dst not in src_regs and not is_num(self.dst): # but we should use src regs
        self.err("Store command require SRC register. Here: %s" % (self.get_cmd()))
    elif self.name == "CFG":
      if is_num(self.src):
        self.err("CFG command use const as port address, so you should use only r0-r3, PORT0, PIN0, PIN1 as source")
      if self.src not in src_regs:
        self.err("Unknown register %s in '%s'" % (self.src, self.get_cmd()))
        self.err("Plz use this registers: %s" % (" ".join(src_regs)))
    elif self.name == "IN":
      if self.dst not in dst_regs:
        self.err("IN command require DST register: %s" % (" ".join(src_regs)))
      if self.src not in src_ports:
        self.err("IN command require SRC ports: %s" % (" ".join(src_ports)))
    elif self.name == "OUT" or self.name == "XOUT":
      if self.dst not in dst_ports:
        self.err("OUT command require DST ports: %s" % (" ".join(dst_ports)))
      if self.src not in src_regs and not is_num(self.src):
        self.err("OUT command require SRC register: %s" % (" ".join(src_regs)))

  def get_size(self):
    if self.name == "LOAD" or self.name == "IN":
      return 1
    elif self.name == "STORE":
      if is_num(self.dst): # see comments above
        return 2
      else:
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
      src_reg = src_regs["CONST" if is_num(self.dst) else self.dst]
      res |= src_reg << 4
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
    if self.name == "STORE":
      return get_num(self.dst) & 0xFF
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

  global gmacro
  res2 = []
  for l in res:
    if l.find(".DEF") == 0:
      def_len = len(".DEF")
      t = l[def_len:].strip()
      p = t.split("=")
      if len(p) != 2:
        print("Error in macro: %s" % l)
        have_errors = True
        continue
      gmacro[p[0]] = p[1]
    else:
      res2.append(l)

  return res2

def extract_labels_and_code(lines):
  res = []
  global have_errors
  if lines[-1].find(':') != -1:
    print("Error. Labels in last line is not allowed.")
    have_errors = True
    return res
  for idx, line in enumerate(lines):
    if idx + 1 < len(lines) and \
       line.find(':') != -1 and \
       lines[idx + 1].find(':') != -1:
      print("Error. Only one label per code line allowed. See %s" % line)
      have_errors = True
      return res

  last_label = ""
  for line in lines:
    if line.find(':') != -1:
      label = line[0:-1]  # remove colon
      if label in glabels:
        print("Error. Label %s already exist." % label)
        have_errors = True
      else:
        last_label = label
    elif len(line) > 0:
      p = line.split()
      for i, v in enumerate(p):
        if v in gmacro:
          p[i] = gmacro[v]

      i = CreateInstruction(p)
      if len(last_label):
        i.label = last_label
        glabels.append(last_label)
        last_label = ""
      res.append(i)

  return res

def fix_alignment(instructions):
  res = []
  addr = 0
  global have_errors
  for i in instructions:
    if i.need_align(addr):
      res.append(CreateInstruction(["NOP"]))
      addr +=1
      if i.need_align(addr):
        print("ASSEMBLER ERROR! HALT!!")
        have_errors = True
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
  print("ADDR TP       COP")
  addr = 0
  for i in instructions:
    i.make_command(addr)
    i.log(addr)
    addr += i.get_size()
    print("")
  return

def print_instructions(instructions):
  addr = 0
  for i in instructions:
    i.check()
    i.log(addr)
    addr += i.get_size()
  return

def check_errors(instructions):
  global have_errors
  for i in instructions:
    i.check()
    if not i.is_valid():
      have_errors = True
  return

def print_dump(fname):
  print("Machine code:")
  cnt = len(machine_code)
  if cnt == 0:
    print("No code found")
    return

  res = ""
  for i in range(0, cnt & 0xFFFE, 2):
    res += "%03X %03X\n" % (machine_code[i], machine_code[i+1])
  if cnt & 1: # real device will have 3 ROM by 8 bit so we always have even word count
    res += "%03X 801\n" % machine_code[-1]
  print(res)

  with open(fname + ".bin", "w") as f:
    f.write(res)

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
  check_errors(instructions)
  print_instructions(instructions)

  if have_errors:
    print("\nCan't assemble.There are some errors.\n")
    return

  print("")
  for l in glabels:
    print("%04X %s" % (glabels[l], l))

  assemble(instructions)
  print_dump(fname)

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
