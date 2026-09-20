#include "i486/instructions.h"

int one_byte_opcodetable[16][16] = {

    {ADD_Eb_Gb, ADD_Ev_Gv, ADD_Gb_Eb, ADD_Gv_Ev, ADD_AL_Ib, ADD_eAX_Iv, PUSH_ES,
     POP_ES, OR_Eb_Gb, OR_Ev_Gv, OR_Gb_Eb, OR_Gv_Ev, OR_AL_Ib, OR_eAX_Iv,
     PUSH_CS, TWO_BYTE_ESCAPE},

    {ADC_Eb_Gb, ADC_Ev_Gv, ADC_Gb_Eb, ADC_Gv_Ev, ADC_AL_Ib, ADC_eAX_Iv, PUSH_SS,
     POP_SS, SBB_Eb_Gb, SBB_Ev_Gv, SBB_Gb_Eb, SBB_Gv_Ev, SBB_AL_Ib, SBB_eAX_Iv,
     PUSH_DS, POP_DS},

    {AND_Eb_Gb, AND_Ev_Gv, AND_Gb_Eb, AND_Gv_Ev, AND_AL_Ib, AND_eAX_Iv,
     SEG_EQ_ES, DAA, SUB_Eb_Gb, SUB_Ev_Gv, SUB_Gb_Eb, SUB_Gv_Ev, SUB_AL_Ib,
     SUB_eAX_Iv, SEG_EQ_CS, DAS},

    {XOR_Eb_Gb, XOR_Ev_Gv, XOR_Gb_Eb, XOR_Gb_Ev, XOR_AL_Ib, XOR_eAX_Iv,
     SEG_EQ_SS, AAA, CMP_Eb_Gb, CMP_Ev_Gv, CMP_Gb_Eb, CMP_Gv_Ev, CMP_AL_Ib,
     CMP_eAX_Iv, SEG_EQ_DS, AAS},

    {INC_eAX, INC_eCX, INC_eDX, INC_eBX, INC_eSP, INC_eBP, INC_eSI, INC_eDI,
     DEC_eAX, DEC_eCX, DEC_eDX, DEC_eBX, DEC_eSP, DEC_eBP, DEC_eSI, DEC_eDI},
    {PUSH_eAX, PUSH_eCX, PUSH_eDX, PUSH_eBX, PUSH_eSP, PUSH_eBP, PUSH_eSI,
     PUSH_eDI, POP_eAX, POP_eCX, POP_eDX, POP_eBX, POP_eSP, POP_eBP, POP_eSI,
     POP_eDI},

    {PUSHA, POPA, BOUND_Gv_Ma, ARPL_Ew_Rw, SEG_EQ_FS, SEG_EQ_GS,
     ATTR_Operand_Size, ATTR_Address_Size, PUSH_Iv, IMUL_GvEvIv, PUSH_Ib,
     IMULGvEvIb, INSB_Yb_DX, INSW__D__Yv_DX, OUTSB_DX_Xb, OUTSW__D__DX_Xv},
    {Jb_JO, Jb_JNO, Jb_JB, Jb_JNB, Jb_JZ, Jb_JNZ, Jb_JBE, Jb_JNBE, Jb_JS,
     Jb_JNS, Jb_JP, Jb_JNP, Jb_JL, Jb_JNL, Jb_JLE, Jb_JNLE},
    {IMM_Grp1_Eb_Ib, IMM_Grp1_Ev_Iv, MOVB_AL_imm8, Grp1_Ev_Ib, TEST_Eb_Gb,
     TEST_Ev_Gv, XCHG_Eb_Gb, XCHG_Ev_Gv, MOV_Eb_Gb, MOV_Ev_Gv, MOV_Gb_Eb,
     MOV_Gv_Ev, MOV_Ew_Sw, LEA_Gv_M, MOV_Sw_Ew, POP_Ev},

    {NOP, XCHG_eCX, XCHG_eDX, XCHG_eBX, XCHG_eSP, XCHG_eBP, XCHG_eSI, XCHG_eDI,
     CBW, CWD, CALL_Ap, WAIT, PUSHF_Fv, POPF_Fv, SAHF, LAHF},

    {MOV_AL_Ob, MOV_eAX_Ov, MOV_Ob_AL, MOV_Ov_eAX, MOVSB_Xb_Yb, MOVSW__D__Xv_Yv,
     CMPSB_Xb_Yb, CMPSW__D__Xv_Yv, TEST_AL_Ib, TEST_eAX_Iv, STOSB_Yb_AL,
     STOSW__D__Yv_eAX, LODSB_AL_Xb, LODSW__D__eAX_Xv, SCASB_AL_Xb,
     SCASW__D__eAX_Xv},

    {MOV_AL, MOV_CL, MOV_DL, MOV_BL, MOV_AH, MOV_CH, MOV_DH, MOV_BH, MOV_eAX,
     MOV_eCX, MOV_eDX, MOV_eBX, MOV_eSP, MOV_eBP, MOV_eSI, MOV_eDI},

    {
        Shift_Grp2_Eb_Ib,
        Shift_Grp2_Ev_Ib,
        RET_near_Iw,
        RES_Or_INVALID_OP,
        LES_Gv_Mp,
        LDS_Gv_Mp,
        MOV_Eb_Ib,
        MOV_Ev_Iv,
        ENTER_Iw_iB,
        LEAVE,
        RET_far_Iw,
        RES_Or_INVALID_OP,
        INT_3,
        INT_Ib,
        INTO,
        IRET,
    },
    {
        Shift_Grp2_Eb_1,
        Shift_Grp2_Ev_1,
        Shift_Grp2_Eb_CL,
        Shift_Grp2_Ev_CL,
        AAM,
        AAD,
        RES_Or_INVALID_OP,
        XLAT,
        ESC_COP,
        ESC_COP,
        ESC_COP,
        ESC_COP,
        ESC_COP,
        ESC_COP,
        ESC_COP,
        ESC_COP,
    },

    {LOOPNE_Jb, LOOPE_Jb, LOOP_Jb, JCXZ_Jb, IN_Al_Ib, IN_eAX_Ib, OUT_Ib_AL,
     OUT_Ib_eAX, CALL_Jv, JMP_JV, JMP_AP, JMP_Jb, IN_AL_DX, IN_eAX_DX,
     OUT_DX_AL, OUT_DX_eAX},
    {LOCK, RES_Or_INVALID_OP, REPNE, REP_REPE, HLT, CMC, Unary_Grp3_Eb,
     Unary_Grp3_Ev, CLC, STC, CLI, STI, CLD, STD, INC_Or_DEC_Grp4,
     INC_Or_DEC_Grp5},
};
int two_byte_opcodetable[16][16] = {};

int group_opcodetable[16][8] = {};
