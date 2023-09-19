#include "shell.h"

/**
 * my_chain - test if the current char in buffer is a chain delimeter
 * @myinfo: the parameter struct
 * @buf: the char buffer
 * @po: the address of current position in buf
 *
 * Return: 1 if chain delimeter, 0 otherwise
 */
int my_chain(info_t *myinfo, char *buf, size_t *po)
{
	size_t k = *po;

	if (buf[k] == '|' && buf[k + 1] == '|')
	{
		buf[k] = 0;
		k++;
		myinfo->cmd_buf_type = CMD_OR;
	}
	else if (buf[k] == '&' && buf[k + 1] == '&')
	{
		buf[k] = 0;
		k++;
		myinfo->cmd_buf_type = CMD_AND;
	}
	else if (buf[k] == ';')
	{
		buf[k] = 0; 
		myinfo->cmd_buf_type = CMD_CHAIN;
	}
	else
		return (0);
	*po = k;
	return (1);
}

/**
 * chk_mychain - checks we should continue chaining based on the last status
 * @myinfo: the parameter struct
 * @buf: the char buffer
 * @po: the address of current position in buf
 * @_i: starting position in the buf
 * @_len: length of the buf
 *
 * Return: Void
 */
void chk_chain(info_t *myinfo, char *buf, size_t *po, size_t _i, size_t _len)
{
	size_t k = *po;

	if (myinfo->cmd_buf_type == CMD_AND)
	{
		if (myinfo->status)
		{
			buf[_i] = 0;
			k = _len;
		}
	}
	if (myinfo->cmd_buf_type == CMD_OR)
	{
		if (!myinfo->status)
		{
			buf[_i] = 0;
			k =_len;
		}
	}

	*po = k;
}

/**
 * replace_myalias - replaces an aliases in the tokenized string
 * @myinfo: the parameter struct
 *
 * Return: 1 if replaced, 0 otherwise
 */
int repalce_myalias(info_t *myinfo)
{
	int i;
	list_t *node1;
	char *po;

	for (i = 0; i < 10; i++)
	{
		node1 = node1_starts_with(myinfo->alias, myinfo->argv[0], '=');
		if (!node1)
			return (0);
		free(myinfo->argv[0]);
		po = strchr(node1->str, '=');
		if (!po)
			return (0);
		po = strdup(po + 1);
		if (!po)
			return (0);
		myinfo->argv[0] = po;
	}
	return (1);
}

/**
 * replace_str - replaces string
 * @_old: the address of old string
 * @_new: new string
 *
 * Return: 1 if replaced, 0 otherwise
 */
int replace_str(char **_old, char *_new)
{
	free(*_old);
	*_old = _new;
	return (1);
}


/**
 * replace_myvars - replaces vars in  tokenized string
 * @myinfo: the parameter struct
 *
 * Return: 1 if replaced, 0 otherwise
 */
int replace_myvars(info_t *myinfo)
{
	int i = 0;
	list_t *node1;

	for (i = 0; myinfo->argv[i]; i++)
	{
		if (myinfo->argv[i][0] != '$' || !myinfo->argv[i][1])
			continue;

		if (!strcmp(myinfo->argv[i], "$?"))
		{
			replace_str(&(myinfo->argv[i]),
				strdup(cnv_number(myinfo->status, 10, 0)));
			continue;
		}
		if (!strcmp(myinfo->argv[i], "$$"))
		{
			replace_str(&(myinfo->argv[i]),
				strdup(cnv_number(getpid(), 10, 0)));
			continue;
		}
		node1 = node1_starts(myinfo->env, &myinfo->argv[i][1], '=');
		if (node1)
		{
			replace_str(&(myinfo->argv[i]),
				strdup(strchr(node1->str, '=') + 1));
			continue;
		}
		replace_str(&myinfo->argv[i], strdup(""));

	}
	return (0);
}


