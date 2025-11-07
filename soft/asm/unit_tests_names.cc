#include <doctest.h>

#include "assm.h"

using namespace std;

TEST_CASE("check names getter") {
  CHECK(Names::RegFromName("R0") == rR0);
  CHECK(Names::RegFromName("R7") == rR7);
}
