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

void test_emul() {
// Intel -> Little endian -> low byte is stored in low address
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

int main(int argc, char* argv[]) {
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
  vector<ROM_DATA> buf(flen / 2, 0);
  cout << "flen: " << flen << ", v.size: " << buf.size() << endl;

  f.read(reinterpret_cast<char*>(&buf[0]), buf.size()*sizeof(ROM_DATA));
  f.close();

  try {
    test_emul();
  }
  catch (exception& e) {
    cout << "Error: " << e.what() << endl;
  }

  return 0;
}
