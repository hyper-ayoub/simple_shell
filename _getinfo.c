#include "shell.h"

/**
 * initialize_info - Clears and initializes the info_t struct.
 * @info: Pointer to the info_t struct.
 */
void initialize_info(info_t *info)
{
    info->argument = NULL;
    info->arguments = NULL;
    info->path_name = NULL;
    info->argument_count = 0;
}

/**
 * set_info_values - Sets values in the info_t struct.
 * @info: Pointer to the info_t struct.
 * @av: Argument vector.
 */
void set_info_values(info_t *info, char **av)
{
    int i = 0;

    info->file_name = av[0];
    if (info->argument)
    {
        info->arguments = strtow(info->argument, " \t");
        if (!info->arguments)
        {
            info->arguments = malloc(sizeof(char *) * 2);
            if (info->arguments)
            {
                info->arguments[0] = _strdup(info->argument);
                info->arguments[1] = NULL;
            }
        }
        for (i = 0; info->arguments && info->arguments[i]; i++)
            ;
        info->argument_count = i;

        replace_aliases(info);
        replace_variables(info);
    }
}

/**
 * free_info_values - Frees specific fields in the info_t struct.
 * @info: Pointer to the info_t struct.
 * @free_all: True if freeing all fields.
 */
void free_info_values(info_t *info, int free_all)
{
    ffree(info->arguments);
    info->arguments = NULL;
    info->path_name = NULL;
    if (free_all)
    {
        if (!info->command_buffer)
            free(info->argument);
        if (info->environment)
            free_list(&(info->environment));
        if (info->history)
            free_list(&(info->history));
        if (info->alias_list)
            free_list(&(info->alias_list));
        ffree(info->environment_variables);
        info->environment_variables = NULL;
        bfree((void **)info->command_buffer);
        if (info->read_file_descriptor > 2)
            close(info->read_file_descriptor);
        _putchar(BUF_FLUSH);
    }
}

