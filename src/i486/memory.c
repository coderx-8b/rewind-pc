#include <bot_utils.h>
#include <i486/memory.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <i486/bus.h>

#define _BOT_UTILS_DEBUG_
constexpr unsigned int KB = 1024;
constexpr unsigned int bios_buff_size = 128 * KB;
constexpr unsigned int MB = 1024 * KB;

static void inline apply_a20_gate(bool a20_gate, uint32_t *addr) {
    if (!a20_gate) {
        *addr = (*addr) & (uint32_t)(~0x00010000);
    }
}

void init_memory(Memory *mem, MemConfig *conf) {

  if (mem == nullptr || mem->bus == nullptr) {
    printf("init_memory() : *mem is null or *bus is null\n");
    return;
  }

  if (!conf) {
    printf("init_memory() : No config provided!\n");
    return;
  }

  // by default I will be using seabios 128kb

  mem->sys_bios = (uint8_t *)malloc(bios_buff_size);
  BotUtils_status status =
      bot_load_bin_file(conf->bios_path, mem->sys_bios, bios_buff_size);
  if (status == ERROR_LOADING_FILE)
    return;

  printf("%x\n", mem->sys_bios[131056]);

  // installed_ram must be in range 2-64
  mem->high_ram = (uint8_t *)malloc(conf->installed_ram * MB);

  printf("Initialized System Bios & High ram.\n");
}



uint8_t mem_get_byte(Memory *mem, uint32_t addr) {
    apply_a20_gate(mem->bus->a20_gate, &addr);

    // TODO: Apply memory map

    return 0xFF;
}



