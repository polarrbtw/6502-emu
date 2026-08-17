#include "Instructions.hpp"

namespace Instructions {

// JMP - Jump
void JMP(CPUContext &ctx, u16 addr) { ctx.regs.PC = addr; }

// JSR - Jump to Subroutine
void JSR(CPUContext &ctx, u16 addr) {
  push16(ctx, addr - 1);
  ctx.regs.PC = addr;
}

// RTS - Return from subroutine
void RTS(CPUContext &ctx, u16 addr) {
  u16 target = pop16(ctx);
  ctx.regs.PC = (target + 1);
}

} // namespace Instructions
