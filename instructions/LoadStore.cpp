#include "Instructions.hpp"

namespace Instructions {

void LDA(CPUContext &ctx, u16 addr) { loadReg(ctx, ctx.regs.A, addr); }

void LDX(CPUContext &ctx, u16 addr) { loadReg(ctx, ctx.regs.X, addr); }

void LDY(CPUContext &ctx, u16 addr) { loadReg(ctx, ctx.regs.Y, addr); }

void STA(CPUContext &ctx, u16 addr) { storeReg(ctx, ctx.regs.A, addr); }

void STX(CPUContext &ctx, u16 addr) { storeReg(ctx, ctx.regs.X, addr); }

void STY(CPUContext &ctx, u16 addr) { storeReg(ctx, ctx.regs.Y, addr); }

} // namespace Instructions
