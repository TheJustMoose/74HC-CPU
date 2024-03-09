///////////////////////////////////////////////////////////////////////////////
/*

Ассемблер для моего 74HCPU под новую систему команд:

|---------------------------------------------|
|   HIGH BYTE   |    LOW BYTE   |  HIGH BYTE  |
|   4   +  3 + 1 + 3  +    5    = 16  (again) |
|0 1 2 3 4 5 6 7 8 9 A B C D E F|        Flags|
|---------------------------------------------|
|   ADD | DST |C| SRC |-|Z|z|I|i| 00 0000  *  | ADDI  R0, 1    // INC R0;
|  ADDC | DST |C| SRC |F|Z|z|I|i| 01 0001  *  | ADDCI R1, 0    // INCC R1;    // бит F нужен для команд -INC-, -DEC-, SUB, -INV-, NEG
|   AND | DST |C| SRC |-|Z|z|I|i| 02 0010  *  | ANDI R2, 0x0F  // здесь есть свободный бит, и вместо F туда можно положить S[WAP] или S[HIFT]
|    OR | DST |C| SRC |-|Z|z|I|i| 03 0011  *  | ORI R3, 2      // в любом случае, сдвиг старшего нибла на место младшего кажется полезным
|   XOR | DST |C| SRC |-|Z|z|I|i| 04 0100  *  | XORI R4, 4     // кстати, в этом случае можно ещё и от команды SWAP избавиться
|   MUL | DST |C| SRC |-|Z|z|I|i| 05 0101  *  | MULI R6, 10    // R7:R6 := R6*10
|   UNO | DST |0|-|TYP|F|-|-|-|-| 06 0110  *  | унарные команды не используют операнд SRC, поэтому нельзя использовать инверторы и отдельные нибблы
|   MOV | DST |C| SRC |*|Z|z|I|i| 07 0111  -  | MOVI R5, 5     // LDI R5, 5       // * - можно использовать, чтобы пихать адрес в SPL/SPH (правда, только из других регистров)
|   LPM | DST |W|EXT|D|U|OFFSET4| 08 1000  -  | LPM R0, [IX]   // LPM R1, [X+1]   // LPM R1, [DX-1]  // W - читать слово (1) или байт (0)
|    LD | DST |0|EXT|D|U|OFFSET4| 09 1001  -  | LD R1, [-Y]    // LD R3, [+SP-1] ; POP R3
|    IN | DST |  PORT   |-|-|I|i| 0A 1010  -  | IN R2, PIN1    // IN R2, ~PIN1 ; инвертировать порт перед чтением
|-------------|7-8-9-A-B|-------|-------------| всё что ниже - не модифицирует регистры
|   OUT | SRC |  PORT   |O|o|X|x| 0B 1011  -  | OUT PORT0, R2  // XOUT PORT0, R2
|    ST | SRC |0|EXT|D|U|OFFSET4| 0C 1100  -  | ST [Y], R2     // ST [IX], R2     // ST [Y+2], R2   // ST [-SP], R2 ; PUSH R2
|   CMP | DST |C| SRC |-|   -   | 0D 1101  +  | CMPI R3, 10    // CMP  R0, R2
|  CMPC | DST |C| SRC |-|   -   | 0E 1110  +  | CMPCI R4, 10   // CMPC R1, R3
| BRNCH |  CALL | 8 bit OFFSET  | 0F 1111 0000| переход в +-127 команды, значение прибавляется к текущему счётчику команд
| BRNCH |   JMP | 8 bit OFFSET  | 0F 1111 0001| <- COP low nibble
| BRNCH |   RET | 8 bit +STACK  | 0F 1111 0010| на сколько байт переместить указатель стека данных, дабы пропустить запушенные параметры
| BRNCH |    JZ | 8 bit OFFSET  | 0F 1111 0011| условные переходы
| BRNCH |    JL | 8 bit OFFSET  | 0F 1111 0100|
| BRNCH |   JNE | 8 bit OFFSET  | 0F 1111 0101|
| BRNCH |    JE | 8 bit OFFSET  | 0F 1111 0110|
| BRNCH |    JG | 8 bit OFFSET  | 0F 1111 0111|
| BRNCH |    JC | 8 bit OFFSET  | 0F 1111 1000|
| BRNCH |   JNZ | 8 bit OFFSET  | 0F 1111 1001|
| BRNCH |   JNC | 8 bit OFFSET  | 0F 1111 1010| выкинуть инструкции, что реально не будут использоваться
| BRNCH |   JHC | 8 bit OFFSET  | 0F 1111 1011| вкрутить что-то вроде NJMP offset (и делать реальный переход на offset*16, к примеру)
| BRNCH |  JNHC | 8 bit OFFSET  | 0F 1111 1100|
| BRNCH |  STOP |   0000 0000   | 0F 1111 1101| отладочный стоп, чтобы можно было смотреть глазами регистры (и есть 8 бит на фантазию)
| BRNCH |AFCALL | Hi 8 bit ADDR | 0F 1111 1110| Absolute Far Call - 8 bit ADDR кладём в старшие биты и ничего не добавляем к младшим
| BRNCH |   NOP |   1111 1111   | 0F 1111 1111| NOP - хорошо бы чтоб имел код 0xFF, это позволит думать, что не прошитая память заполнена NOP-ами
|---------------------------------------------|
*/
///////////////////////////////////////////////////////////////////////////////

