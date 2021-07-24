#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

#include "configHandler.h"

#define CONFIG_PATH "/.local/share/file_sorter/config/config.conf"

int getConfig(int, size_t *);

int writeConfig(char* changes, size_t changesLen) {
    int configFD = getConfig(O_RDWR | O_TRUNC, NULL);

    if (configFD == -1) return configFD;
    if (write(configFD, changes, changesLen) == -1) return -1;

    close(configFD);
    return 0;
}

int readConfig(char** configContent) {
    size_t configLen;
    int configFD = getConfig(O_RDONLY, &configLen);
    char* buffer;

    if (configFD == -1) return configFD;
    if (configLen == -1) return (int) configLen;

    buffer = calloc(configLen, sizeof(char));
    if (read(configFD, buffer, configLen) == -1)
        return -1;

    *configContent = calloc(configLen + 1, sizeof(char));
    strncpy(*configContent, buffer, configLen);

    free(buffer);
    return 0;
}

int getConfig(int flag, size_t *configLen) {
    char* username = getlogin();
    char* configPath = calloc(1, sizeof(char) * (strlen(CONFIG_PATH) + strlen(username) + strlen("home") + 3));
    struct stat configStat;
    int fd;

    strcpy(configPath, "/home/");
    strcat(configPath, username);
    strcat(configPath, CONFIG_PATH);

    fd = open(configPath, flag);

    if (configLen != NULL) {
        if (lstat(configPath, &configStat) == -1) {
            *configLen = -1;
            return fd;
        }
        *configLen = configStat.st_size;
    }

    free(configPath);
    return fd;
}
