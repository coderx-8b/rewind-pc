#include "i486/bus.h"
#include "i486/mmu.h"

// protection enable bit | 0 - Real Mode , 1 - Protected mode
#define PE(CR0) (CR0 & 1)

bool init_bus(Bus *bus) {
  if (bus == nullptr || bus->mem == nullptr || bus->cpu == nullptr)
    return false;

  bus->a20_gate = true;
  bus->high_fetch = true;

  return true;
}

// NOTE: instruction fetch default to CS segment selector

// TODO: Exceptions, see when to generate exceptions
uint8_t fetch_inst(Bus *bus) {

  if (PE(bus->cpu->cr0) == 0) {
    // processor in real mode
    return mem_get_byte(bus->mem, gen_rm_addr(bus));
  } else {
    // in protected mode
    return mem_get_byte(bus->mem, gen_pm_addr(bus));
  }
  return 0xFF;
}
