#include "Instructions.hpp"

namespace Instructions {

// Arithmetic Shift Left
void ASL(CPUContext &ctx, u16 addr) {
  u8 data = ctx.bus.read(addr);
  ctx.regs.flags.CF = (data >> 7) & 1;
  data = data << 1; // shifting left by 1 multiplies by 2
  ctx.bus.write(addr, data);
  ctx.regs.flags.updateNZ(data);
}

void ASL_A(CPUContext &ctx, u16 addr) {
  u8 data = ctx.regs.A;
  ctx.regs.flags.CF = (data >> 7) & 1;
  data = data << 1;
  ctx.regs.A = data;
  ctx.regs.flags.updateNZ(data);
}

// Logical Shift Right
void LSR(CPUContext &ctx, u16 addr) {
  u8 data = ctx.bus.read(addr);
  ctx.regs.flags.CF = data & 1;
  data = data >> 1; // shifting right by 1 divides by 2
  ctx.bus.write(addr, data);
  ctx.regs.flags.updateNZ(data);
}

void LSR_A(CPUContext &ctx, u16 addr) {
  u8 data = ctx.regs.A;
  ctx.regs.flags.CF = data & 1;
  data = data >> 1;
  ctx.regs.A = data;
  ctx.regs.flags.updateNZ(data);
}

// Rotate Left
void ROL(CPUContext &ctx, u16 addr) {
  u8 data = ctx.bus.read(addr);
  u8 oldCF = ctx.regs.flags.CF;
  u8 dataBit7 = (data >> 7) & 1;
  data = data << 1;
  data = data | oldCF;
  ctx.bus.write(addr, data);
  ctx.regs.flags.CF = dataBit7;
  ctx.regs.flags.updateNZ(data);
}

void ROL_A(CPUContext &ctx, u16 addr) {
  u8 data = ctx.regs.A;
  u8 oldCF = ctx.regs.flags.CF;
  u8 dataBit7 = (data >> 7) & 1;
  data = data << 1;
  data = data | oldCF;
  ctx.regs.A = data;
  ctx.regs.flags.CF = dataBit7;
  ctx.regs.flags.updateNZ(data);
}

// Rotate Right
void ROR(CPUContext &ctx, u16 addr) {
  u8 data = ctx.bus.read(addr);
  u8 oldCF = ctx.regs.flags.CF;
  u8 dataBit0 = data & 1;
  data = data >> 1;
  data = data | (oldCF << 7);
  ctx.bus.write(addr, data);
  ctx.regs.flags.CF = dataBit0;
  ctx.regs.flags.updateNZ(data);
}

void ROR_A(CPUContext &ctx, u16 addr) {
  u8 data = ctx.regs.A;
  u8 oldCF = ctx.regs.flags.CF;
  u8 dataBit0 = data & 1;
  data = data >> 1;
  data = data | (oldCF << 7);
  ctx.regs.A = data;
  ctx.regs.flags.CF = dataBit0;
  ctx.regs.flags.updateNZ(data);
}
} // namespace Instructions
