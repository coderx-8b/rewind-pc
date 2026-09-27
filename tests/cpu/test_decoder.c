#include "i486/instructions.h"
#include <i486/cpu.h>
#include <i486/bus.h>
#include <stdint.h>
#include <stdio.h>
#include "test_decoder.h"

#define BUFF_SIZE 1024 * 1024

static uint8_t insts[BUFF_SIZE] = {};
int curr_inst = 0;





void load_insts(const char *file_name) {
    FILE *file = freopen(file_name, "r", stdin);

    if (!file) {
        printf("File cannot be opened %s in load_insts() from test_decoder\n", file_name);
        return;
    } 

    int c = fgetc(file);
    int i = 0;
    while(c != EOF && i < BUFF_SIZE) {
        insts[i++] = (uint8_t)c;
    }

    if (file != nullptr) {
        fclose(file);
    }
}

uint8_t mem_fetch_next_byte(Bus *_) {

    return insts[curr_inst++];

}

static InstructionName opcodes[] = {
    NOP,
    ADD_Eb_Gb,
    ADD_eAX_Iv,
    IMM_Grp1_ADD_Eb_Ib,
    ESC_COP,
    RET_far_Iw,
    RET_near_Iw,
    RES_Or_INVALID_OP,
    PUSH_ES,
    PUSH_eCX,
    PUSH_eBP,
    OR_Eb_Gb,
    Shift_Grp2_RCL_Eb_1,
    IMM_Grp1_AND_Ev_Iv,
    Grp1_ADC_Ev_Ib,
    CWD,
    Grp6__LTR_Ew,
    Grp7__LMSW_Ew,
    RES_Or_INVALID_OP,
    // MOVSX_Gv_Ew,
    // CMPXCHG_Eb_Gb


};


void test_decoder_default() {
    insts[0] = 0x90;
    insts[1] = 0x00;
    insts[2] = 0x05;
    // for IMM_Grp1_ADD_Eb_Ib
    insts[3] = 0x80;
    insts[4] = 0x00;

    insts[5] = 0xDC; // ESC_COP4
    insts[6] = 0xCA;    // RET_far_Iw
    insts[7] = 0xC2;    // RET_near_Iw
    insts[8] = 0xC3;    // RES_Or_INVALID_OP
    insts[9] = 0x06;    // PUSH_ES
    insts[10] = 0x51;   // PUSH_eCX
                        
    insts[11] = 0x55; // PUSH_eBP
    insts[12] = 0x08;   // OR_Eb_Gb
    insts[13] = 0xD0;   // Shift_Grp2_RCL_Eb_1
    insts[14] = 0b00010000; // mod_rm
    insts[15] = 0x81;   // IMM_Grp1_AND_Ev_Iv
    insts[16] = 0b00100000; // mod_rm
    insts[17] = 0x83;   // Grp1_ADC_Ev_Ib
    insts[18] = 0b00010000;
    insts[19] = 0x99;   // CWD

    // Two byte opcodes
    insts[20] = 0x0F;
    insts[21] = 0x00;   // Grp6_LTR_Ew
    insts[22] = 0b00011000;

    insts[23] = 0x0F;
    insts[24] = 0x01;       // Grp7_LMSW_Ew
    insts[25] = 0b00110000;

    insts[26] = 0x0F;
    insts[27] = 0x01;       // Grp7 invalid
    insts[28] = 0b00101000;

    insts[29] = 0x0F;
    insts[30] = 0xBF;   // MOVSX_Gv_Ew

    insts[31] = 0x0F;
    insts[32] = 0xA6;   // CMPXCHG_Eb_Gb

    Cpu cpu;
    Bus bus;
    bus.cpu = &cpu;
    cpu.eip = 0;
    cpu.bus = &bus;
    
    int sz = sizeof(opcodes) / sizeof(InstructionName);
    printf("Testing test_decoder_default for %d tests...\n", sz);
    int failed_cases = 0;
    for (int i = 0; i < sz; i++) {
        InstructionInfo info = {.mod_rm = 0};
        InstructionName name = decode(&cpu, insts[curr_inst++], &info);

        if (name != opcodes[i]) {
            printf("Failed at %d, expected %d but got %d\n", i+1, opcodes[i], name);
            ++failed_cases;
        }

    }

    printf("test_decoder_default failed cases %d\n", failed_cases);


}
