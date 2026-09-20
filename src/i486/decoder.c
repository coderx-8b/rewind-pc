#include "i486/cpu.h"
#include "i486/instructions.h"

extern int one_byte_opcodetable[0xF][0xF];
extern int two_byte_opcodetable[0xF][0xF];

// extra for imm_grp1 instructions
extern int group_opcodetable[0x9][0x8];

InstructionName decode(Cpu *cpu, uint8_t op, InstructionInfo *inst_info) {

  int row_in_op = 0, col_in_op = 0;
  InstructionName inst_name;
  if (op == 0x0F) {
    // two byte opcode table
    op = mem_byte_fetch(cpu->bus, cpu->eip);
    row_in_op = (op >> 4);
    col_in_op = (op & 0xF);
    inst_name = two_byte_opcodetable[row_in_op][col_in_op];
    switch (inst_name) {
    case Grp6:
    case Grp7:
    case Grp8_Ev_Ib:
    default:
      return 0;
    }

  } else {
    row_in_op = (op >> 4);
    col_in_op = (op & 0xF);

    inst_name = one_byte_opcodetable[row_in_op][col_in_op];
    switch (inst_name) {
    case IMM_Grp1_Eb_Ib:
    case IMM_Grp1_Ev_Iv:
    case Grp1_Ev_Ib:
    case Shift_Grp2_Eb_1:
    case Shift_Grp2_Ev_1:
    case Shift_Grp2_Eb_CL:
    case Shift_Grp2_Ev_CL:
    case Unary_Grp3_Eb:
    case Unary_Grp3_Ev:
    case INC__DEC__Grp4:
    case INC__DEC__Grp5:
    default:
      return 0;
    }
  }

  return INVALID_OP;
}
