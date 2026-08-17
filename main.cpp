#include "vm/vm.hpp"

int main(int argc, char *argv[]) {
  if (argc < 2) {
    error("usage: %s <rom_file>", argv[0]);
    return 1;
  }

  VM vm;

  vm.LoadROM(argv[1], 0);

  // todo: run tests
  while (true) {
    vm.Step();
  }

  return 0;
}
