#include "i486/cpu.h"
#include <stdint.h>



// high byte in low word of a register
static inline void slwhb(uint32_t *reg, uint8_t val) {
    *reg = (*reg & 0xFFFF00FF) | ((val << 8)&0xFF00);
}

static inline void slw(uint32_t *reg, uint16_t val) {
    *reg = (*reg & 0xFFFF0000) | val;
}

static inline void slwlb(uint32_t *reg, uint8_t val) {
    *reg = (*reg & 0xFFFFFF00) | val;
}

#define SET_DH(val) slwhb(&cpu->edx, val)
#define SET_DL(val) slwlb(&cpu->edx, val)
#define SET_DX(val) slw(&cpu->edx, val)
#define SET_AX(val) slw(&cpu->eax, val)
#define SET_AH(val) slwhb(&cpu->eax, val)
#define SET_AL(val) slwlb(&cpu->eax, val)
#define SET_CX(val) slw(&cpu->ecx, val)
#define SET_CH(val) slwhb(&cpu->ecx, val)
#define SET_CL(val) slwlb(&cpu->ecx, val)
#define SET_BX(val) slw(&cpu->ebx, val)
#define SET_BH(val) slwhb(&cpu->ebx, val)
#define SET_BL(val) slwlb(&cpu->ebx, val)

#define SET_BP(val) slw(&cpu->ebp, val)
#define SET_SI(val) slw(&cpu->esi, val)
#define SET_DI(val) slw(&cpu->edi, val)
#define SET_SP(val) slw(&cpu->esp, val)


// Returns false if initialization fails or true on success
bool init_cpu(Cpu *cpu, Bus *bus) {

    if (cpu == nullptr || bus == nullptr) return false;

    cpu->eip = 0x0000FFF0;
    cpu->eflags = 0x00000002;
    cpu->eax = 0x0;
    SET_DH(0x04);
    cpu->cr0 = 0x60000010;
    cpu->dr7 = 0x00000400;

    cpu->cs.selector = 0xF000;
    cpu->cs.base_addr = 0xFFFF0000;
    cpu->cs.limit = 0xFFFF;
    cpu->cs.attrs = 0x9B;

    cpu->ds.selector = 0x0;
    cpu->ds.base_addr = 0x0;
    cpu->ds.limit = 0xFFFF;
    cpu->ds.attrs = 0x93;


    cpu->ss.selector = 0x0;
    cpu->ss.base_addr = 0x0;
    cpu->ss.limit = 0xFFFF;
    cpu->ss.attrs = 0x93;

    cpu->es.selector = 0x0;
    cpu->es.base_addr = 0x0;
    cpu->es.limit = 0xFFFF;
    cpu->es.attrs = 0x93;
    

    cpu->fs.selector = 0x0;
    cpu->fs.base_addr = 0x0;
    cpu->fs.limit = 0xFFFF;
    cpu->fs.attrs = 0x93;

    cpu->gs.selector = 0x0;
    cpu->gs.base_addr = 0x0;
    cpu->gs.limit = 0xFFFF;
    cpu->gs.attrs = 0x93;

    cpu->idtr.base_addr = 0x0;
    cpu->idtr.limit = 0x03FF;
    cpu->gdtr.base_addr = 0x0;

    cpu->ldtr.selector = 0x0;
    cpu->tr.selector = 0x0;

    return true;

}
