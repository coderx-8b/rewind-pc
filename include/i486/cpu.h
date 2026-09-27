#ifndef _REWIND_I486_CPU_H_
#define _REWIND_I486_CPU_H_

#include "instructions.h"
#include <stdint.h>

// Consider using this when you need to access other 16bit and 8bit parts of a
// register ex. #define AX   GET_LOW_WORD(eax) or #define AX(reg)
// GET_LOW_WORD(eax)

#define GET_LOW_BYTE(reg) (reg & 0xFFu)
#define GET_HIGH_BYTE(reg) ((reg >> 8) & 0xFFu)
#define GET_LOW_WORD(reg) (reg & 0xFFFFu)

// needs to be defined somewhere so cpu can have access to other components
// connected via bus
typedef struct Bus Bus;
// needs to be defined somewhere
uint8_t mem_byte_fetch(Bus *bus, uint32_t addr);
uint8_t mem_fetch_next_byte(Bus *bus);
uint16_t mem_word_fetch(Bus *bus, uint32_t addr);
uint32_t mem_dword_fetch(Bus *bus, uint32_t addr);

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

  // segment selectors
  struct {
    uint16_t selector;
    uint32_t base_addr;
    uint32_t limit;
    uint16_t attrs;
  } cs;
  struct {
    uint16_t selector;
    uint32_t base_addr;
    uint32_t limit;
    uint16_t attrs;
  } ss;
  struct {
    uint16_t selector;
    uint32_t base_addr;
    uint32_t limit;
    uint16_t attrs;
  } ds;

  struct {
    uint16_t selector;
    uint32_t base_addr;
    uint32_t limit;
    uint16_t attrs;
  } es;
  struct {
    uint16_t selector;
    uint32_t base_addr;
    uint32_t limit;
    uint16_t attrs;
  } fs;
  struct {
    uint16_t selector;
    uint32_t base_addr;
    uint32_t limit;
    uint16_t attrs;
  } gs;

  uint32_t eflags;
  uint32_t eip;

  // system and memory management registers
  struct {
    uint32_t base_addr;
    uint16_t limit;
  } gdtr;

  struct {
    uint32_t base_addr;
    uint16_t limit;
  } idtr;

  struct {
    uint16_t selector;
    uint32_t base_addr;
    uint32_t limit;
    uint16_t attrs;
  } ldtr;

  struct {
    uint16_t selector;
    uint32_t base_addr;
    uint32_t limit;
    uint16_t attrs;
  } tr;

  // control registers
  uint32_t cr0;
  uint32_t cr1;
  uint32_t cr2;
  uint32_t cr3;

  // debug registers
  uint32_t dr0;
  uint32_t dr1;
  uint32_t dr2;
  uint32_t dr3;
  uint32_t dr6;
  uint32_t dr7;

  uint32_t tr3;
  uint32_t tr4;
  uint32_t tr5;
  uint32_t tr6;
  uint32_t tr7;

} Cpu;

/*
 * op - opcode byte should be given to decoder
 * Note: If decoder fetches another byte for decoding
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

// Initializes the cpu to the default state of registers
bool init_cpu(Cpu *cpu, Bus *bus);

InstructionName decode(Cpu *cpu, uint8_t op, InstructionInfo *inst_info);

#endif
