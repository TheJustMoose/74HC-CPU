#include <iostream>
#include "lcd.h"
#include "emul.h"

using namespace std;

int main(int argc, char* argv[]) {
  if (argc == 1) {
    cout << "74hcpu emulator" << endl;
    cout << "using: emul <firmware.hex>" << endl;
  }
}
