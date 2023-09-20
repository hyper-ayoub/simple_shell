#include "shell.h"

/**
 * get_myhistoryfile - gets the history file
 * @myinfo: parameter struct
 *
 * Return: allocated string containg history file
 */

char *get_myhistoryfile(info_t *myinfo)
{
	char *buf, *dir;

	dir = _getenv(myinfo, "HOME=");
	if (!dir)
		return (NULL);
	buf = malloc(sizeof(char) * (strlen(dir) + strlen(HIST_FILE) + 2));
	if (!buf)
		return (NULL);
	buf[0] = 0;
	strcpy(buf, dir);
	strcat(buf, "/");
	strcat(buf, HIST_FILE);
	return (buf);
}

/**
 * write_myhistory - creates a file, or appends to an existing file
 * @myinfo: parameter struct
 *
 * Return: 1 on success, else -1
 */
int write_myhistory(info_t *myinfo)
{
	ssize_t fd;
	char *prjname = get_myhistoryfile(myinfo);
	list_t *node1 = NULL;

	if (!prjname)
		return (-1);

	fd = open(prjname, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(prjname);
	if (fd == -1)
		return (-1);
	for (node1 = myinfo->history; node1; node1 = node1->next)
	{
		puts_fd(node1->str, fd);
		put_fd('\n', fd);
	}
	put_fd(BUF_FLUSH, fd);
	close(fd);
	return (1);
}

/**
 * read_myhistory - reads history from file
 * @myinfo: parameter struct
 *
 * Return: histcount on success, 0 otherwise
 */
int read_myhistory(info_t *myinfo)
{
	int i, last = 0, linecount = 0;
	ssize_t fd, rdlen, fsize = 0;
	struct stat st;
	char *buf = NULL, *prjname = get_myhistoryfile(myinfo);

	if (!prjname)
		return (0);

	fd = open(prjname, O_RDONLY);
	free(prjname);
	if (fd == -1)
		return (0);
	if (!fstat(fd, &st))
		fsize = st.st_size;
	if (fsize < 2)
		return (0);
	buf = malloc(sizeof(char) * (fsize + 1));
	if (!buf)
		return (0);
	rdlen = read(fd, buf, fsize);
	buf[fsize] = 0;
	if (rdlen <= 0)
		return (free(buf), 0);
	close(fd);
	for (i = 0; i < fsize; i++)
		if (buf[i] == '\n')
		{
			buf[i] = 0;
			build_myhistoryls(myinfo, buf + last, linecount++);
			last = i + 1;
		}
	if (last != i)
		build_myhistoryls(myinfo, buf + last, linecount++);
	free(buf);
	myinfo->histcount = linecount;
	while (myinfo->histcount-- >= HIST_MAX)
		dlt_node1_in_index(&(myinfo->history), 0);
	renumber_myhistory(myinfo);
	return (myinfo->histcount);
}

/**
 * build_myhistoryls - adds entry to a history linked list
 * @myinfo: the Structure containing potential arguments. Used to maintain
 * @buf: buffer
 * @mylinecount: the history linecount, histcount
 *
 * Return: Always 0
 */
int build_myhistoryls(info_t *myinfo, char *buf, int mylinecount)
{
	list_t *node1 = NULL;

	if (myinfo->history)
		node1 = myinfo->history;
	myadd_node1_end(&node1, buf, mylinecount);

	if (!myinfo->history)
		myinfo->history = node1;
	return (0);
}

/**
 * refresh_sequence_numbers - renumbers the history linked list after changes
 * @info: the Structure containing potential arguments. Used to maintain
 *
 * Return: the new histcount
 */
int refresh_sequence_numbers(info_t *myinfo)
{
	list_t *node1 = myinfo->history;
	int i = 0;

	while (node1)
	{
		node1->num = i++;
		node1 = node1->next;
	}
	return (myinfo->histcount = i);
}
