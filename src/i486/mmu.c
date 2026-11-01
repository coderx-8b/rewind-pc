#include <i486/mmu.h>
#include <i486/cpu.h>
#include <i486/exceptions.h>

#define Default_Operation_Size(attr)    ((attr >> 6) & 1)
#define IP(reg) GET_LOW_WORD(reg)

static void inline apply_a20_gate(bool a20_gate, uint32_t *addr) {
    if (!a20_gate) {
        *addr = (*addr) & (uint32_t)(~0x00010000);
    }
}



// This function genereate real mode address 
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
    apply_a20_gate(bus->a20_gate, &addr);
    return addr;
}

// This function generate protected mode address

uint32_t gen_pm_addr(Bus *bus) {

    uint32_t addr = 0;
    const Cpu *cpu = bus->cpu;

    // TODO: Do limit check correctly

    addr = cpu->cs.base_addr;
    if (Default_Operation_Size(cpu->cs.attrs)) {
        addr += cpu->eip;
    } else {
        addr += IP(cpu->eip);
    }

    return 0x00;
}
