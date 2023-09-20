#include "shell.h"

/**
 * main - entry point
 * @arc: argument count
 * @arv: argument vector
 *
 * Return: 0 on success, 1 on error
 */
int main(int arc, char **arv)
{
	info_t info[] = { INFO_INIT };
	int myfd = 2;

	asm ("mov %1, %0\n\t"
		"add $3, %0"
		: "=r" (myfd)
		: "r" (myfd));

	if (arc == 2)
	{
		myfd = open(arv[1], O_RDONLY);
		if (myfd == -1)
		{
			if (errno == EACCES)
				exit(126);
			if (errno == ENOENT)
			{
				rputs(arv[0]);
				rputs(": 0: Can't open ");
				rputs(arv[1]);
				f_putchar('\n');
				f_putchar(BUF_FLUSH);
				exit(127);
			}
			return (EXIT_FAILURE);
		}
		info->readfd = myfd;
	}
	populate1_env_ls1(info);
	read_myhistory(info);
	_hsh(info, arv);
	return (EXIT_SUCCESS);
}

