#include "Instructions.hpp"

namespace Instructions {

// Increment a memory location
void INC(CPUContext &ctx, u16 addr) {
  u8 data = ctx.bus.read(addr);
  data += 1;
  ctx.bus.write(addr, data);
  ctx.regs.flags.updateNZ(data);
}

// Increment the X register
void INX(CPUContext &ctx, u16 addr) {
  ctx.regs.X += 1;
  ctx.regs.flags.updateNZ(ctx.regs.X);
}

// Increment the Y register
void INY(CPUContext &ctx, u16 addr) {
  ctx.regs.Y += 1;
  ctx.regs.flags.updateNZ(ctx.regs.Y);
}

// Decrement a memory location
void DEC(CPUContext &ctx, u16 addr) {
  u8 data = ctx.bus.read(addr);
  data -= 1;
  ctx.bus.write(addr, data);
  ctx.regs.flags.updateNZ(data);
}

// Decrement the X register
void DEX(CPUContext &ctx, u16 addr) {
  ctx.regs.X -= 1;
  ctx.regs.flags.updateNZ(ctx.regs.X);
}

// Decrement the Y register
void DEY(CPUContext &ctx, u16 addr) {
  ctx.regs.Y -= 1;
  ctx.regs.flags.updateNZ(ctx.regs.Y);
}

} // namespace Instructions
