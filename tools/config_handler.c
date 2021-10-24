/* config_handler.c */
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

#include <config/config_handler.h>
#include <mem/mem.h>

#define CONFIG_PATH "/.local/share/file_sorter/config/config.conf"

static int get_config(int flag, size_t *config_len) {
    char *username = getlogin();
    size_t config_path_s = strlen(CONFIG_PATH) + strlen(username) + strlen("home") + 3;
    char config_path[config_path_s];
    struct stat config_stat;
    int fd;

    strcpy(config_path, "/home/");
    strcat(config_path, username);
    strcat(config_path, CONFIG_PATH);

    fd = open(config_path, flag);

    if (config_len != NULL) {
        if (lstat(config_path, &config_stat) == -1) {
            *config_len = -1;
            return fd;
        }
        *config_len = config_stat.st_size;
    }

    return fd;
}


int write_config(char *changes, size_t changesLen) {
    int config_fd = get_config(O_RDWR | O_TRUNC, NULL);

    if (config_fd == -1) return config_fd;
    if (write(config_fd, changes, changesLen) == -1) return -1;

    close(config_fd);
    return 0;
}

char *read_config() {
    size_t config_len = 0;
    int config_fd = get_config(O_RDONLY, &config_len);

    if (config_fd == -1) return NULL;
    if (config_len == -1) return NULL;

    char *buffer;
    ALLOCATE_MEMORY(buffer, config_len + 1, sizeof(char));
    if (read(config_fd, buffer, config_len) == -1) {
        free(buffer);
        return NULL;
    }

    size_t config_content_s = config_len + 1;
    char *config_content = NULL;
    ALLOCATE_MEMORY(config_content, config_content_s, sizeof(char));
    strcpy(config_content, buffer);

    close(config_fd);

    free(buffer);
    return config_content;
}

