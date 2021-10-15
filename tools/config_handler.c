/* config_handler.c */
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

#include <config/config_handler.h>

#define CONFIG_PATH "/.local/share/file_sorter/config/config.conf"

int get_config(int flag, size_t *config_len);

int write_config(char *changes, size_t changesLen) {
    int config_fd = get_config(O_RDWR | O_TRUNC, NULL);

    if (config_fd == -1) return config_fd;
    if (write(config_fd, changes, changesLen) == -1) return -1;

    close(config_fd);
    return 0;
}

int read_config(char **configContent) {
    size_t config_len;
    int config_fd = get_config(O_RDONLY, &config_len);
    char *buffer;

    if (config_fd == -1) return config_fd;
    if (config_len == -1) return (int) config_len;

    buffer = calloc(config_len, sizeof(char));
    if (read(config_fd, buffer, config_len) == -1)
        return -1;

    *configContent = calloc(config_len + 1, sizeof(char));
    strncpy(*configContent, buffer, config_len);

    free(buffer);
    close(config_fd);
    return 0;
}

int get_config(int flag, size_t *config_len) {
    char *username = getlogin();
    char *config_path = calloc(strlen(CONFIG_PATH) + strlen(username) + strlen("home") + 3, sizeof(char));
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

    free(config_path);
    return fd;
}