#include <algorithm>
#include <bitset>
#include <cctype>
#include <cstdlib>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <vector>
#include <windows.h>

#include "asm.h"

using namespace std;

///////////////////////////////////////////////////////////////////////////////

struct ARITHM {
 public:
  uint16_t cop : 4;
  uint16_t dst : 3;
  uint16_t C : 1;
  uint16_t src : 3;
  uint16_t F : 1;
  uint16_t Z : 1;
  uint16_t z : 1;
  uint16_t I : 1;
  uint16_t i : 1;
};

OP_TYPE CopToType(COP cop) {
  if (cop == cNO_OP)
    return tNO_OP;
  else if (cop >= cADD && cop <= cMUL)
    return tBINARY;
  else if (cop == cMOV || cop == cCMP || cop == cCMPC)
    return tBINARY;
  else if (cop == cUNO)
    return tUNARY;
  else if (cop == cLPM || cop == cLPMW || cop == cLD || cop == cST)
    return tMEMORY;
  else if (cop == cIN || cop == cOUT || cop == cTOGL)
    return tIO;
  else if (cop >= bCALL && cop <= bNOP)
    return tBRANCH;
  else  // I don't know when this should work
    return tNO_OP;
}

map<string, uint16_t> unary_codes {
  { "INV", 0x00 },
  { "SWAP", 0x20 },
  { "LSR", 0x40 },
  { "LSRC", 0x60 },
};

map<string, COP> cop_names {
  { "ADD", cADD}, { "ADDC", cADDC},
  { "AND", cAND}, { "OR", cOR}, { "XOR", cXOR},
  { "MUL", cMUL},
  { "INV", cUNO}, { "SWAP", cUNO}, { "LSR", cUNO}, { "LSRC", cUNO},
  { "MOV", cMOV},
  { "LPM", cLPM}, { "LPMW", cLPMW}, { "LD", cLD}, { "LOAD", cLD},
  { "IN", cIN}, { "OUT", cOUT}, { "TOGL", cTOGL},
  { "ST", cST}, { "STORE", cST},
  { "CMP", cCMP}, { "CMPC", cCMPC},
  { "CALL", bCALL},
  { "JMP", bJMP },
  { "RET", bRET },
  { "JZ", bJZ },
  { "JL", bJL },
  { "JNE", bJNE },
  { "JE", bJE },
  { "JG", bJG },
  { "JC", bJC },
  { "JNZ", bJNZ },
  { "JNC", bJNC },
  { "JHC", bJHC },
  { "JNHC", bJNHC },
  { "STOP", bSTOP },
  { "AFCALL", bAFCALL },
  { "NOP", bNOP },
};

map<string, REG> reg_names {
  { "R0", rR0 }, { "R1", rR1 }, { "R2", rR2 }, { "R3", rR3 }, { "R4", rR4 }, { "R5", rR5 }, { "R6", rR6 }, { "R7", rR7 },
// R0.L R0.H R1.L R1.H....
  { "XL", rXL}, { "XH", rXH}, { "YL", rYL}, { "YH", rYH}, { "ZL", rZL}, { "ZH", rZH}, { "SPL", rSPL}, { "SPH", rSPH},
};

map<string, PTR> ptr_names {
  { "X", rX }, { "Y", rY }, { "Z", rZ }, { "SP", rSP },
  { "XI", rXI }, { "YI", rYI }, { "ZI", rZI }, { "SPI", rSPI },
  { "XD", rXD }, { "YD", rYD }, { "ZD", rZD }, { "SPD", rSPD },
};

