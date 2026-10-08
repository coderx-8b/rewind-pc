#include <i486/memory.h>
#include <stdio.h>

// TODO: Understand how the 80486 start the instruction and fetch

int main() {

  printf("Rewind is a IBM Pc emulator.\n");
  MemConfig config = {.bios_path =
                          "/home/bot/Projects/emulators/rewind/local/bios.bin",
                      .installed_ram = 8};
  Memory mem;
  init_memory(&mem, &config);
  return 0;
}
