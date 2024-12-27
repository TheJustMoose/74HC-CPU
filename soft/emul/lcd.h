#pragma once

#include <string>

#include "observer.h"

class Reg;

class LCD : public Observer {
public:
  void Connect(Reg* data_reg, Reg* ctrl_reg);

  void Latch(uint8_t Data, bool CmdOrData);
  std::string Content() const {
    return content_;
  }

  void OnChange(Subject*) override;

private:
  std::string content_;
  Reg* data_reg_ {nullptr};
  Reg* ctrl_reg_ {nullptr};
};
