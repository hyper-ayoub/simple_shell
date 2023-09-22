#include "shell.h"

/**
 * history_display - Display the command history.
 * @info: Structure containing potential arguments.
 *
 * Return: Always 0.
 */
int history_display(info_t *info)
{
    print_list(info->history);
    return (0);
}

/**
 * unset_shell_alias - Unset a shell alias.
 * @info: Parameter struct.
 * @str: The string alias to unset.
 *
 * Return: Always 0 on success, 1 on error.
 */
int unset_shell_alias(info_t *info, char *str)
{
    char *position, character;
    int result;

    position = _strchr(str, '=');
    if (!position)
        return (1);
    character = *position;
    *position = 0;
    result = delete_node_at_index(&(info->alias),
            get_node_index(info->alias, node_starts_with(info->alias, str, -1)));
    *position = character;
    return (result);
}

/**
 * set_shell_alias - Set a shell alias.
 * @info: Parameter struct.
 * @str: The string alias to set.
 *
 * Return: Always 0 on success, 1 on error.
 */
int set_shell_alias(info_t *info, char *str)
{
    char *position;

    position = _strchr(str, '=');
    if (!position)
        return (1);
    if (!*++position)
        return (unset_shell_alias(info, str));

    unset_shell_alias(info, str);
    return (add_node_end(&(info->alias), str, 0) == NULL);
}

/**
 * print_shell_alias - Print a shell alias.
 * @node: The alias node to print.
 *
 * Return: Always 0 on success, 1 on error.
 */
int print_shell_alias(list_t *node)
{
    char *position = NULL, *alias = NULL;

    if (node)
    {
        position = _strchr(node->str, '=');
        for (alias = node->str; alias <= position; alias++)
            _putchar(*alias);
        _putchar('\'');
        _puts(position + 1);
        _puts("'\n");
        return (0);
    }
    return (1);
}

/**
 * shell_alias - Handle shell aliases.
 * @info: Structure containing potential arguments.
 *
 * Return: Always 0.
 */
int shell_alias(info_t *info)
{
    int i = 0;
    char *position = NULL;
    list_t *node = NULL;

    if (info->argc == 1)
    {
        node = info->alias;
        while (node)
        {
            print_shell_alias(node);
            node = node->next;
        }
        return (0);
    }
    for (i = 1; info->argv[i]; i++)
    {
        position = _strchr(info->argv[i], '=');
        if (position)
            set_shell_alias(info, info->argv[i]);
        else
            print_shell_alias(node_starts_with(info->alias, info->argv[i], '='));
    }

    return (0);
}