///////////////////////////////////////////////////////////////////////////////

string to_upper(string s) {
  std::transform(s.begin(), s.end(), s.begin(), ::toupper);
  return s;
}

// will remove leading spaces
// also remove more than one space in a row
string normalize_line(string s) {
  string res;
  bool skip_space {true};
  bool in_string {false};
  for (size_t i = 0; i < s.size(); i++) {
    if (s[i] == '"')
      in_string = !in_string;

    if (!in_string) {
      if (s[i] == ' ') {
        if (skip_space)
          continue;
        else
          skip_space = true;
      } else {
        skip_space = false;
      }
    }
    res += s[i];
  }

  return res;
}

string trim_right(string s) {
  if (s.empty())
    return {};

  int cnt {0};
  string::reverse_iterator it;
  for (it = s.rbegin(); it != s.rend(); it++)
    if (*it == ' ')
      cnt++;
    else
      break;

  if (cnt > 0)
    s.resize(s.size() - cnt);

  return s;
}

string trim_left(string s) {
  if (s.empty())
    return {};

  int cnt {0};
  string::iterator it;
  for (it = s.begin(); it != s.end(); it++)
    if (*it == ' ')
      cnt++;
    else
      break;

  if (cnt > 0)
    s = s.erase(0, cnt);

  return s;
}

string trim(string s) {
  return trim_left(trim_right(s));
}

void remove_all_spaces(string& s) {
  // try to remove all spaces
  s.erase(remove_if(s.begin(), s.end(), isspace), s.end());
}

string remove_quotes(string s) {
  if (s.size() <= 2)
    return s;
  return s.substr(1, s.size() - 2);
}

string sreplace(string where, string from, string to) {
  size_t lpos = where.find(from);
  if (lpos == string::npos)
    return where;

  string left = where.substr(0, lpos);

  string right {};
  size_t rpos = lpos + from.size();
  if (rpos < where.size())
    right = where.substr(rpos);

  return left + to + right;
}

bool StrToInt(string val, int* pout, string* err = nullptr) {
  int res = 0;
  try {
    if (val.find("0X") == 0)
      res = stoi(&val[2], nullptr, 16);
    else if (*val.rbegin() == 'h')
      res = stoi(&val[0], nullptr, 16);
    else if (val.find("0O") == 0)
      res = stoi(&val[2], nullptr, 8);
    else if (val.find("0B") == 0)
      res = stoi(&val[2], nullptr, 2);
    else {
      res = stoi(val, nullptr, 10);
    }
  } catch(std::invalid_argument& e) {
    if (err) {
      *err += e.what();
      *err += "\n";
      *err += "arg: ";
      *err += val;
    }
    return false;
  }

  if (pout)
    *pout = res;
  return true;
}

///////////////////////////////////////////////////////////////////////////////

REG CodeGen::RegFromName(string name) {
  if (name.empty())
    return rUnkReg;
  if (reg_names.find(name) != reg_names.end())
    return reg_names[name];
  else {
    err("Unknown register: " + name);
    return rUnkReg;
  }
}

PTR CodeGen::PtrFromName(string name, bool* inc = nullptr, bool* dec = nullptr) {
  if (name.empty())
    return rUnkPtr;

  PTR ptr {rUnkPtr};
  if (ptr_names.find(name) != ptr_names.end()) {
    ptr = ptr_names[name];
    if (inc)
      *inc = ptr & rInc;
    if (dec)
      *dec = ptr & rDec;
    return (PTR)(ptr & 0x0F);
  } else {
    err("Unknown pointer register: " + name);
    return rUnkPtr;
  }
}

uint16_t CodeGen::PortFromName(string name, string prefix) {
  if (name.empty())
    return 0;
  if (name.find(prefix) != 0) {
    err("Unknown port name: " + name);
    return 0;
  }
  uint16_t res = stoi(&name[prefix.size()], nullptr, 10);
  if (res > 63)
    err("Port number should be in range 0-63");
  return res;
}

void CodeGen::err(string msg) {
  cout << msg << endl;
  errors_.push_back(msg);
}

///////////////////////////////////////////////////////////////////////////////

// ADD R0, R1
// ADD R2, 10
class BinaryCodeGen: public CodeGen {
 public:
  BinaryCodeGen(COP cop, string left, string right)
    : CodeGen(cop), right_str_(right) {
    left_op_ = RegFromName(left);
    SetImmediate(right);
  }

