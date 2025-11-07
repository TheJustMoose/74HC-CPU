#include <doctest.h>

#include "assm.h"

using namespace std;

TEST_CASE("check names getter") {
  CHECK(Names::RegFromName("Rx") == rUnkReg);

  CHECK(Names::RegFromName("R0") == rR0);
  CHECK(Names::RegFromName("R1") == rR1);
  CHECK(Names::RegFromName("R2") == rR2);
  CHECK(Names::RegFromName("R3") == rR3);
  CHECK(Names::RegFromName("R4") == rR4);
  CHECK(Names::RegFromName("R5") == rR5);
  CHECK(Names::RegFromName("R6") == rR6);
  CHECK(Names::RegFromName("R7") == rR7);

  CHECK(Names::RegFromName("XL") == rXL);
  CHECK(Names::RegFromName("XH") == rXH);
  CHECK(Names::RegFromName("YL") == rYL);
  CHECK(Names::RegFromName("YH") == rYH);
  CHECK(Names::RegFromName("ZL") == rZL);
  CHECK(Names::RegFromName("ZH") == rZH);
  CHECK(Names::RegFromName("SPL") == rSPL);
  CHECK(Names::RegFromName("SPH") == rSPH);

  bool inc, dec;
  CHECK(Names::PtrFromName("SP", &inc, &dec) == rSP);
  CHECK(!inc); CHECK(!dec);

  CHECK(Names::PtrFromName("SPI", &inc, &dec) == rSP);
  CHECK(inc); CHECK(!dec);

  CHECK(Names::PtrFromName("SPD", &inc, &dec) == rSP);
  CHECK(!inc); CHECK(dec);
}
