#include "shell.h"

/**
 * clear1_myinfo1 - initializes info_t struct
 * @myinfo: the struct address
 */
void clear1_myinfo1(info_t *myinfo)
{
	myinfo->arg = NULL;
	myinfo->argv = NULL;
	myinfo->path = NULL;
	myinfo->argc = 0;
}

/**
 * set1_myinfo1 - initializes info_t struct
 * @myinfo: the struct address
 * @myav: argument vector
 */
void set1_myinfo1(info_t *myinfo, char **myav)
{
	int i = 0;

	myinfo->fname = myav[0];
	if (myinfo->arg)
	{
		myinfo->argv = _strtow(myinfo->arg, " \t");
		if (!myinfo->argv)
		{

			myinfo->argv = malloc(sizeof(char *) * 2);
			if (myinfo->argv)
			{
				myinfo->argv[0] = _strdup(myinfo->arg);
				myinfo->argv[1] = NULL;
			}
		}
		for (i = 0; myinfo->argv && myinfo->argv[i]; i++)
			;
		myinfo->argc = i;

		replace_alias(myinfo);
		replace_vars(myinfo);
	}
}


/**
 * free1_myinfo1 - frees info_t struct fields
 * @myinfo: the struct address
 * @myall: true if freeing all fields
 */
void free1_myinfo1(info_t *myinfo, int myall)
{
	afree(myinfo->argv);
	myinfo->argv = NULL;
	myinfo->path = NULL;
	if (myall)
	{
		if (!myinfo->cmd_buf)
			free(myinfo->arg);
		if (myinfo->env)
			free_list1(&(myinfo->env));
		if (myinfo->history)
			free_list1(&(myinfo->history));
		if (myinfo->alias)
			free_list1(&(myinfo->alias));
		afree(myinfo->environ);
			myinfo->environ = NULL;
		afree((void **)myinfo->cmd_buf);
		if (myinfo->readfd > 2)
			close(myinfo->readfd);
		f_putchar(BUF_FLUSH);
	}
}

#include "shell.h"

/**
 * clear_myinfo - initializes info_t struct
 * @myinfo: struct address
 */
void clear_myinfo(info_t *myinfo)
{
    memset(myinfo, 0, sizeof(info_t));
}

/**
 * set_myinfo - initializes info_t struct
 * @myinfo: the struct address
 * @myav: argument vector
 */
void set_myinfo(info_t *myinfo, char **myav)
{
    myinfo->fname = myav[0];
    if (myinfo->arg)
    {
        myinfo->argv = _strtow(myinfo->arg, " \t");
        if (!myinfo->argv)
        {
            myinfo->argv = (char **)malloc(sizeof(char *) * 2);
            if (myinfo->argv)
            {
                myinfo->argv[0] = _strdup(myinfo->arg);
                myinfo->argv[1] = NULL;
            }
        }
        myinfo->argc = myinfo->argv ? count_elements(myinfo->argv) : 0;

        replace_alias(myinfo);
        replace_vars(myinfo);
    }
}

/**
 * free_myinfo - frees info_t struct fields
 * @myinfo: the struct address
 * @myall: true if freeing all fields
 */
void free_myinfo(info_t *myinfo, int myall)
{
    if (myinfo->argv)
        afree(myinfo->argv);
    myinfo->argv = NULL;
    myinfo->path = NULL;
    if (myall)
    {
        if (!myinfo->cmd_buf)
            free(myinfo->arg);
        free_list1(&(myinfo->env));
        free_list1(&(myinfo->history));
        free_list1(&(myinfo->alias));
        afree((void **)myinfo->environ);
        myinfo->environ = NULL;
        afree((void **)myinfo->cmd_buf);
        if (myinfo->readfd > 2)
            close(myinfo->readfd);
        f_putchar(BUF_FLUSH);
    }
}










