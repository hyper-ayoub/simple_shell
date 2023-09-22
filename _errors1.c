#include "shell.h"

/**
 * error_atoi - Converts a string to an integer with error handling.
 * @s: The string to be converted.
 * 
 * Return: 0 if no numbers in string, converted number otherwise, -1 on error.
 */
int error_atoi(char *s) {
    int i = 0;
    unsigned long int result = 0;

    if (*s == '+')
        s++;
    for (i = 0; s[i] != '\0'; i++) {
        if (s[i] >= '0' && s[i] <= '9') {
            result *= 10;
            result += (s[i] - '0');
            if (result > INT_MAX)
                return -1;
        } else {
            return -1;
        }
    }
    return result;
}

/**
 * print_shell_error - Prints a shell error message.
 * @info: The parameter and return info struct.
 * @error_str: String containing the specified error type.
 */
void print_shell_error(info_t *info, char *error_str) {
    my_puts_err(info->fname);
    my_puts_err(": ");
    print_decimal(info->line_count, STDERR_FILENO);
    my_puts_err(": ");
    my_puts_err(info->argv[0]);
    my_puts_err(": ");
    my_puts_err(error_str);
}

/**
 * print_decimal - Prints a decimal (integer) number (base 10).
 * @input: The input number.
 * @fd: The file descriptor to write to.
 * 
 * Return: Number of characters printed.
 */
int print_decimal(int input, int fd) {
    int (*__putchar)(char) = my_putchar_err;
    int i, count = 0;
    unsigned int abs_val, current;

    if (fd == STDERR_FILENO)
        __putchar = my_putchar_err;
    if (input < 0) {
        abs_val = -input;
        __putchar('-');
        count++;
    } else {
        abs_val = input;
    }
    current = abs_val;
    for (i = 1000000000; i > 1; i /= 10) {
        if (abs_val / i) {
            __putchar('0' + current / i);
            count++;
        }
        current %= i;
    }
    __putchar('0' + current);
    count++;

    return count;
}

/**
 * convert_to_string - Converts a number to a string representation.
 * @num: The number to convert.
 * @base: The base for conversion.
 * @flags: Argument flags.
 * 
 * Return: The resulting string.
 */
char *convert_to_string(long int num, int base, int flags) {
    static char *array;
    static char buffer[50];
    char sign = 0;
    char *ptr;
    unsigned long n = num;

    if (!(flags & CONVERT_UNSIGNED) && num < 0) {
        n = -num;
        sign = '-';
    }
    array = flags & CONVERT_LOWERCASE ? "0123456789abcdef" : "0123456789ABCDEF";
    ptr = &buffer[49];
    *ptr = '\0';

    do {
        *--ptr = array[n % base];
        n /= base;
    } while (n != 0);

    if (sign)
        *--ptr = sign;
    return ptr;
}

/**
 * remove_shell_comments - Replaces the first instance of '#' with '\0'.
 * @buf: Address of the string to modify.
 */
void remove_shell_comments(char *buf) {
    int i;

    for (i = 0; buf[i] != '\0'; i++) {
        if (buf[i] == '#' && (!i || buf[i - 1] == ' ')) {
            buf[i] = '\0';
            break;
        }
    }
}

