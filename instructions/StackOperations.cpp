#include "Instructions.hpp"

namespace Instructions {

// TSX - Transfer Stack Pointer to X
void TSX(CPUContext &ctx, u16 addr) {
  ctx.regs.X = ctx.regs.SP;
  ctx.regs.flags.updateNZ(ctx.regs.X);
}

// TXS - Transfer X to Stack Pointer
void TXS(CPUContext &ctx, u16 addr) { ctx.regs.SP = ctx.regs.X; }

// PHA - Push Accumulator
void PHA(CPUContext &ctx, u16 addr) { push8(ctx, ctx.regs.A); }

// Push Processor Status
void PHP(CPUContext &ctx, u16 addr) { push8(ctx, ctx.regs.flags.packFlags()); }

// PLA - Pull Accumulator
void PLA(CPUContext &ctx, u16 addr) {
  u8 value = pop8(ctx);
  ctx.regs.A = value;
  ctx.regs.flags.updateNZ(ctx.regs.A);
}

// PLP - Pull Processor Status
void PLP(CPUContext &ctx, u16 addr) {
  u8 procStatus = pop8(ctx);
  ctx.regs.flags.unpackFlags(procStatus);
  ctx.regs.flags.BC = 0; // should be 0 apparently
  // although doesnt matter since nothing can access BC
}

} // namespace Instructions
