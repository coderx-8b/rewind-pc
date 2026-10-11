#ifndef _REWIND_I486_MEMORY_H_
#define _REWIND_I486_MEMORY_H_

#include <stdint.h>

typedef struct Memory {
  uint8_t *sys_bios;
  uint8_t *high_ram;
  uint8_t *low_ram;

} Memory;

typedef struct MemConfig {
  const char *bios_path;
  uint8_t installed_ram;

} MemConfig;

void init_memory(Memory *mem, MemConfig *conf);

uint8_t mem_get_byte(Memory *mem, uint32_t addr);

#endif
