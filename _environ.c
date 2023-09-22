#include "shell.h"

/**
 * my_env - Prints the current environment.
 * @info: Structure containing potential arguments.
 * Return: Always 0.
 */
int my_env(info_t *info) {
    print_list_str(info->environment);
    return 0;
}

/**
 * get_environment - Gets the value of an environment variable.
 * @info: Structure containing potential arguments.
 * @name: Environment variable name.
 * Return: The value of the variable.
 */
char *get_environment(info_t *info, const char *name) {
    list_t *node = info->environment;
    char *p;

    while (node) {
        p = starts_with(node->str, name);
        if (p && *p)
            return p;
        node = node->next;
    }
    return NULL;
}

/**
 * my_setenv - Initializes a new environment variable or modifies an existing one.
 * @info: Structure containing potential arguments.
 * Return: Always 0.
 */
int my_setenv(info_t *info) {
    if (info->argc != 3) {
        e_puts("Incorrect number of arguments\n");
        return 1;
    }
    if (set_environment(info, info->arguments[1], info->arguments[2]))
        return 0;
    return 1;
}

/**
 * my_unsetenv - Removes an environment variable.
 * @info: Structure containing potential arguments.
 * Return: Always 0.
 */
int my_unsetenv(info_t *info) {
    int i;

    if (info->argc == 1) {
        e_puts("Too few arguments.\n");
        return 1;
    }
    for (i = 1; i <= info->argc; i++)
        unset_environment(info, info->arguments[i]);

    return 0;
}

/**
 * populate_environment_list - Populates the environment linked list.
 * @info: Structure containing potential arguments.
 * Return: Always 0.
 */
int populate_environment_list(info_t *info) {
    list_t *node = NULL;
    size_t i;

    for (i = 0; environ[i]; i++)
        add_node_end(&node, environ[i], 0);
    info->environment = node;
    return 0;
}

