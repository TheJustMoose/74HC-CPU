///////////////////////////////////////////////////////////////////////////////
/*

Ассемблер для моего 74HCPU под новую систему команд:

    4   +  3  +1+  3  +   5   = 16
 0 1 2 3 4 5 6 7 8 9 A B C D E F         флаги
-----------------------------------------------
|   ADD | DST |C| SRC |-|Z|z|I|i| 00 0000  *  // ADDI  R0, 1    // INC R0;
|  ADDC | DST |C| SRC |F|Z|z|I|i| 01 0001  *  // ADDCI R1, 0    // INCC R1;    // бит F нужен для команд -INC-, -DEC-, SUB, -INV-, NEG
|   AND | DST |C| SRC |-|Z|z|I|i| 02 0010  *  // ANDI R2, 0x0F  // здесь есть свободный бит, и вместо F туда можно положить S[WAP] или S[HIFT]
|    OR | DST |C| SRC |-|Z|z|I|i| 03 0011  *  // ORI R3, 2      // в любом случае, сдвиг старшего нибла на место младшего кажется полезным
|   XOR | DST |C| SRC |-|Z|z|I|i| 04 0100  *  // XORI R4, 4     // кстати, в этом случае можно ещё и от команды SWAP избавиться
|   MUL | DST |C| SRC |-|Z|z|I|i| 05 0101  *  // MULI R6, 10    // R7:R6 := R6*10
|   UNO | DST |0|TYP|-|F|-|-|-|-| 06 0110  *  // унарные команды не используют операнд SRC, поэтому нельзя использовать инверторы и отдельные нибблы
|   MOV | DST |C| SRC |*|Z|z|I|i| 07 0111  -  // MOVI R5, 5     // LDI R5, 5       // * - можно использовать, чтобы пихать адрес в SPL/SPH (правда, только из других регистров)
|   LPM | DST |W|EXT|?|U|OFFSET4| 08 1000  -  // LPM R0, [IX]   // LPM R1, [X+1]   // LPM R1, [DX-1]  // W - читать слово (1) или байт (0)
|    LD | DST |0|EXT|D|U|OFFSET4| 09 1001  -  // LD R1, [-Y]    // LD R3, [+SP-1] ; POP R3
|    IN | DST |  PORT   |-|-|I|i| 0A 1010  -  // IN R2, PIN1    // IN R2, ~PIN1 ; инвертировать порт перед чтением
|-------------|7-8-9-A-B|-------|------------ всё что ниже - не модифицирует регистры
|   OUT | SRC |  PORT   |O|o|X|x| 0B 1011  -  // OUT PORT0, R2  // XOUT PORT0, R2
|    ST | SRC |0|EXT|D|U|OFFSET4| 0C 1100  -  // ST [Y], R2     // ST [IX], R2     // ST [Y+2], R2   // ST [-SP], R2 ; PUSH R2
|   CMP | DST |C| SRC |-|   -   | 0D 1101  +  // CMPI R3, 10    // CMP  R0, R2
|  CMPC | DST |C| SRC |-|   -   | 0E 1110  +  // CMPCI R4, 10   // CMPC R1, R3
| BRNCH |  CALL | 8 bit OFFSET  | 0F 1111 0000 // переход в +-127 команды, значение прибавляется к текущему счётчику команд
| BRNCH |   JMP | 8 bit OFFSET  | 0F 1111 0001 <- COP low byte
| BRNCH |   RET | 8 bit +STACK  | 0F 1111 0010 // на сколько байт переместить указатель стека, дабы пропустить запушенные параметры
| BRNCH |    JZ | 8 bit OFFSET  | 0F 1111 0011 // условные переходы
| BRNCH |    JL | 8 bit OFFSET  | 0F 1111 0100
| BRNCH |   JNE | 8 bit OFFSET  | 0F 1111 0101
| BRNCH |    JE | 8 bit OFFSET  | 0F 1111 0110
| BRNCH |    JG | 8 bit OFFSET  | 0F 1111 0111
| BRNCH |    JC | 8 bit OFFSET  | 0F 1111 1000
| BRNCH |   JNZ | 8 bit OFFSET  | 0F 1111 1001
| BRNCH |   JNC | 8 bit OFFSET  | 0F 1111 1010
| BRNCH |   JHC | 8 bit OFFSET  | 0F 1111 1011
| BRNCH |  JNHC | 8 bit OFFSET  | 0F 1111 1100
| BRNCH |  STOP |   0000 0000   | 0F 1111 1101 // отладочный стоп, чтобы можно было смотреть глазами регистры (и есть 8 бит на фантазию, например останавливаться только при записи в порт)
| BRNCH |AFCALL | Hi 8 bit ADDR | 0F 1111 1110 // Absolute Far Call - 8 bit ADDR кладём в старшие биты и ничего не добавляем к младшим
| BRNCH |   NOP |   1111 1111   | 0F 1111 1111 // NOP - хорошо бы чтоб имел код 0xFF, это позволит думать, что не прошитая память заполнена NOP-ами
*/
///////////////////////////////////////////////////////////////////////////////

