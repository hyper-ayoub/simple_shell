#include "shell.h"

/**
 * my_puts_err - Prints an input string to stderr.
 * @str: The string to be printed.
 *
 * Return: Nothing.
 */
void my_puts_err(char *str) {
    int i = 0;

    if (!str)
        return;
    while (str[i] != '\0') {
        my_putchar_err(str[i]);
        i++;
    }
}

/**
 * my_putchar_err - Writes the character c to stderr.
 * @c: The character to print.
 *
 * Return: On success, 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int my_putchar_err(char c) {
    static int i;
    static char buf[WRITE_BUF_SIZE];

    if (c == BUF_FLUSH || i >= WRITE_BUF_SIZE) {
        write(2, buf, i);
        i = 0;
    }
    if (c != BUF_FLUSH)
        buf[i++] = c;
    return 1;
}

/**
 * my_putchar_fd - Writes the character c to the given file descriptor.
 * @c: The character to print.
 * @fd: The file descriptor to write to.
 *
 * Return: On success, 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int my_putchar_fd(char c, int fd) {
    static int i;
    static char buf[WRITE_BUF_SIZE];

    if (c == BUF_FLUSH || i >= WRITE_BUF_SIZE) {
        write(fd, buf, i);
        i = 0;
    }
    if (c != BUF_FLUSH)
        buf[i++] = c;
    return 1;
}

/**
 * my_puts_fd - Prints an input string to the given file descriptor.
 * @str: The string to be printed.
 * @fd: The file descriptor to write to.
 *
 * Return: The number of characters printed.
 */
int my_puts_fd(char *str, int fd) {
    int i = 0;

    if (!str)
        return 0;
    while (*str) {
        i += my_putchar_fd(*str++, fd);
    }
    return i;
}

