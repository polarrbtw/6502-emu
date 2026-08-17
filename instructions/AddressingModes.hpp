#include "../cpu/CPUContext.hpp"

namespace AddressingModes {

// todo:
// fix inconsistencies with variable names

// Immediate
inline u16 IMM(CPUContext &ctx) {
  u16 pc = ctx.regs.PC;
  ctx.regs.PC++;
  return pc;
}

// Implied
inline u16 IMP(CPUContext &) { return 0; }

// Zero Page
inline u16 ZP(CPUContext &ctx) {
  u16 base = ctx.bus.read(ctx.regs.PC);
  ctx.regs.PC++;
  return base;
}

// Zero Page, X
inline u16 ZPX(CPUContext &ctx) {
  u8 base = ctx.bus.read(ctx.regs.PC);
  ctx.regs.PC++;
  base += ctx.regs.X;
  return static_cast<u16>(base);
}

// Zero Page, Y
inline u16 ZPY(CPUContext &ctx) {
  u8 base = ctx.bus.read(ctx.regs.PC);
  ctx.regs.PC++;
  base += ctx.regs.Y; // another way to wrap like in indexed indirect
  return static_cast<u16>(base);
}

// Relative
inline u16 RL(CPUContext &ctx) {
  // bytes must be a signed 8bit integer
  i32 bytes = static_cast<i8>(ctx.bus.read(ctx.regs.PC));
  ctx.regs.PC++;
  return static_cast<u16>(ctx.regs.PC + bytes);
}

// Absolute
inline u16 ABS(CPUContext &ctx) {
  u16 base = ctx.bus.readWord(ctx.regs.PC);
  ctx.regs.PC += 2;
  return base;
}

// Absolute, X
inline u16 ABSX(CPUContext &ctx) {
  u16 base = ABS(ctx);
  u16 target = base + ctx.regs.X;
  // compare high bytes
  ctx.pageCrossed = (base >> 8) != (target >> 8);

  return target;
}

// Absolute, Y
inline u16 ABSY(CPUContext &ctx) {
  u16 base = ABS(ctx);
  u16 target = base + ctx.regs.Y;
  // compare high bytes
  ctx.pageCrossed = (base >> 8) != (target >> 8);

  return target;
}

// Indirect
inline u16 INDIRECT(CPUContext &ctx) {
  u16 ptr = ctx.bus.readWord(ctx.regs.PC);
  ctx.regs.PC += 2; // since both operands are next to the opcode - reading from
                    // instruction stream

  return ctx.bus.readWord(ptr);
}

// Indexed Indirect, only used with X register
inline u16 IINDIRECTX(CPUContext &ctx) {
  // LDA ($20, X) <-- get $20 (val)
  u8 val = ctx.bus.read(ctx.regs.PC);
  ctx.regs.PC++;
  u8 base = (val + ctx.regs.X) & 0xFF;
  // wrapping from
  // https://emulator101.mirror.simoni.dev/6502-addressing-modes.html
  return ctx.bus.readWord(base);
}

// Indirect Indexed, only used with Y register
inline u16 IINDIRECTY(CPUContext &ctx) {
  // LDA ($86),Y <-- get $86 (val)
  u8 val = ctx.bus.read(ctx.regs.PC);
  ctx.regs.PC++;
  u16 base = ctx.bus.readWord(
      val); // reading from zero page memory so no need to increment PC
  u16 target = base + ctx.regs.Y;
  // compare high bytes
  ctx.pageCrossed = (base >> 8) != (target >> 8);

  return target;
}

} // namespace AddressingModes
