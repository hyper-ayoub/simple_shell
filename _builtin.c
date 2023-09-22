#include "shell.h"

/**
 * my_exit - Exits the shell.
 * @info: Structure containing potential arguments.
 *
 * Return: Exits with a given exit status (0) if info->arguments[0] != "exit".
 */
int my_exit(info_t *info) {
    int exit_status;

    if (info->arguments[1]) {
        exit_status = str_to_int(info->arguments[1]);
        if (exit_status == -1) {
            info->status = 2;
            print_error(info, "Illegal number: ");
            e_puts(info->arguments[1]);
            e_putchar('\n');
            return 1;
        }
        info->err_num = str_to_int(info->arguments[1]);
        return -2;
    }
    info->err_num = -1;
    return -2;
}

/**
 * my_cd - Changes the current directory of the process.
 * @info: Structure containing potential arguments.
 *
 * Return: Always 0.
 */
int my_cd(info_t *info) {
    char *s, *dir, buffer[1024];
    int chdir_ret;

    s = getcwd(buffer, 1024);
    if (!s)
        e_puts("TODO: >>getcwd failure emsg here<<\n");
    if (!info->arguments[1]) {
        dir = _getenv(info, "HOME=");
        if (!dir)
            chdir_ret = chdir((dir = _getenv(info, "PWD=")) ? dir : "/");
        else
            chdir_ret = chdir(dir);
    } else if (_strcmp(info->arguments[1], "-") == 0) {
        if (!_getenv(info, "OLDPWD=")) {
            e_puts(s);
            e_putchar('\n');
            return 1;
        }
        e_puts(_getenv(info, "OLDPWD="));
        e_putchar('\n');
        chdir_ret = chdir((dir = _getenv(info, "OLDPWD=")) ? dir : "/");
    } else {
        chdir_ret = chdir(info->arguments[1]);
    }
    if (chdir_ret == -1) {
        print_error(info, "can't cd to ");
        e_puts(info->arguments[1]);
        e_putchar('\n');
    } else {
        _setenv(info, "OLDPWD", _getenv(info, "PWD="));
        _setenv(info, "PWD", getcwd(buffer, 1024));
    }
    return 0;
}

/**
 * my_help - Displays help information (not yet implemented).
 * @info: Structure containing potential arguments.
 *
 * Return: Always 0.
 */
int my_help(info_t *info) {
    char **arg_array;

    arg_array = info->arguments;
    e_puts("help call works. Function not yet implemented \n");
    if (0)
        e_puts(*arg_array); /* temp att_unused workaround */
    return 0;
}

