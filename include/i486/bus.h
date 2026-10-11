#ifndef _REWIND_i486_BUS_H
#define _REWIND_i486_BUS_H

#include <stdint.h>
#include "cpu.h"
#include "memory.h"



typedef struct Bus {
    bool high_fetch; // this controls how linear address is calculated after reset in real mode
    Cpu *cpu;
    Memory *mem;

} Bus;

uint8_t fetch_inst(Bus *bus);

#endif
