#include <bot_utils.h>
#include <stdio.h>

BotUtils_status bot_load_bin_file(const char *file_path, void *buff, size_t buff_size) {

    FILE *file = fopen(file_path, "rb");
    if (!file) {
#ifdef _BOT_UTILS_DEBUG_
        perror("bot_load_bin_file(): Error opening file.\n");
#endif
        return ERROR_LOADING_FILE;
    }

    size_t count = fread(buff, 1, buff_size, file);
    if (count != buff_size) {
#ifdef _BOT_UTILS_DEBUG_
        perror("bot_load_bin_file(): Loaded data may be of different size.\n");
#endif
        return ERROR_LOADING_FILE;
    }


    return SUCCESS;
}
