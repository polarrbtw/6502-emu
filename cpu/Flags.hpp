#pragma once
#include "Types.hpp"
#include <bitset>

/* Order of bits for Processor Status (needed for packFlags)
B0 - Carry Flag
B1 - Zero Flag
B2 - Interrupt Disable Flag
B3 - Decimal Mode Flag
B4 - Break Command Flag
B5 - Unused (apparently always set to 1)
B6 - Overflow Flag
B7 - Result Negative Flag
*/

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

  u8 packFlags() {
    std::bitset<8> bits;
    // indexed from right to left 0-7

    bits.set(0, CF);
    bits.set(1, ZF);
    bits.set(2, ID);
    bits.set(3, DM);
    bits.set(4, BC);
    bits.set(5, 1); // unused, always set to 1
    bits.set(6, OF);
    bits.set(7, NF);

    return static_cast<u8>(bits.to_ulong());
  }

  void unpackFlags(u8 procStatus) {
    std::bitset<8> bits{procStatus};
    CF = bits[0];
    ZF = bits[1];
    ID = bits[2];
    DM = bits[3];
    BC = bits[4];
    OF = bits[6];
    NF = bits[7];
  }
};
