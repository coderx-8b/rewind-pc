#include <bot_utils.h>
#include <i486/memory.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define _BOT_UTILS_DEBUG_
constexpr unsigned int KB = 1024;
constexpr unsigned int bios_buff_size = 128 * KB;
constexpr unsigned int MB = 1024 * KB;

void init_memory(Memory *mem, MemConfig *conf) {

  if (!mem) {
    printf("init_memory() : *mem is null\n");
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

  // installed_ram must be in range 2-64
  mem->high_ram = (uint8_t *)malloc(conf->installed_ram * MB);

  printf("Initialized System Bios & High ram.\n");
}
