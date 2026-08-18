# 6502 CPU Emulation

lightweight mos 6502 cpu emulator written in C++20

## features
- **full instruction set:** implemented all 56 documented 6502 opcodes
- **addressing modes:** support for all 13 addressing modes (Immediate, Zero Page, Absolute, Indirect, etc.)
- **opcode lookup table:** uses a lookup table to execute instructions instead of a switch statement
- **cpu context:** all components of the cpu are separated (registers, flags, and the bus/ram) and constructed in a vm class

## limitations
- **decimal mode:** decimal mode handling for `ADC` and `SBC` instructions hasn't been implemented.
- **testing:** all instructions asnd addressing modes have been fully coded, but haven't been fully tested.

## requirements
- C++20 compatible compiler (GCC, Clang or MSVC)
- CMake 3.20+

## compiling
```bash
git clone https://github.com/polarrbtw/6502-emu.git
cd 6502-emu
mkdir build && cd build
cmake ..
cmake -- build.
```
