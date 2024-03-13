#pragma once

#include <string>
#include <vector>

using namespace std;

typedef unsigned int UINT;

// Code Of Operation
enum COP {
  cADD = 0x0000, cADDC = 0x1000,
  cAND = 0x2000, cOR = 0x3000, cXOR = 0x4000,
  cMUL = 0x5000, cUNO = 0x6000, cMOV = 0x7000,
  cLPM = 0x8000, cLPMW = 0x8100, cLD = 0x9000,
  cIN = 0xA000, cOUT = 0xB000, cTOGL = 0xB003,
  cST = 0xC000,
  cCMP = 0xD000, cCMPC = 0xE000,
  bCALL = 0xF000,
  bJMP = 0xF100,
  bRET = 0xF200,
  bJZ = 0xF300,
  bJL = 0xF400,
  bJNE = 0xF500,
  bJE = 0xF600,
  bJG = 0xF700,
  bJC = 0xF800,
  bJNZ = 0xF900,
  bJNC = 0xFA00,
  bJHC = 0xFB00,
  bJNHC = 0xFC00,
  bSTOP = 0xFD00,
  bAFCALL = 0xFE00,
  bNOP = 0xFF00,    // processor operation
  cNO_OP = 0x10000  // just constant for "there is no operation here", for example for labels or error op names
};

enum OP_TYPE {
  tBINARY, tUNARY, tMEMORY, tIO, tBRANCH, tNO_OP
};

enum REG : uint16_t {
  // Arithmetic registers
  rR0 = 0, rR1 = 1, rR2 = 2, rR3 = 3, rR4 = 4, rR5 = 5, rR6 = 6, rR7 = 7,   // Bank 0
  // Pointer registers
  rXL = 0, rXH = 1, rYL = 2, rYH = 3, rZL = 4, rZH = 5, rSPL = 6, rSPH = 7, // Bank 1
  rUnkReg = 0x100
};

enum PTR : uint16_t {
  // Pointer register pairs
  rX = 0, rY = 1, rZ = 2, rSP = 3,
  // Flags
  rInc = 0x10, rDec = 0x20,
  // Same pointers but with post increment
  rXI = rX | rInc, rYI = rY | rInc, rZI = rZ | rInc, rSPI = rSP | rInc,
  // Same pointers but with post decrement
  rXD = rX | rDec, rYD = rY | rDec, rZD = rZ | rDec, rSPD = rSP | rDec,
  rUnkPtr = 0x100
};

class CodeGen {
 public:
  CodeGen(COP cop)
   : operation_(cop) {}
  virtual ~CodeGen() {}

  virtual uint16_t Emit() = 0;
  virtual void update_machine_code(const map<string, UINT>& name_to_address) {}

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
  UINT address() {
    return address_;
  }
  void set_address(UINT addr) {
    address_ = addr;
  }

  void err(string msg);
  vector<string> get_err() {
    return errors_;
  }

  REG RegFromName(string name);
  PTR PtrFromName(string name, bool* inc, bool* dec);
  uint16_t PortFromName(string name, string prefix);

 protected:
  UINT address_ {0};
  COP operation_ {cNO_OP};
  vector<string> errors_ {};
};

class CodeLine {
 public:
  CodeLine(int line_number, string line_text);

  //string prepare_line(string line);

  uint16_t generate_machine_code();
  void update_machine_code(const map<string, UINT>& name_to_address);
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

  UINT address() {
    return code_gen_ ? code_gen_->address() : 0;
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

  int line_number() {
    return line_number_;
  }

 private:
  int line_number_ {0};

  unique_ptr<CodeGen> code_gen_ {nullptr};

  vector<string> labels_ {};
  string line_text_ {};
};

class StringConst {
 public:
  StringConst() = default;
  StringConst(const string& str): str_(str) {}
  StringConst& operator=(const StringConst& rval);

  UINT get_size() const;
  UINT addr() const { return addr_; }
  void set_addr(UINT);
  void out_code() const;
  string str() const {
    return str_;
  }

 private:
  string str_ {};
  UINT addr_ {0};
};

class Assembler {
 public:
  int process(string fname, bool show_preprocess_out = false);

 protected:
  void merge_code_with_labels();
  void extract_orgs();
  void extract_string();
  void extract_defs();
  void pass1();
  void pass2();
  void pass3();
  UINT get_max_address();
  void out_code();
  void out_labels();
  void out_orgs();

 private:
  map<int, string> lines_ {};
  map<int, UINT> line_to_org_ {};
  vector<CodeLine> code_ {};
  map<string, UINT> name_to_address_ {};
  map<string, StringConst> string_consts_ {};
};
