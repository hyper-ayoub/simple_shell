#include "shell.h"

/**
 * is_executable - Determines if a file is an executable command.
 * @path: Path to the file.
 *
 * Return: 1 if true, 0 otherwise.
 */
int is_executable(char *path)
{
    struct stat st;

    if (!path || stat(path, &st) != 0)
        return (0);

    if (st.st_mode & S_IFREG)
        return (1);

    return (0);
}

/**
 * copy_chars - Copies characters from a string based on start and stop indices.
 * @str: The source string.
 * @start: Starting index.
 * @stop: Stopping index.
 *
 * Return: Pointer to a new buffer.
 */
char *copy_chars(const char *str, int start, int stop)
{
    static char buf[1024];
    int i = 0, k = 0;

    for (k = 0, i = start; i < stop; i++)
    {
        if (str[i] != ':')
            buf[k++] = str[i];
    }

    buf[k] = '\0';
    return (buf);
}

/**
 * find_executable_in_path - Finds an executable command in the PATH environment variable.
 * @pathstr: The PATH environment variable string.
 * @cmd: The command to find.
 *
 * Return: Full path of the command if found, or NULL.
 */
char *find_executable_in_path(const char *pathstr, const char *cmd)
{
    int i = 0, curr_pos = 0;
    char *path;

    if (!pathstr)
        return (NULL);

    if (strlen(cmd) > 2 && starts_with(cmd, "./"))
    {
        if (is_executable((char *)cmd))
            return ((char *)cmd);
    }

    while (1)
    {
        if (!pathstr[i] || pathstr[i] == ':')
        {
            path = copy_chars(pathstr, curr_pos, i);

            if (!*path)
                strcat(path, cmd);
            else
            {
                strcat(path, "/");
                strcat(path, cmd);
            }

            if (is_executable(path))
                return (path);

            if (!pathstr[i])
                break;

            curr_pos = i;
        }

        i++;
    }

    return (NULL);
}

