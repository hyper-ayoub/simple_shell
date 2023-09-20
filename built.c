#include "shell.h"

/**
 * my_exit1 - exits the shell
 * @myinfo: the Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 *  Return: exits with a given exit status
 *         (0) if info.argv[0] != "exit"
 */
int my_exit1(info_t *myinfo)
{
	int exit_check;

	if (myinfo->argv[1])  
	{
		exit_check = my_erratoi1(myinfo->argv[1]);
		if (exit_check == -1)
		{
			myinfo->status = 2;
			prt_error1(myinfo, "Illegal number: ");
			rputs(myinfo->argv[1]);
			f_putchar('\n');
			return (1);
		}
		myinfo->err_num = my_erratoi1(myinfo->argv[1]);
		return (-2);
	}
	myinfo->err_num = -1;
	return (-2);
}
/**
 * my_cd1 - changes the current directory of the process
 * @myinfo: the Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 *  Return: Always 0
 */

int my_cd1(info_t *myinfo) {
    char buffer[1024];
    char *dir = NULL;
    int chdir_ret;


    char *s = getcwd(buffer, sizeof(buffer));
    if (!s) {
        perror("getcwd");
        return 1;
    }

    if (!myinfo->argv[1]) {
        dir = getenv("HOME");
        if (!dir)
            dir = getenv("PWD");
    } else if (strcmp(myinfo->argv[1], "-") == 0) {
        dir = getenv("OLDPWD");
        if (!dir) {
            puts(s);
            putchar('\n');
            return 1;
        }
        puts(dir);
        putchar('\n');
    } else {
        dir = myinfo->argv[1];
    }


    chdir_ret = chdir(dir);
    if (chdir_ret == -1) {
        perror("chdir");
        return 1;
    }


    setenv("OLDPWD", s, 1); 
    setenv("PWD", getcwd(buffer, sizeof(buffer)), 1); 

    return 0;
}
/**
 * my_help1 - changes the current directory of the process
 * @myinfo: the Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 *  Return: Always 0
 */
int my_help(info_t *myinfo)
{
	char **arg1_myarray;

	arg1_myarray = myinfo->argv;
	puts("help call works. Function not yet implemented \n");
	if (0)
		puts(*arg1_myarray); 
	return (0);
}
