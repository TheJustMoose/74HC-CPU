#include "lcd.h"
#include "emul.h"

using namespace std;

void LCD::Connect(Reg* data_reg, Reg* ctrl_reg) {
  data_reg_ = data_reg;
  ctrl_reg_ = ctrl_reg;
  if (data_reg_)
    data_reg_->Subscribe(this);
}

void LCD::Latch(uint8_t Data, bool CmdOrData) {
  if (CmdOrData)  // skip CMDs
    return;
  content_ += static_cast<char>(Data);
}

void LCD::OnChange(Subject*) {
  if (!data_reg_)
    return;
  if (!ctrl_reg_)
    return;
  // bit 0 in control register mean "Control or Data"
  Latch(*data_reg_, static_cast<uint8_t>(*ctrl_reg_) & 0x01);
}