  void SetImmediate(string right) {
    int t = 0;
    immediate_ = StrToInt(right, &t);  // MOV R1, 10
    if (immediate_) {
      if (t < 0)
        right_val_ = t & 0x00FF;
      else
        right_val_ = t;

      if (right_val_> 0xFF)
        err("Error. Immediate value should have 8 bit only (0 - 255). Got: " + right);
    }

    if (!immediate_)  // not val, try to check register name
      right_op_ = RegFromName(right);  // MOV R0, 10

    if (!immediate_ && right_op_ == rUnkReg)
      err("You have to use Register name or immediate value as rval.");
    else
      right_str_ = "";
  }

  uint16_t Emit() {
    //ARITHM res;
    //res.cop = operation_;
    //return res;
    uint16_t cop = operation_;
    cop |= left_op_ << 9;  // don't forget about C bit
    if (immediate_) {
      cop |= right_val_;
      cop |= 0x0100;  // set C bit to 1
    }
    else
      cop |= right_op_ << 5;
    return cop;
  }

  void update_machine_code(const map<string, UINT>& name_to_address) {
    if (right_str_.empty())
      return;

    bool hi {false};
    if (right_str_.find("LO(") == 0)
      right_str_ = right_str_.substr(3, right_str_.size() - 4);
    else if (right_str_.find("HI(") == 0) {
      right_str_ = right_str_.substr(3, right_str_.size() - 4);
      hi = true;
    }

    map<string, UINT>::const_iterator it;
    for (it = name_to_address.begin(); it != name_to_address.end(); it++) {
      string t = to_upper(it->first);
      if (t == right_str_)
        break;
    }

    if (it == name_to_address.end()) {
      err("Name " + right_str_ + " not found in symbol list");
      return;
    }

    err("Replace " + it->first + " to " + to_string(it->second));

    right_val_ = it->second;
    if (hi)
      right_val_ >>= 8;
    right_val_ &= 0x00FF;
    immediate_ = true;
  }

  vector<int> get_blocks() {
    if (immediate_)
      //    COP dst C value
      return {4, 3, 1, 8};
    else
      //    COP dst C src F
      return {4, 3, 1, 3, 1};
  }

 private:
  REG left_op_ {rUnkReg};
  REG right_op_ {rUnkReg};
  uint16_t right_val_ {0};
  bool immediate_ {false};
  string right_str_ {};
};

// LSR R7
class UnaryCodeGen: public CodeGen {
 public:
  UnaryCodeGen(string op_name, string reg)
    : CodeGen(cUNO), op_name_(op_name) {
    reg_ = RegFromName(reg);
    if (unary_codes.find(op_name) != unary_codes.end())
      ucode_ = unary_codes[op_name];
    else {
      ucode_ = 0;
      err("Unknown unary operation ");
    }
  }

  uint16_t Emit() {
    uint16_t cop = operation_;
    cop |= ucode_;
    cop |= reg_ << 9;  // don't forget about C bit
    return cop;
  }

  vector<int> get_blocks() {
    //    COP reg 0  - TYP F
    return {4, 3, 1, 1, 2, 1};
  }

 private:
  string op_name_;
  uint16_t ucode_ {0};
  REG reg_ {rUnkReg};
};

// LD R0, X
// LD R1, XI + 10
class MemoryCodeGen: public CodeGen {
 public:
  MemoryCodeGen(COP cop, string left, string right, string tail)
    : CodeGen(cop) {
    if (cop == cLD || cop == cLPM || cop == cLPMW) {
      reg_ = RegFromName(left);
      ptr_ = PtrFromName(right, &inc_, &dec_);
    } else if (cop == cST) {
      ptr_ = PtrFromName(left, &inc_, &dec_);
      reg_ = RegFromName(right);
    } else {
      err("Unknown memory operation. Should be LD or ST or LPM.");
    }

    offset_ = parse_offset(tail);
  }

  UINT parse_offset(string tail) {
    if (tail.empty())
      return 0;

    if (tail[0] != '+' && tail[0] != '-') {
      err("You can add or substract offset from pointer register. No other operations.");
      return 0;
    }

    if (tail.size() < 2) {
      err("You lost offset value.");
      return 0;
    }

    UINT res {0};
    int off = stoi(&tail[1], nullptr, 10);
    if (tail[0] == '-')
      off = -off;
    if (off > 7)
      err("Offset has to be <= 7.");
    else if (off < -8)
      err("Offset has to be >= -8.");
    else
      res = off & 0x0F;  // we need only 4 bits
    return res;
  }

