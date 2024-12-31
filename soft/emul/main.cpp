#include <fstream>
#include <iostream>
#include <iomanip>
#include <vector>
#include "lcd.h"
#include "emul.h"

using namespace std;

ostream& operator<< (ostream& ostr, const Reg& reg) {
  return ostr << static_cast<int>(reg);
}

ostream& operator<< (ostream& ostr, const LCD& lcd) {
  return ostr << lcd.Content();
}

// Intel -> Little endian -> low byte is stored in low address

void test_emul() {
//  TEST DATA:
// |   MOV | DST |C| SRC |*|Z|z|I|i| 70 0111 0000| |
//     MOV   R0,     0x0F
//    0111   000  1  0000 1111 == 0x710F
//     MOV   R1,     0x01
//    0111   001  1  0000 0001 == 0x7301
// |   ADD | DST |C| SRC |-|Z|z|I|i| 00 0000 0000|*|
//     ADD   R1,     R0
//    0000   001  0  000 00000 == 0x0200
  vector<ROM_DATA> buf(3, 0);
  buf[0] = 0x710F;
  buf[1] = 0x7301;
  buf[2] = 0x0200;

  ROM rom;
  rom.Flash(std::move(buf));

  cout << "max ROM addr: " << rom.GetMaxAddress() << endl;
  ROM_DATA d = rom.Read(0);
  cout << "First word: " << hex << d << endl;

  CPU cpu;
  for (ROM_ADDR addr = 0; addr < rom.GetMaxAddress(); addr++) {
    ROM_DATA machine_code = rom.Read(addr);
    std::unique_ptr<Instruction> ins = CreateFromMachineCode(machine_code);
    ins->Execute(&cpu);
  }
}

struct TEST {
  uint8_t first;  // low byte
  uint8_t second; // high byte
};

TEST test;

struct BTEST {
  uint8_t low : 4;  // low nibble
  uint8_t high : 4; // high nibble
};

union UN {
  uint8_t byte;
  BTEST btest;
} un;

int main(int argc, char* argv[]) {
  uint16_t x = 0x0001;
  printf("%s-endian\n", *((uint8_t *) &x) ? "little" : "big");

  cout << "first addr:  " << hex << (void*)&(test.first) << endl;
  cout << "second addr: " << hex << (void*)&(test.second) << endl;

  un.byte = 0xF1;
  cout << "low: " << hex << (int)un.btest.low << endl;
  cout << "high: " << hex << (int)un.btest.high << endl;

  INSTRUCTION ins {};
  ins.machine_code = 0x710F;

  cout << "uint16_t: " << hex << (int)(ins.machine_code) << endl;
  cout << "bytes[0]: " << hex << (int)(ins.bytes[0]) << endl;
  cout << "bytes[1]: " << hex << (int)(ins.bytes[1]) << endl;

  cout << "cop: " << hex << (int)(ins.bin_ins.high.cop) << endl;
  cout << "dst: " << hex << (int)(ins.bin_ins.high.dst) << endl;
  cout << "cnst: " << hex << (int)(ins.bin_ins.high.cnst) << endl;

  cout << "low byte: " << hex << setw(2) << setfill('0') << (int)(ins.bin_ins.low.Const) << endl;

  if (argc == 1) {
    cout << "74hcpu emulator" << endl;
    cout << "using: emul <firmware.hex>" << endl;
    return 0;
  }

  ifstream f(argv[1], ios::binary);
  if (!f) {
    cout << "Can't open file: " << argv[1] << endl;
    return 1;
  }

  // get length of file:
  f.seekg(0, f.end);
  size_t flen = f.tellg();
  f.seekg(0, f.beg);

  if (flen % 2) {
    cout << "File size should be even but: " << flen << endl;
    return 1;
  }

  // TODO: will it work on big-endian?
  //vector<ROM_DATA> buf(flen / 2, 0);
  //cout << "flen: " << flen << ", v.size: " << buf.size() << endl;

  //f.read(reinterpret_cast<char*>(&buf[0]), buf.size()*sizeof(ROM_DATA));
  f.close();

  try {
    test_emul();
  }
  catch (exception& e) {
    cout << "Error: " << e.what() << endl;
  }

  return 0;
}

/*
  Reg r0;
  r0 = 10;
  cout << "r0: " << r0 << endl;

  Reg r1;
  r1 = 0;
  cout << "r1: " << r1 << endl;

  LCD lcd;
  lcd.Connect(&r0, &r1);
  cout << "LCD: " << lcd << endl;

  const char* buf = "74hcpu";
  for (int i = 0; buf[i] != 0; i++) {
    r0 = buf[i];
    cout << "LCD: " << lcd << endl;
  }
*/
