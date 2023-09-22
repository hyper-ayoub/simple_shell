#include "shell.h"

/**
 * main_shell_loop - Main shell loop.
 * @info: Pointer to the parameter & return info struct.
 * @av: Argument vector from main().
 *
 * Return: 0 on success, 1 on error, or error code.
 */
int main_shell_loop(info_t *info, char **av)
{
    ssize_t r = 0;
    int builtin_ret = 0;

    while (r != -1 && builtin_ret != -2)
    {
        clear_info(info);
        if (is_interactive(info))
            _puts("$ ");
        _eputchar(BUF_FLUSH);
        r = get_input(info);
        if (r != -1)
        {
            set_info(info, av);
            builtin_ret = find_builtin_command(info);
            if (builtin_ret == -1)
                find_executable_command(info);
        }
        else if (is_interactive(info))
            _putchar('\n');
        free_info(info, 0);
    }
    write_history_to_file(info);
    free_info(info, 1);
    if (!is_interactive(info) && info->status)
        exit(info->status);
    if (builtin_ret == -2)
    {
        if (info->err_num == -1)
            exit(info->status);
        exit(info->err_num);
    }
    return (builtin_ret);
}

/**
 * find_builtin_command - Finds a builtin command.
 * @info: Pointer to the parameter & return info struct.
 *
 * Return: -1 if builtin not found,
 *         0 if builtin executed successfully,
 *         1 if builtin found but not successful,
 *         -2 if builtin signals exit()
 */
int find_builtin_command(info_t *info)
{
    int i, builtin_ret = -1;
    builtin_table builtintbl[] = {
        {"exit", my_exit},
        {"env", my_env},
        {"help", my_help},
        {"history", my_history},
        {"setenv", my_setenv},
        {"unsetenv", my_unsetenv},
        {"cd", my_cd},
        {"alias", my_alias},
        {NULL, NULL}
    };

    for (i = 0; builtintbl[i].type; i++)
    {
        if (_strcmp(info->argv[0], builtintbl[i].type) == 0)
        {
            info->line_count++;
            builtin_ret = builtintbl[i].func(info);
            break;
        }
    }
    return (builtin_ret);
}

/**
 * find_executable_command - Finds an executable command in PATH.
 * @info: Pointer to the parameter & return info struct.
 *
 * Return: void
 */
void find_executable_command(info_t *info)
{
    char *path = NULL;
    int i, k;

    info->path = info->argv[0];
    if (info->linecount_flag == 1)
    {
        info->line_count++;
        info->linecount_flag = 0;
    }
    for (i = 0, k = 0; info->arg[i]; i++)
    {
        if (!is_delimiter(info->arg[i], " \t\n"))
        {
            k++;
        }
    }
    if (!k)
    {
        return;
    }

    path = find_command_in_path(info, _getenv(info, "PATH="), info->argv[0]);
    if (path)
    {
        info->path = path;
        fork_executable_command(info);
    }
    else
    {
        if ((is_interactive(info) || _getenv(info, "PATH=") || info->argv[0][0] == '/') && is_cmd(info, info->argv[0]))
        {
            fork_executable_command(info);
        }
        else if (*(info->arg) != '\n')
        {
            info->status = 127;
            print_error(info, "not found\n");
        }
    }
}

/**
 * fork_executable_command - Forks an exec thread to run a command.
 * @info: Pointer to the parameter & return info struct.
 *
 * Return: void
 */
void fork_executable_command(info_t *info)
{
    pid_t child_pid;

    child_pid = fork();
    if (child_pid == -1)
    {
        /* TODO: PUT ERROR FUNCTION */
        perror("Error:");
        return;
    }
    if (child_pid == 0)
    {
        if (execve(info->path, info->argv, get_environment(info)) == -1)
        {
            free_info(info, 1);
            if (errno == EACCES)
                exit(126);
            exit(1);
        }
        /* TODO: PUT ERROR FUNCTION */
    }
    else
    {
        wait(&(info->status));
        if (WIFEXITED(info->status))
        {
            info->status = WEXITSTATUS(info->status);
            if (info->status == 126)
                print_error(info, "Permission denied\n");
        }
    }
}