  uint16_t Emit() {
    uint16_t cop = operation_;
    cop |= reg_ << 9;  // don't forget about C bit
    cop |= ptr_ << 6;
    cop |= dec_ << 5;
    cop |= inc_ << 4;
    cop |= offset_;
    return cop;
  }

  vector<int> get_blocks() {
    //    COP dst 0 EXT D  U  OFFSET
    return {4, 3, 1, 2, 1, 1, 4};
  }

 private:
  REG reg_ {rUnkReg};
  PTR ptr_ {rUnkPtr};
  bool inc_ {false};  // post increment ptr_
  bool dec_ {false};  // post decrement ptr_
  UINT offset_ {0};
};

// IN R0, PORT1
class IOCodeGen: public CodeGen {
 public:
  IOCodeGen(COP cop, string left, string right)
    : CodeGen(cop) {
    if (cop == cIN) {
      reg_ = RegFromName(left);
      port_ = PortFromName(right, "PIN");
    } else if (cop == cOUT || cop == cTOGL) {
      port_ = PortFromName(left, "PORT");
      reg_ = RegFromName(right);
    } else {
      err("Unknown IO operation. Should be IN or OUT.");
    }
  }

  uint16_t Emit() {
    uint16_t cop = operation_;
    cop |= reg_ << 9;
    cop |= port_ << 4;
    return cop;
  }

  vector<int> get_blocks() {
    //   COP dst port -- Ii
    //   COP src port Oo Xx
    return {4, 3, 5, 2, 2};
  }

 private:
  REG reg_ {rUnkReg};
  uint16_t port_ {0};
};

class BranchCodeGen: public CodeGen {
 public:
  BranchCodeGen(COP cop, string label)
    : CodeGen(cop), label_(label) {}

  uint16_t Emit() {
    uint16_t cop = operation_;
    cop |= (uint16_t)target_addr_;
    if (operation_ == bNOP)
      cop |= 0xFF;
    return cop;
  }

  void update_machine_code(const map<string, UINT>& name_to_address) {
    map<string, UINT>::const_iterator it;
    for (it = name_to_address.begin(); it != name_to_address.end(); it++) {
      if (to_upper(it->first) == label_) {
        UINT label_addr = it->second;
        if (operation_ == bAFCALL) {
          if (label_addr % 256)
            err("Label address in far call must be a multiple of 256.");
          target_addr_ = label_addr >> 8;  // absolute address divided by 256
        } else {
          int offset = label_addr;
          offset -= address_;         // offset from current address
          if (offset > 127 || offset < -128)
            err("Error: Label " + label_ + " is too far from this instruction");
          else
            target_addr_ = offset & 0xFF;
        }
        cout << "new target address: " << hex << target_addr_ << endl;
      }
    }
  }

  vector<int> get_blocks() {
    //    COP TYP offset/addr
    return {4, 4, 8};
  }

 private:
  string label_;
  UINT target_addr_ {0};
};

///////////////////////////////////////////////////////////////////////////////

