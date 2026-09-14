#ifndef _REWIND_I486_CPU_H_
#define _REWIND_I486_CPU_H_

#include "instructions.h"
#include <cstdint>


// Consider using this when you need to access other 16bit and 8bit parts of a register ex.
// #define AX   GET_LOW_WORD(eax)
// or #define AX(reg) GET_LOW_WORD(eax)

#define GET_LOW_BYTE(reg)   (reg & 0xFFu)
#define GET_HIGH_BYTE(reg)  ((reg >> 8) & 0xFFu)
#define GET_LOW_WORD(reg)   (reg & 0xFFFFu)


// needs to be defined somewhere
uint8_t mem_fetch(uint32_t addr);

// needs to be defined somewhere so cpu can have access to other components connected via bus
typedef struct Bus Bus;

typedef struct Cpu {

    Bus *bus;

    // general purpose registers

    uint32_t eax;
    uint32_t ebx;
    uint32_t ecx;
    uint32_t edx;
    uint32_t esi;
    uint32_t edi;
    uint32_t esp;
    uint32_t ebp;

    // segment registers
    uint16_t cs;
    uint16_t ss;
    uint16_t ds;
    uint16_t es;
    uint16_t fs;
    uint16_t gs;
    
    uint32_t eflags;
    uint32_t eip;


} Cpu;

/*
 * op - opcode byte should be given to decoder
 * Note: If decoder fetch another byte for decoding
 * instruction like instructions that use modrm byte 
 * for knowing full instruction type.
 * Or two byte opcodes that further needs another byte
 * modrm byte for knowing the type.
 * Than the fetched modrm byte will be stored in 
 * InstructionInfo struct
 *
 * TODO Asses the use of this InstructionInfo if needed or not
 * or if needed can more meta data info assign to it
 */

InstructionName decode(uint8_t op, InstructionInfo *inst_info);



#endif
