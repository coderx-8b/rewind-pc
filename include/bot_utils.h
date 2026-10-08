#ifndef _BOT_UTILS_H_
#define _BOT_UTILS_H_

#include <stddef.h>
typedef enum BotUtils_status {

    SUCCESS = 0,
    ERROR_LOADING_FILE,


} BotUtils_status;

BotUtils_status bot_load_bin_file(const char* file_path, void *buff, size_t buff_size);

#endif
