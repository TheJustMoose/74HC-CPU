#pragma once

#include <string>

class LCD {
public:
  void Latch(uint8_t Data, bool CmdOrData);
  std::string Content() const;

private:
  std::string content_;
};
