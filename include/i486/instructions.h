#ifndef _REWIND_INSTRUCTIONS_H_
#define _REWIND_INSTRUCTIONS_H_

// defines all instruction types
#include <cstdint>
typedef enum InstructionName {

    ADD_Eb_Gb,
    ADD_Ev_Gv,
    ADD_Gb_Eb,
    ADD_Gv_Ev,
    ADD_AL_Ib,
    ADD_eAX_Iv,
    PUSH_ES,
    POP_ES



} InstructionName;

// TODO mod_rm for know is temprory
// define some more fields or asses the use of this struct
// or remove if not needed
typedef struct InstructionInfo {

    uint8_t mod_rm;

} InstructionInfo;
#endif
