#include "Instructions.hpp"

namespace Instructions {

// AND - Logical AND
void AND(CPUContext &ctx, u16 addr) {
  u8 data = ctx.bus.read(addr);
  u8 result = ctx.regs.A & data;
  ctx.regs.A = result;
  ctx.regs.flags.updateNZ(ctx.regs.A);
}

// EOR - Exclusive OR
void EOR(CPUContext &ctx, u16 addr) {
  u8 data = ctx.bus.read(addr);
  u8 result = ctx.regs.A ^ data;
  ctx.regs.A = result;
  ctx.regs.flags.updateNZ(ctx.regs.A);
}

// ORA - Logical Inclusive OR
void ORA(CPUContext &ctx, u16 addr) {
  u8 data = ctx.bus.read(addr);
  u8 result = ctx.regs.A | data;
  ctx.regs.A = result;
  ctx.regs.flags.updateNZ(ctx.regs.A);
}

// BIT - Bit Test
void BIT(CPUContext &ctx, u16 addr) {
  u8 data = ctx.bus.read(addr);
  u8 result = ctx.regs.A & data;
  ctx.regs.flags.ZF = result == 0;
  ctx.regs.flags.OF = std::bitset<8>(data)[6];
  ctx.regs.flags.NF = std::bitset<8>(data)[7];
}
} // namespace Instructions
