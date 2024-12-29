#include <fstream>
#include <iostream>
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

  ROM rom;
  rom.Flash(std::move(buf));

  cout << "max ROM addr: " << rom.GetMaxAddress() << endl;
  ROM_DATA d = rom.Read(0);
  cout << "First word: " << hex << d << endl;

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
