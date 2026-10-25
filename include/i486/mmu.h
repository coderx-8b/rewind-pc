#ifndef _REWIND_I486_MMU_H_
#define _REWIND_I486_MMU_H_
#include "i486/bus.h"
#include <stdint.h>

uint32_t gen_rm_addr(Bus *bus);
uint32_t gen_pm_addr(Bus *bus);
#endif
