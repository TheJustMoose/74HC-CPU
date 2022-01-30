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
# const have index 4
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

labels = {}
label_of_line = {}
parsed_cmd = []
have_errors = False

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
      if dst in labels or is_num(dst):
        if is_num(dst) and get_num(dst) > 65535:
          print("Too big address %s in '%s'" % (dst, " ".join(parts)))
          return False
      elif dst not in labels:
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

def extract_labels(lines):
  res = []
  if lines[-1].find(':') != -1:
    print("Error. Labels in last line is not allowed.")
    return res
  for idx, l in enumerate(lines):
    if idx + 1 < len(lines) and \
       l.find(':') != -1 and \
       lines[idx + 1].find(':') != -1:
      print("Error. Only one label per code line allowed. See %s" % l)
      return res

  for idx, l in enumerate(lines):
    if idx + 1 < len(lines) and \
       l.find(':') != -1:
      label = l[0:-1]  # remove colon
      if label in labels:
        print("Error. Label %s already exist." % label)
      else:
        # use index of CLEARED code line because label will be removed from code
        labels[label] = len(res)
        label_of_line[len(res)] = label
    else:
      res.append(l)

  return res

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
    if line_index in label_of_line:
      l = label_of_line[line_index]
      print(l, c)
    else:
      print(c)
    line_index += 1
  return

def asm(fname):
  print("Assembling: " + fname)
  if not os.path.isfile(fname):
    print("Error. File not exist.")
    return

  lines = read_and_prepare(fname)
  if len(lines) == 0:
    print("No useful code in file!")
    return

  lines = extract_labels(lines)
  for idx, l in enumerate(lines):
    if idx in label_of_line:
      print("%d: %s # %s" % (idx, l, label_of_line[idx]))
    else:
      print("%d: %s" % (idx, l))
  first(lines)

  print("")
  print("Parsed commands:")
  for p in parsed_cmd:
    print(p, cmd_size(p))

def main():
  if len(sys.argv) != 2:
    print("To use type:\nasm.py your_source.asm\n")
    return
  asm(sys.argv[1])

  print("")
  print("labels: ", labels)
  print("label_of_line: ", label_of_line)

main()
