#include <i486/mmu.h>
#include <i486/exceptions.h>

uint32_t gen_rm_addr(Bus *bus){

    uint32_t addr = 0;
    const Cpu *cpu = bus->cpu;

    if (cpu->eip > 0xFFFF) {
      // TODO: generate General protection exception (do again after basics are
      // implemented)
      generate_gp(bus); // TODO: temprory impl
    }

    if (bus->high_fetch) {
      addr = cpu->cs.base_addr + cpu->eip;
    } else {
      addr = ((uint32_t)cpu->cs.selector << 4) + cpu->eip;
    }
    return addr;
}

uint32_t gen_pm_addr(Bus *bus) {

    return 0x00;
}
