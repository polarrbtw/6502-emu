#include "Instructions.hpp"

namespace Instructions {

// BRK - https://www.masswerk.at/6502/6502_instruction_set.html#BRK

// BRK - Force an interrupt
void BRK(CPUContext &ctx, u16 addr) {
  push16(ctx, ctx.regs.PC + 2); // skip BRK & break mark (reason for the break)
  ctx.regs.flags.BC = 1;        // break flag
  push8(ctx, ctx.regs.flags.packFlags());

  ctx.regs.PC = ctx.bus.readWord(0xFFFE);
}

// NOP - No Operation
void NOP(CPUContext &ctx, u16 addr) { return; }

// RTI - Return from Interrupt
void RTI(CPUContext &ctx, u16 addr) {
  u8 procStatus = pop8(ctx); // procStatus - flags
  ctx.regs.PC = pop16(ctx);

  ctx.regs.flags.unpackFlags(procStatus);
  ctx.regs.flags.BC = 0;
}

} // namespace Instructions
