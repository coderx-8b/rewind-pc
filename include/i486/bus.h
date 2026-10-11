#ifndef _REWIND_i486_BUS_H
#define _REWIND_i486_BUS_H

#include <stdint.h>


typedef struct Cpu Cpu;
typedef struct Memory Memory;

typedef struct Bus {
    Cpu *cpu;
    Memory *mem;

} Bus;

uint8_t fetch_inst(Bus *bus);

#endif
