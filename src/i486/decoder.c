#include "i486/cpu.h"
#include "i486/instructions.h"

extern InstructionName one_byte_opcodetable[0xF][0xF];
extern InstructionName two_byte_opcodetable[0xF][0xF];

// extra for imm_grp1_Eb_Ib and Ev_Iv etc. instructions
extern InstructionName group_opcodetable[][0x8];


#define Get_Grp_Index(inst_name) (inst_name - Default_grp_value)

InstructionName decode(Cpu *cpu, uint8_t op, InstructionInfo *inst_info) {
  inst_info->mod_rm = 0;
  int index = 0;

  int row_in_op = 0, col_in_op = 0;
  InstructionName inst_name;
  if (op == 0x0F) {
    // two byte opcode table
    op = mem_byte_fetch(cpu->bus, cpu->eip);
    row_in_op = (op >> 4);
    col_in_op = (op & 0xF);
    inst_name = two_byte_opcodetable[row_in_op][col_in_op];

    if (INST_IS_Grp678(inst_name)) {
        // instruction either of type grp6 7 or 8
        
        // mod/rm byte [5-3] selects the opcode in group 6
        op = mem_byte_fetch(cpu->bus, cpu->eip);
        inst_info->mod_rm = op;
        index = ((op >> 3) & 0x7);
        inst_name = group_opcodetable[Get_Grp_Index(inst_name)][index];
    }


  } else {
      // instruction is in one byte opcode table
    row_in_op = (op >> 4);
    col_in_op = (op & 0xF);

    inst_name = one_byte_opcodetable[row_in_op][col_in_op];
    if (INST_IS_Grp12345(inst_name)) {
        op = mem_byte_fetch(cpu->bus, cpu->eip);
        inst_info->mod_rm = op;
        index = ((op >> 3) & 0x7);
        inst_name = group_opcodetable[Get_Grp_Index(inst_name)][index];
    }
  }

  return inst_name;
}
