#include <iostream>
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
  }

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
}
