#ifndef _REWIND_i486_BUS_H
#define _REWIND_i486_BUS_H

#include <stdint.h>
#include "cpu.h"
#include "memory.h"



typedef struct Bus {
    bool high_fetch; // this controls how linear address is calculated after reset in real mode
    bool a20_gate;  // a20 gate controls address wrap arround for real mode
    Cpu *cpu;
    Memory *mem;

} Bus;

bool init_bus(Bus *bus);

uint8_t fetch_inst(Bus *bus);

#endif
