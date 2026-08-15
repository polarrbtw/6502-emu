#pragma once
#include "Types.hpp"

struct Flags {
  u8 CF : 1; // carry flag
  u8 ZF : 1; // zero flag
  u8 ID : 1; // interrupt disable
  u8 DM : 1; // decimal mode
  u8 BC : 1; // break command
  u8 OF : 1; // overflow flag
  u8 NF : 1; // negative flag

  // Helpers
  void updateNZ(u8 value) {
    ZF = (value == 0);
    NF = (value & 0b10000000) > 0;
    // 0x80 = 10000000 - bits from right to left 0,7 (8 bits)
  }
};
