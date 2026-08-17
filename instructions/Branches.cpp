#include "Instructions.hpp"

namespace Instructions {

// branchIf sets addr to PC if condition is true

// Branch if carry flag clear
void BCC(CPUContext &ctx, u16 addr) {
  branchIf(ctx, ctx.regs.flags.CF == 0, addr);
}

// Branch if carry flag set
void BCS(CPUContext &ctx, u16 addr) {
  branchIf(ctx, ctx.regs.flags.CF == 1, addr);
}

// Branch if zero flag set
void BEQ(CPUContext &ctx, u16 addr) {
  branchIf(ctx, ctx.regs.flags.ZF == 1, addr);
}

// Branch if negative flag set
void BMI(CPUContext &ctx, u16 addr) {
  branchIf(ctx, ctx.regs.flags.NF == 1, addr);
}

// Branch if zero flag clear
void BNE(CPUContext &ctx, u16 addr) {
  branchIf(ctx, ctx.regs.flags.ZF == 0, addr);
}

// Branch if negative flag clear
void BPL(CPUContext &ctx, u16 addr) {
  branchIf(ctx, ctx.regs.flags.NF == 0, addr);
}

// Branch if overflow flag clear
void BVC(CPUContext &ctx, u16 addr) {
  branchIf(ctx, ctx.regs.flags.OF == 0, addr);
}

// Branch if overflow flag set
void BVS(CPUContext &ctx, u16 addr) {
  branchIf(ctx, ctx.regs.flags.OF == 1, addr);
}
} // namespace Instructions
