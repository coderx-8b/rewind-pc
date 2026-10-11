#include "i486/bus.h"
#include "i486/exceptions.h"

// protection enable bit | 0 - Real Mode , 1 - Protected mode
#define PE(CR0) (CR0 & 1)

// NOTE: instruction fetch default to CS segment selector

// TODO: Exceptions, see when to generate exceptions
uint8_t fetch_inst(Bus *bus) {
  const Cpu *cpu = bus->cpu;

  uint32_t linear_addr = 0;

  if (PE(cpu->cr0) == 0) {
    // processor in real mode

    // NOTE: by default the limit is 0xFFFF in real mode
    if (cpu->eip > 0xFFFF) {
      // TODO: generate General protection exception
      generate_gp(bus);
    }

    // TODO: check for other way to do this like seprate fuction
    if (bus->high_fetch) {
      linear_addr = cpu->cs.base_addr + cpu->eip;
    } else {
      linear_addr = ((uint32_t)cpu->cs.selector << 4) + cpu->eip;
    }
    return mem_get_byte(bus->mem, linear_addr);
  }

  return 0xFF;
}