#include <algorithm>
#include <cctype>
#include <fstream>
#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <vector>
#include <windows.h>

using namespace std;

///////////////////////////////////////////////////////////////////////////////

// Code Of Operation
enum COP {
  cADD = 0x00, cADDC = 0x10,
  cAND = 0x20, cOR = 0x30, cXOR = 0x40,
  cMUL = 0x50, cUNO = 0x60, cMOV = 0x70,
  cLPM = 0x80, cLD = 0x90,
  cIN = 0xA0, cOUT = 0xB0,
  cST = 0xC0,
  cCMP = 0xD0, cCMPC = 0xE0,
  bCALL = 0xF0,
  bJMP = 0xF1,
  bRET = 0xF2,
  bJZ = 0xF3,
  bJL = 0xF4,
  bJNE = 0xF5,
  bJE = 0xF6,
  bJG = 0xF7,
  bJC = 0xF8,
  bJNZ = 0xF9,
  bJNC = 0xFA,
  bJHC = 0xFB,
  bJNHC = 0xFC,
  bSTOP = 0xFD,
  bAFCALL = 0xFE,
  bNOP = 0xFF,    // processor operation
  cNO_OP = 0x100  // just constant for "there is no operation here", for example for labels
};

enum OP_TYPE {
  tBINARY, tUNARY, tMEMORY, tIO, tBRANCH, tNO_OP
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
  else if (cop == cLPM || cop == cLD || cop == cST)
    return tMEMORY;
  else if (cop == cIN || cop == cOUT)
    return tIO;
  else if (cop >= bCALL && cop <= bNOP)
    return tBRANCH;
  else  // I don't know then this should work
    return tNO_OP;
}

enum UNARY_TYPE {
  unINV, unSWAP, unLSR, unLSRC
};

map<string, COP> cop_names {
  { "ADD", cADD}, { "ADDC", cADDC},
  { "AND", cAND}, { "OR", cOR}, { "XOR", cXOR},
  { "MUL", cMUL},
  { "INV", cUNO}, { "SWAP", cUNO}, { "LSR", cUNO}, { "LSRC", cUNO},
  { "MOV", cMOV},
  { "LPM", cLPM}, { "LD", cLD}, { "LOAD", cLD},
  { "IN", cIN}, { "OUT", cOUT},
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

enum REG {
  // Arithmetic registers
  rR0 = 0, rR1 = 1, rR2 = 2, rR3 = 3, rR4 = 4, rR5 = 5, rR6 = 6, rR7 = 7,
  // Pointer register pairs
  rX = 8, rY = 9, rZ = 10, rSP = 11,
  // Same pointers but with post increment
  rXI = 8, rYI = 9, rZI = 10, rSPI = 11,
  // Same pointers but with post decrement
  rXD = 8, rYD = 9, rZD = 10, rSPD = 11,
  rUnk = 100
};

map<string, REG> reg_names {
  { "R0", rR0 }, { "R1", rR1 }, { "R2", rR2 }, { "R3", rR3 }, { "R4", rR4 }, { "R5", rR5 }, { "R6", rR6 }, { "R7", rR7 },
  { "X", rX }, { "Y", rY }, { "Z", rZ }, { "SP", rSP },
  { "XI", rXI }, { "YI", rYI }, { "ZI", rZI }, { "SPI", rSPI },
  { "XD", rXD }, { "YD", rYD }, { "ZD", rZD }, { "SPD", rSPD },
};

//  tBINARY, tUNARY, tMEMORY, tIO, tBRANCH, tNO_OP
class CodeGen {
 public:
  CodeGen();
  virtual void Emit() = 0;
};

class BinaryCodeGen: public CodeGen {
 public:
  BinaryCodeGen() = default;
  void Init(COP cop, string left, string right);
  void Emit() {}
};

class UnaryCodeGen: public CodeGen {
 public:
  UnaryCodeGen() = default;
  void Init(COP cop, string op);
  void Emit() {}
};

class MemoryCodeGen: public CodeGen {
 public:
  MemoryCodeGen() = default;
  void Init(COP cop, string left, string right);
  void Emit() {}
};

class IOCodeGen: public CodeGen {
 public:
  IOCodeGen() = default;
  void Init(COP cop, string left, string right);
  void Emit() {}
};

class BranchCodeGen: public CodeGen {
 public:
  BranchCodeGen() = default;
  void Init(COP cop, string label);
  void Emit() {}
};

class CodeLine {
 public:
  CodeLine(int line_number, string line_text);

  void generate_machine_code();

 private:
  int line_number_ {0};
  int address_ {0};
  COP operation_ {cNO_OP};
  //REG left_op_ {rUnk};
  //REG right_op_ {rUnk};

  vector<string> labels_ {};
  string line_text_ {};
};

string to_upper(string s) {
  std::transform(s.begin(), s.end(), s.begin(), ::toupper);
  return s;
}

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
    //cout << "line_text_ after label remove: " << line_text_ << endl;
    pos = line_text_.find(":");
  }
  cout << "line tail: " << line_text_ << endl;

  string t = to_upper(line_text_);
  pos = t.find(',');
  if (pos != string::npos)
    t[pos] = ' ';  // try to convert 'mov r0, r1' to 'mov r0  r1'
  //cout << "after replace: " << t << endl;

  stringstream ss(t);
  // examples:
  // MOV R0, R1
  // JMP label
  string cop, left, right;
  ss >> cop;
  ss >> left;
  ss >> right;

  if (cop_names.find(cop) != cop_names.end()) {
    operation_ = cop_names[cop];
  } else {
    cout << "Error. Unknown operation: |" << cop << "|" << endl;
    return;
  }

  OP_TYPE opt = CopToType(operation_);
  cout << "Operation type: " << opt << endl;

  CodeGen* cg {nullptr};
  switch (opt) {
    // а здесь надо как-то пропихнуть внутрь регистры, возможно даже лишние :(
    case tBINARY: cg = new BinaryCodeGen(opt, left, right);
    case tUNARY: cg = new UnaryCodeGen(opt, left);
    case tMEMORY: cg = new MemoryCodeGen(opt, left, right);
    case tIO: cg = new IOCodeGen(opt, left, right);
    case tBRANCH: cg = new BranchCodeGen(opt, left);
    case tNO_OP:
    default:
      cout << "No operation is required" << endl;
  }