CodeLine::CodeLine(int line_number, string line_text)
  : line_number_(line_number), line_text_(line_text) {

  size_t pos = line_text_.find(":");
  while (pos != string::npos) {
    string label = line_text_.substr(0, pos);
    if (!label.empty()) {
      labels_.push_back(label);
      cout << "label: " << label << endl;
    }
    line_text_.erase(0, pos + 1);
    pos = line_text_.find(":");
  }
  cout << "line tail: " << line_text_ << endl;

  stringstream ss(prepare_line(line_text_));
  // examples:
  // MOV R0, R1
  // JMP label
  string op_name, left, right, tail;
  ss >> op_name;      // LD
  ss >> left;         // R0
  ss >> right;        // XI
  getline(ss, tail);  // right value may have offset, for example: XI + 10, so get full line: +10
  remove_all_spaces(tail);

  string msg;
  if (g_def_values.find(op_name) != g_def_values.end()) {
    const MACRO &m = g_def_values[op_name];
    cout << "have to replace " << op_name << " to " << m.val_ << endl;
    string new_op {m.val_};
    if (m.arg_.size()) {
      new_op = sreplace(new_op, m.arg_, left);  // macro has one arg
      new_op = sreplace(new_op, m.arg_, left);  // but instructions may have two regs
    }
    cout << "***** " << new_op << endl;
    msg = ".def was applied, got: " + new_op;

    // Try 2:
    stringstream ss(prepare_line(new_op));
    ss >> op_name;      // LD
    ss >> left;         // R0
    ss >> right;        // XI
    getline(ss, tail);  // right value may have offset, for example: XI + 10, so get full line: +10
    remove_all_spaces(tail);
  }

  if (g_def_values.find(left) != g_def_values.end()) {
    const MACRO &m = g_def_values[left];
    cout << "have to replace " << left << " to " << m.val_ << endl;
    left = m.val_;
  }

  if (g_def_values.find(right) != g_def_values.end()) {
    const MACRO &m = g_def_values[right];
    cout << "have to replace " << right << " to " << m.val_ << endl;
    right = m.val_;
  }

  COP op {cNO_OP};
  if (cop_names.find(op_name) != cop_names.end()) {
    op = cop_names[op_name];
  } else {
    cout << "Error. Unknown operation: |" << op_name << "|" << endl;
    return;
  }

  OP_TYPE opt = CopToType(op);
  cout << "Operation type: " << opt << endl;

  CodeGen* cg {nullptr};
  switch (opt) {
    case tBINARY: cg = new BinaryCodeGen(op, left, right); break;
    case tUNARY: cg = new UnaryCodeGen(op_name, left); break;
    case tMEMORY: cg = new MemoryCodeGen(op, left, right, tail); break;
    case tIO: cg = new IOCodeGen(op, left, right); break;
    case tBRANCH: cg = new BranchCodeGen(op, left); break;
    case tNO_OP:
    default:
      cout << "No operation is required" << endl;
  }

  code_gen_.reset(cg);
  if (code_gen_ && msg.size())
    code_gen_->err(msg);

  cout << "GOT: |" << op_name << "|" << left << "|" << right << "|" << tail << "|" << endl;
}

string CodeLine::prepare_line(string line) {
  string res = to_upper(line);
  size_t pos = res.find(',');
  if (pos != string::npos)
    res[pos] = ' ';  // try to convert 'mov r0, r1' to 'mov r0  r1'
  return res;
}

uint16_t CodeLine::generate_machine_code() {
  if (!code_gen_)
    return bNOP | 0xFF;

  uint16_t cop = code_gen_->Emit();
  return cop;
}

void CodeLine::update_machine_code(const map<string, UINT>& name_to_address) {
  if (!code_gen_)
    return;
  code_gen_->update_machine_code(name_to_address);
}

string CodeLine::FormattedCOP() {
  if (!code_gen_)
    return {};
  return code_gen_->FormattedCOP();
}

///////////////////////////////////////////////////////////////////////////////

void help();

int main(int argc, char* argv[]) {
  //locale::global(locale(""));
  SetConsoleOutputCP(CP_UTF8);

  if (argc < 2) {
    help();
    return 0;
  }

  if (argc == 2 && argv[1]) {
    string cmd(argv[1]);
    if (cmd == "help") {
      help();
      return 0;
    }

    // okay, probably cmd is file name ;)
    Assembler assm;
    return assm.process(cmd);
  }

  cout << "argc: " << argc << endl;
  return 0;
}

void help() {
  const char* help_lines[] = {
      "74HCPU assembler v 0.3\n",
      "Support next operations:\n",
      "arithmetic: ADD, ADDC, AND, OR, XOR, MUL, UNO, MOV\n",
      "memory: LPM, LD, ST\n",
      "port: IN, OUT\n",
      "compare: CMP, CMPC\n",
      "jmp: CALL, JMP, RET, JZ, JL, JNE, JE, JG, JC, JNZ, JNC, JHC, JNHC, STOP, AFCALL, NOP\n",
      "Registers: R0, R1, R2, R3, R4, R5, R6, R7\n",
      "Register pointers: X(XL+XH), Y(YL+YH), Z(ZL+ZH), SP(SPL+SPH)\n",
      "PORTS: PORT0-31, PIN0-31\n",
      nullptr
  };

  int i = 0;
  while (help_lines[i]) {
    cout << help_lines[i];
    i++;
  }
}

///////////////////////////////////////////////////////////////////////////////

StringConst& StringConst::operator=(const StringConst& rval) {
  this->str_ = rval.str_;
  this->addr_ = rval.addr_;
  return *this;
}

UINT StringConst::get_size() const {
  return str_.size() + 1;
}

void StringConst::set_addr(UINT addr) {
  if (addr > 0xFFFF) {
    cout << "Address is too much: " << addr;
    return;
  }

  addr_ = addr;
}

