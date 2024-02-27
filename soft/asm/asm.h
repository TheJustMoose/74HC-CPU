#pragma once

#include <string>
#include <vector>

using namespace std;

typedef unsigned int UINT;

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

enum REG : uint16_t {
  // Arithmetic registers
  rR0 = 0, rR1 = 1, rR2 = 2, rR3 = 3, rR4 = 4, rR5 = 5, rR6 = 6, rR7 = 7, rUnkReg = 0x100
};

enum PTR : uint16_t {
  // Pointer register pairs
  rX = 0, rY = 1, rZ = 2, rSP = 3,
  // Same pointers but with post increment
  rXI = 0x10, rYI = 0x11, rZI = 0x12, rSPI = 0x13,
  // Same pointers but with post decrement
  rXD = 0x20, rYD = 0x21, rZD = 0x22, rSPD = 0x23,
  rUnkPtr = 0x100
};

class CodeGen {
 public:
  CodeGen(COP cop)
   : operation_(cop) {}
  virtual ~CodeGen() {}

  virtual uint16_t Emit() = 0;
  virtual void update_machine_code(const map<string, UINT>& label_to_address) {}

  virtual vector<int> get_blocks() { return {}; }
  virtual string cop() {
    stringstream s;
    s << bitset<16>(Emit());
    return s.str();
  }
  string FormattedCOP() {
    string res = cop();
    vector<int> blocks = get_blocks();
    if (blocks.empty())
      return res;

    size_t pos {0};
    for (auto b : blocks) {
      pos += b;
      if (pos >= res.size())
        break;
      res.insert(pos, " ");
      pos++;
    }
    return res;
  }
  void set_address(UINT addr) {
    address_ = addr;
  }

  void err(string msg);
  vector<string> get_err() {
    return errors_;
  }

  bool StrToInt(string val, UINT* pout);
  REG RegFromName(string name);
  PTR PtrFromName(string name);
  uint16_t PortFromName(string name, string prefix);

 protected:
  UINT address_ {0};
  COP operation_ {cNO_OP};
  vector<string> errors_ {};
};

class CodeLine {
 public:
  CodeLine(int line_number, string line_text);

  uint16_t generate_machine_code();
  void update_machine_code(const map<string, UINT>& label_to_address);
  string FormattedCOP();

  vector<string> get_labels() {
    return labels_;
  }

  string get_labels_as_string() {
    if (!has_labels())
      return {};

    string res;
    for (auto& l : labels_) {
      res += l;
      res += " ";
    }
    return res;
  }

  bool has_labels() {
    return labels_.size() > 0;
  }

  string get_line_text() {
    return line_text_;
  }

  void set_address(UINT addr) {
    if (code_gen_)
      code_gen_->set_address(addr);
  }

  vector<string> get_err() {
    if (code_gen_)
      return code_gen_->get_err();
    else
      return {};
  }

 private:
  int line_number_ {0};

  unique_ptr<CodeGen> code_gen_ {nullptr};

  vector<string> labels_ {};
  string line_text_ {};
};

// TODO: extract some methods into Assembler class
class Assembler {
 public:
  int process(string fname);
  void out_src();

 protected:
  void merge_code_with_labels();
  void extract_orgs();
  void pass1();
  void pass2();
  void pass3();
  void out_code();

 private:
  map<int, string> lines_ {};
  vector<CodeLine> code_;
  map<string, UINT> label_to_address_;
};

class FileReader {
 public:
  FileReader() = default;

  int read_file(string fname, map<int, string> *result);

  void handle_char(const char& c);
  string trim_right(string);

 private:
  string line_ {};
  bool skip_space_ {true};
  bool skip_comment_ {false};
  int line_num_ {1};
  map<int, string> lines_ {};
};
