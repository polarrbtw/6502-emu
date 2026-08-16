#include "Instructions.hpp"

namespace Instructions {

// ADC - Add with Carry
void ADC(CPUContext &ctx, u16 addr) {
  u8 data = ctx.bus.read(addr);
  u16 sum = ctx.regs.A + data + ctx.regs.flags.CF;
  u8 oldA = ctx.regs.A;
  ctx.regs.A = sum;
  ctx.regs.flags.CF = sum > 0xFF; // greater than 255 (0xFF)?
  ctx.regs.flags.updateNZ(ctx.regs.A);
  bool signA = (oldA >> 7) & 1; // sign of accumulator
  bool signD = (data >> 7) & 1; // sign of memory (data)
  bool signS = (sum >> 7) & 1;  // sign of sum

  // if sign of A and M match and if signA (or signM) doesnt match the sign of
  // the sum, then we have signed overflow
  // adding 2 positives always gives a positive, same with negatives
  ctx.regs.flags.OF = (signA == signD) && (signA != signS);
}

// SBC - Subtract with Carry
void SBC(CPUContext &ctx, u16 addr) {
  u8 data = ctx.bus.read(addr);
  data = ~data;
  u16 sum = ctx.regs.A + data + ctx.regs.flags.CF;
  u8 oldA = ctx.regs.A;
  ctx.regs.A = sum;
  ctx.regs.flags.CF = sum > 0xFF; // greater than 255 (0xFF)?
  ctx.regs.flags.updateNZ(ctx.regs.A);
  bool signA = (oldA >> 7) & 1; // sign of accumulator
  bool signD = (data >> 7) & 1; // sign of memory (data)
  bool signS = (sum >> 7) & 1;  // sign of sum

  // if sign of A and M match and if signA (or signM) doesnt match the sign of
  // the sum, then we have signed overflow
  // adding 2 positives always gives a positive, same with negatives
  ctx.regs.flags.OF = (signA == signD) && (signA != signS);
}

// CMP - Compare
void CMP(CPUContext &ctx, u16 addr) {
  u8 data = ctx.bus.read(addr);
  compareReg(ctx, ctx.regs.A, data);
}

// Compare X register
void CPX(CPUContext &ctx, u16 addr) {
  u8 data = ctx.bus.read(addr);
  compareReg(ctx, ctx.regs.X, data);
}

// Compare Y register
void CPY(CPUContext &ctx, u16 addr) {
  u8 data = ctx.bus.read(addr);
  compareReg(ctx, ctx.regs.Y, data);
}

} // namespace Instructions
