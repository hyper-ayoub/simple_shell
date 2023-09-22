#include "shell.h"

/**
 * obtain_history_file - gets the history file
 * @info: parameter struct
 *
 * Return: allocated string containing history file
 */
char *obtain_history_file(info_t *info)
{
    char *path, *file;
    path = _getenv(info, "HOME=");
    if (!path)
        return (NULL);
    file = malloc(sizeof(char) * (_strlen(path) + _strlen(HISTORY_FILE) + 2));
    if (!file)
        return (NULL);
    file[0] = 0;
    _strcpy(file, path);
    _strcat(file, "/");
    _strcat(file, HISTORY_FILE);
    return (file);
}

/**
 * save_history - creates a file, or appends to an existing file
 * @info: the parameter struct
 *
 * Return: 1 on success, else -1
 */
int save_history(info_t *info)
{
    ssize_t fd;
    char *filename = obtain_history_file(info);
    list_t *node = NULL;

    if (!filename)
        return (-1);

    fd = open(filename, O_CREAT | O_TRUNC | O_RDWR, 0644);
    free(filename);
    if (fd == -1)
        return (-1);

    for (node = info->history; node; node = node->next)
    {
        _putsfd(node->str, fd);
        _putfd('\n', fd);
    }

    _putfd(BUFFER_FLUSH, fd);
    close(fd);
    return (1);
}

/**
 * load_history - reads history from file
 * @info: the parameter struct
 *
 * Return: histcount on success, 0 otherwise
 */
int load_history(info_t *info)
{
    int i, last = 0, linecount = 0;
    ssize_t fd, rdlen, fsize = 0;
    struct stat st;
    char *buffer = NULL, *filename = obtain_history_file(info);

    if (!filename)
        return (0);

    fd = open(filename, O_RDONLY);
    free(filename);
    if (fd == -1)
        return (0);

    if (!fstat(fd, &st))
        fsize = st.st_size;

    if (fsize < 2)
        return (0);

    buffer = malloc(sizeof(char) * (fsize + 1));
    if (!buffer)
        return (0);

    rdlen = read(fd, buffer, fsize);
    buffer[fsize] = 0;

    if (rdlen <= 0)
        return (free(buffer), 0);

    close(fd);

    for (i = 0; i < fsize; i++)
    {
        if (buffer[i] == '\n')
        {
            buffer[i] = 0;
            build_history_list(info, buffer + last, linecount++);
            last = i + 1;
        }
    }

    if (last != i)
        build_history_list(info, buffer + last, linecount++);

    free(buffer);
    info->histcount = linecount;

    while (info->histcount-- >= HISTORY_MAX)
        delete_node_at_index(&(info->history), 0);

    renumber_history(info);
    return (info->histcount);
}

/**
 * add_to_history - adds entry to a history linked list
 * @info: Structure containing potential arguments
 * @buffer: buffer
 * @linecount: the history linecount, histcount
 *
 * Return: Always 0
 */
int add_to_history(info_t *info, char *buffer, int linecount)
{
    list_t *node = NULL;

    if (info->history)
        node = info->history;

    add_node_end(&node, buffer, linecount);

    if (!info->history)
        info->history = node;

    return (0);
}

/**
 * refresh_history - renumbers the history linked list after changes
 * @info: Structure containing potential arguments
 *
 * Return: the new histcount
 */
int refresh_history(info_t *info)
{
    list_t *node = info->history;
    int i = 0;

    while (node)
    {
        node->num = i++;
        node = node->next;
    }

    return (info->histcount = i);
}

