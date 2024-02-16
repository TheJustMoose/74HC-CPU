#pragma once

#include <string>

using namespace std;

typedef unsigned int UINT;

class CodeGen;

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

enum REG : UINT {
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

class CodeLine {
 public:
  CodeLine(int line_number, string line_text);

  void generate_machine_code();

 private:
  int line_number_ {0};
  int address_ {0};

  unique_ptr<CodeGen> code_gen_ {nullptr};

  vector<string> labels_ {};
  string line_text_ {};
};

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
