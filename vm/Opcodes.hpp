#pragma once
#include "../cpu/CPUContext.hpp"
#include <array>

// addressing mode
// instruction
// cycles

using addrFunc = u16 (*)(CPUContext &);
using instrFunc = void (*)(CPUContext &, u16 addr);

struct Opcode {
  addrFunc addrMode;
  instrFunc instr;
  u8 cycles;
  bool pageCross = false;
};

extern const std::array<Opcode, 256> OpcodeTable;