/*
  if (!left.empty()) {
    if (reg_names.find(left) != reg_names.end())
      left_op_ = reg_names[left];
    else
      cout << "Unknown register: " << left << endl;
  }

  if (!right.empty()) {
    if (reg_names.find(right) != reg_names.end())
      right_op_ = reg_names[right];
    else
      cout << "Unknown register: " << right << endl;
  }
*/
  cout << "GOT: |" << cop << "|" << left << "|" << right << "|" << endl;
  cout << "CODE: " << hex << operation_ << endl;
}

void CodeLine::generate_machine_code() {
}

///////////////////////////////////////////////////////////////////////////////

// TODO: extract some methods into Assembler class
class FileReader {
 public:
  int process(string fname);
  int read_file(string fname);
  void out_src();

 protected:
  void handle_char(const char& c);
  string trim_right(string);
  void merge_code_with_labels();
  void pass1();

 private:
  map<int, string> lines_ {};
  string line_ {};
  bool skip_space_ {true};
  bool skip_comment_ {false};
  int line_num_ {1};
};

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
    FileReader fr;
    return fr.process(cmd);
  }

  printf("argc: %d\n", argc);
  return 0;
}

void help() {
  const char* help_lines[] = {
      "74HCPU assembler v 0.2\n",
      "Support next operations:\n",
      "arithmetic: ADD, ADDC, AND, OR, XOR, MUL, UNO, MOV\n",
      "memory: LPM, LD, ST\n",
      "port: IN, OUT\n",
      "compare: CMP, CMPC\n",
      "jmp: CALL, JMP, RET, JZ, JL, JNE, JE, JG, JC, JNZ, JNC, JHC, JNHC, STOP, AFCALL, NOP\n",
      "Registers: R0, R1, R2, R3, R4, R5, R6, R7\n",
      "Register pointers: X(XL+XH), Y(YL+YH), Z(ZL+ZH), SP(SPL+ZPH)\n",
      "PORTS: PORT0-31, PIN0-31",
      nullptr
  };

  int i = 0;
  while (help_lines[i]) {
    cout << help_lines[i];
    i++;
  }
}

int FileReader::process(string fname) {
  int res = read_file(fname);
  if (res != 0)
    return res;

  merge_code_with_labels();
  pass1();
  out_src();

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
      lines_[line_num_] = t;
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

string FileReader::trim_right(string s) {
  if (s.empty())
    return {};

  // index of first right non empty char:
  size_t i = s.size() - 1;  // TODO: try rbegin() here
  while (s[i] == ' ' && i > 0)
     i--;

  if (i >= 0 && i < s.size())
    s.resize(i + 1);  // +1 will convert index to size
  return s;
}

void FileReader::merge_code_with_labels() {
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

void FileReader::pass1() {
  map<int, string>::iterator it;
  for (it = lines_.begin(); it != lines_.end(); it++) {
    CodeLine cl(it->first, it->second);
    cl.generate_machine_code();
  }
}

int FileReader::read_file(string fname) {
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
  return 0;
}

void FileReader::out_src() {
  for (auto v : lines_)
    //cout << v.second << endl;
    cout << v.first << " " << v.second << endl;
}

///////////////////////////////////////////////////////////////////////////////