void StringConst::out_code() const {
  UINT addr = addr_;
  for (size_t i = 0; i < str_.size(); i++)
    cout << "     " << hex
       << setw(4) << setfill('0') << right << addr++ << ": "
       << setw(4) << setfill('0') << right << UINT(str_[i]) << " "
       << str_[i] << endl;

  cout << "     " << hex
       << setw(4) << setfill('0') << right << addr++ << ": "
       << setw(4) << setfill('0') << right << UINT(0) << " "
       << "Zero" << endl;
}

///////////////////////////////////////////////////////////////////////////////

int Assembler::process(string fname) {
  FileReader fr;
  int res = fr.read_file(fname, &lines_);
  if (res != 0)
    return res;

  merge_code_with_labels();
  extract_orgs();
  extract_string();
  extract_defs();
  pass1();
  pass2();
  pass3();
  out_labels();
  out_orgs();
  out_code();

  return 0;
}

void Assembler::merge_code_with_labels() {
  map<int, string>::iterator it, prev;
  for (it = lines_.begin(); it != lines_.end();) {
    prev = it;
    it++;
    if (*prev->second.rbegin() == ':' &&       // ok, comment was found
        it != lines_.end()) {                  // and we have some code on the next line
      it->second = prev->second + it->second;  // move comment to the next line
      lines_.erase(prev);                      // remove comment from curent line
    }
  }
}

void Assembler::extract_orgs() {
  map<int, string>::iterator it;
  for (it = lines_.begin(); it != lines_.end();) {
    int line = it->first;
    string org = normalize_line(it->second);
    if (org.find(".org") == 0) {
      cout << line << ":" << org << endl;
      org.erase(0, sizeof(".org"));

      int val {0};
      string msg_err;
      if (StrToInt(org, &val, &msg_err)) {
        line_to_org_[line] = val;
        cout << "now line " << line << " has address " << val << endl;
      } else
        cout << "Can't convert org value to int" << endl << msg_err << endl;
      it = lines_.erase(it);  // now remove this directive from asm
    }
    else
      it++;
  }
}

void Assembler::extract_string() {
  map<int, string>::iterator it;
  for (it = lines_.begin(); it != lines_.end();) {
    string str = normalize_line(it->second);
    if (str.find(".str") == 0) {
      str.erase(0, sizeof(".str"));

      size_t pos = str.find(" ");
      if (pos == string::npos) {
        cout << "Error in string const: '" << it->second << "'" << endl;
        cout << "Line: " << it->first << ". String value not found" << endl;
      } else if (pos < str.size()) {
        string str_name = trim(str.substr(0, pos));
        string str_val = remove_quotes(trim(str.substr(pos + 1)));
        string_consts_[str_name] = StringConst(str_val);
        cout << "STR '" << str_name << "' = '" << str_val << "'" << endl;
      }
      it = lines_.erase(it);  // now remove this directive from asm
    }
    else
      it++;
  }
}

string extract_arg(string& name_w_arg) {
  size_t left = name_w_arg.find('(');
  size_t right = name_w_arg.find(')');

  if (left == string::npos || right == string::npos)
    return {};
  if (right < left)
    return {};

  string arg = name_w_arg.substr(left + 1, right - left - 1);
  name_w_arg.resize(left);
  return arg;
}

void Assembler::extract_defs() {
  map<int, string>::iterator it;
  for (it = lines_.begin(); it != lines_.end();) {
    string str = normalize_line(it->second);
    if (str.find(".def") == 0) {
      str.erase(0, sizeof(".def"));
      //str = trim(str);

      size_t pos = str.find(" ");
      if (pos != string::npos) {
        string def_name = trim(str.substr(0, pos));
        string def_val = trim(str.substr(pos + 1));
        string def_arg = extract_arg(def_name);
        g_def_values[def_name] = MACRO(def_val, def_arg);
        if (def_arg.size())
          cout << "DEF " << def_name << "(" << def_arg << ") = " << def_val << endl;
        else
          cout << "DEF " << def_name << " = " << def_val << endl;
      } else
        cout << "error in .def directive: " << it->second << endl;

      it = lines_.erase(it);  // now remove this directive from asm
    }
    else
      it++;
  }
}

// generate machine code
void Assembler::pass1() {
  map<int, string>::iterator it;
  for (it = lines_.begin(); it != lines_.end(); it++) {
    code_.push_back(CodeLine(it->first, normalize_line(it->second)));
  }
}

