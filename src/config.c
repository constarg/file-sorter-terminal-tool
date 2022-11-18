#include <config.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>
#include <malloc.h>
#include <stdio.h>

static inline int get_conf_path(char **dst)
{
    char *usr = getlogin();
    if (usr == NULL) return -1;
    char rel_path[] = ".local/share/file_sorter"
                      "/config/config.conf";
    (*dst) = (char *) malloc(sizeof(char) * strlen(usr)
                                          + strlen(rel_path)
                                          + 7); // len of /home/ + \0
    if (*dst == NULL) return -1;
    // build the absolute path.
    strcpy(*dst, "/home/");
    strcat(*dst, usr);
    strcat(*dst, rel_path);
    return 0;
}

int write_config(const struct conf *src)
{
    char *conf_path = NULL;
    size_t size_src = strlen(src);
    FILE *conf = NULL;

    // get the absolute path.
    if (get_conf_path(&conf_path) == -1) return -1;
    conf = fopen(conf_path, "w");
    free(conf_path);

    if (conf == NULL) return -1;
    // use fwrite, as it is faster than fprintf.
    if (fwrite(src, size_src, 1, conf)
        != size_src) {
        fclose(conf);
        return -1;
    }
    fclose(conf);
    return 0;
}

int read_config(struct conf *dst)
{
    char *conf_path = NULL;
    struct stat stat_buff;
    FILE *conf = NULL;

    // get the absolute path.
    if (get_conf_path(&conf_path) == -1) return -1;
    conf = fopen(conf_path, "r");

    // get stats of the conf file.
    if (stat(conf_path, &stat_buff) == -1) {
        free(conf_path);
        return -1;
    }
    free(conf_path);

    // allocate space for the dst.
    (*dst) = (char *) malloc(sizeof(char) *
                             stat_buff.st_size + 1);
    if (*dst == NULL) return -1;

    // read the content of config file.
    if (fread(*dst, stat_buff.st_size,
              1, conf) != stat_buff.st_size) {
        fclose(conf);
        return -1;
    }    
    fclose(conf);
    return 0;
}
