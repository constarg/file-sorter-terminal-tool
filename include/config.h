#ifndef CONFIG_H
#define CONFIG_H

/**
 * Write the config file contents.
 * @param src The buffer that contains the changed content.
 * @return 0 on success or -1 on error.
 */
extern int write_config(const char *src);

/**
 * Reads the config file contents and
 * store them in a buffer.
 * @param dst The destination buffer.
 * @return 0 on success or -1 on error.
 */
extern int read_config(char *dst);

#endif