// get real address of labels & string
void Assembler::pass2() {
  UINT addr = 0;
  vector<CodeLine>::iterator it;
  map<int, UINT>::iterator oit = line_to_org_.begin();
  for (it = code_.begin(); it != code_.end(); it++, addr++) {
    if (oit != line_to_org_.end() &&
        it->line_number() > oit->first) {
      cout << "***** org placed here *****" << endl;
      if (oit->second > addr) {
        addr = oit->second;
        cout << "move address to: " << addr << endl;
      }
      oit++;
    }

    it->set_address(addr);

    vector<string> labels = it->get_labels();
    vector<string>::iterator lit;
    for (lit = labels.begin(); lit != labels.end(); lit++)
      name_to_address_[*lit] = addr;
  }

  UINT max_addr = get_max_address();
  cout << "max_addr: " << max_addr << " (" << hex << max_addr << "h)" << endl;

  addr = max_addr + 1;
  for (auto& s : string_consts_) {
    s.second.set_addr(addr);
    name_to_address_[s.first] = addr;
    cout << "add to name_to_address_: " << s.first << " = " << to_string(addr) << endl;
    addr += s.second.get_size();
  }
}

// set real jump addresses
void Assembler::pass3() {
  vector<CodeLine>::iterator it;
  for (it = code_.begin(); it != code_.end(); it++)
    it->update_machine_code(name_to_address_);
}

UINT Assembler::get_max_address() {
  UINT max_addr {0};
  vector<CodeLine>::iterator it;
  for (it = code_.begin(); it != code_.end(); it++)
    if (max_addr < it->address())
      max_addr = it->address();
  return max_addr;
}

void Assembler::out_code() {
  cout << "STRINGS ADDR:" << endl;
  for (const auto& s : string_consts_)
    cout << s.first << ": " << s.second.addr() << endl;

  cout << "LINE ADDR: COP   ASM               LABELS          FORMATTED_COP" << endl;
  vector<CodeLine>::iterator it;
  for (it = code_.begin(); it != code_.end(); it++) {
    cout << dec
         << setw(4) << setfill(' ') << right << it->line_number() << " "
         << hex
         << setw(4) << setfill('0') << right << it->address() << ": "
         << setw(4) << setfill('0') << right << it->generate_machine_code() << "  "
         << setw(16) << setfill(' ') << left << it->get_line_text() << "  "
         << setw(16) << setfill(' ') << left << it->get_labels_as_string()
         << setw(16) << setfill(' ') << left << it->FormattedCOP()
         << endl;

    vector<string> el = it->get_err();
    for (auto& e : el)
      cout << "         > " << e << endl;
  }

  cout << "STRINGS:" << endl;
  for (auto& s : string_consts_) {
    cout << s.first << ":" << endl;
    s.second.addr();
    s.second.out_code();
  }
}

void Assembler::out_labels() {
  cout << "LABELS:" << endl;
  for (auto v : name_to_address_)
    //    line number        line code
    cout << v.first << " " << v.second << endl;
}

void Assembler::out_orgs() {
  cout << "ORGS:" << endl;
  for (auto v : line_to_org_)
    cout << v.first << " " << v.second << endl;
}

///////////////////////////////////////////////////////////////////////////////

int FileReader::read_file(string fname, map<int, string> *result) {
  if (!result) {
    cout << "Error: no output array";
    return 1;
  }

  ifstream f;
  f.open(fname, ios::binary);
  if (!f) {
    cout << "Error. Can't open file " << fname << endl;
    return 1;
  }

  cout << "Processing " << fname << "..." << endl;
  for_each(istreambuf_iterator<char>(f),
           istreambuf_iterator<char>(),
           [this](const char& c) { handle_char(c); });

  handle_char('\n');  // probably there is no EOL on the last line of code
  f.close();

  *result = std::move(lines_);

  return 0;
}

void FileReader::handle_char(const char& c) {
  if (c == '\r')
    return;

  if (c == ' ' && skip_space_)
    return;

  skip_space_ = false;

  if (c == '\n') {
    string t = trim_right(line_);
    if (!t.empty())
      lines_[line_num_] = std::move(t);
    line_ = "";  // not sure about line state after move
    skip_space_ = true;
    skip_comment_ = false;
    line_num_++;
    return;
  }

  if (c == ';')
    skip_comment_ = true;

  if (!skip_comment_)
    line_ += c;
}

///////////////////////////////////////////////////////////////////////////////
