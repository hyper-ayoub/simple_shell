#include "shell.h"

/**
 * main - Entry point of the shell.
 * @argc: Argument count.
 * @argv: Argument vector.
 *
 * Return: 0 on success, 1 on error.
 */
int main(int argc, char **argv)
{
    info_t shell_info[] = { INFO_INIT }; // Initialize the shell info struct
    int file_descriptor = 2; // Initialize a file descriptor for error output

    // Inline assembly to manipulate the file descriptor
    asm ("mov %1, %0\n\t"
        "add $3, %0"
        : "=r" (file_descriptor)
        : "r" (file_descriptor));

    if (argc == 2)
    {
        file_descriptor = open(argv[1], O_RDONLY); // Attempt to open a file
        if (file_descriptor == -1)
        {
            if (errno == EACCES)
                exit(126); // Exit with status 126 on permission denied
            if (errno == ENOENT)
            {
                _eputs(argv[0]);
                _eputs(": 0: Can't open ");
                _eputs(argv[1]);
                _eputchar('\n');
                _eputchar(BUF_FLUSH);
                exit(127); // Exit with status 127 on file not found
            }
            return (EXIT_FAILURE);
        }
        shell_info->readfd = file_descriptor; // Update read file descriptor
    }
    populate_env_list(shell_info); // Populate the environment list
    read_history(shell_info); // Read command history
    hsh(shell_info, argv); // Start the shell execution
    return (EXIT_SUCCESS); // Return success status
}

