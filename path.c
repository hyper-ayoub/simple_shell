
#include "shell.h"

/**
 * my_cmd - determines if a file is an executable command
 * @myinfo: the info struct
 * @mypath: path to the file
 *
 * Return: 1 if true, 0 otherwise
 */
int my_cmd(info_t *myinfo, char *mypath)
{
	struct stat st;

	(void)myinfo;
	if (!mypath || lstat(mypath, &st))
		return (0);

	if (st.st_mode & S_IFREG)
	{
		return (1);
	}
	return (0);
}

/**
 * dupli_mychars - duplicates characters
 * @mypathstr: the PATH string
 * @_start: starting index
 * @_stop: stopping index
 *
 * Return: pointer to a new buffer
 */
char *dupli_mychars(char *mypathstr, int _start, int _stop)
{
	static char buf[1024];
	int i = 0, j = 0;

	for (j = 0, i = _start; i < _stop; i++)
		if (mypathstr[i] != ':')
			buf[j++] = mypathstr[i];
	buf[j] = 0;
	return (buf);
}

/**
 * find_mypath - finds this cmd in the PATH string
 * @myinfo: the info struct
 * @mypathstr: the PATH string
 * @cmd: the cmd to find
 *
 * Return: the full path of cmd if found or NULL
 */
char *find_mypath(info_t *myinfo, char *mypathstr, char *cmd)
{
	int i = 0, curr_pos = 0;
	char *mypath;

	if (!mypathstr)
		return (NULL);
	if ((strlen(cmd) > 2) && mystrats_with(cmd, "./"))
	{
		if (my_cmd(myinfo, cmd))
			return (cmd);
	}
	while (1)
	{
		if (!mypathstr[i] || mypathstr[i] == ':')
		{
			mypath = dupli_mychars(mypathstr, curr_pos, i);
			if (!*mypath)
				strcat(mypath, cmd);
			else
			{
				strcat(mypath, "/");
				strcat(mypath, cmd);
			}
			if (my_cmd(myinfo, mypath))
				return (mypath);
			if (!mypathstr[i])
				break;
			curr_pos = i;
		}
		i++;
	}
	return (NULL);
}
