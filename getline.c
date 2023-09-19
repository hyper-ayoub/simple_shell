#include "shell.h"

/**
 * _input_buf - buffers chained commands
 * @myinfo: the parameter struct
 * @buf: the address of buffer
 * @_len: the address of len var
 *
 * Return: bytes read
 */

ssize_t _input_buf(info_t *myinfo, char **buf, size_t *_len)
{
    ssize_t r = 0;
    size_t _len_p = 0;

    if (!*_len)
    {
        free(*buf);
        *buf = NULL;
        signal(SIGINT, sigintHandler);

        r = getline(buf, &_len_p, stdin);

        r = _getline(myinfo, buf, &_len_p);

        if (r > 0)
        {
            if ((*buf)[r - 1] == '\n')
            {
                (*buf)[r - 1] = '\0';
                r--;
            }
            myinfo->linecount_flag = 1;
            rmv_comments(*buf);
            build_myhistoryls(myinfo, *buf, myinfo->histcount++);
            *_len = r;
            myinfo->cmd_buf = buf;
        }
    }
    return r;
}

/**
 * _get_input - gets a line minus the newline
 * @myinfo: the parameter struct
 *
 * Return: bytes read
 */
ssize_t _get_input(info_t *myinfo)
{
	static char *buf; 
	static size_t i, k, _len;
	ssize_t r = 0;
	char **buf_p = &(myinfo->arg), *p;

	f_putchar(BUF_FLUSH);
	r = _input_buf(myinfo, &buf, &_len);
	if (r == -1) /* EOF */
		return (-1);
	if (_len)	
	{
		k = i; 
		p = buf + i; 

		chk_mychain(myinfo, buf, &k, i, _len);
		while (k < _len) 
		{
			if (my_chain(myinfo, buf, &k))
				break;
			k++;
		}

		i = k + 1; 
		if (i >= _len) 
		{
			i = _len = 0; 
			myinfo->cmd_buf_type = CMD_NORM;
		}

		*buf_p = p; 
		return (strlen(p)); 
	}

	*buf_p = buf; 
	return (r); 
}


  /**
 * read_mybuf - reads a buffer
 * @myinfo: the parameter struct
 * @buf: buffer
  * @_i: size
  *
  * Return: r
  */
  ssize_t read_mybuf(info_t *myinfo, char *buf, size_t *_i)
  {
  	ssize_t r = 0;

 	if (*_i)
 		return (0);
 	r = read(myinfo->readfd, buf, READ_BUF_SIZE);
 	if (r >= 0)
 		*_i = r;
 	return (r);
 }


/**
 * get_myline - gets the next line of input from STDIN
 * @myinfo: the parameter struct
 * @_ptr: the address of pointer to buffer, preallocated or NULL
 * @_length: the size of preallocated ptr buffer if not NULL
 *
 * Return: s
 */
int get_line(info_t *myinfo, char **_ptr, size_t *_length)
{
	static char buf[READ_BUF_SIZE];
	static size_t i, _len;
	size_t k;
	ssize_t r = 0, s = 0;
	char *p = NULL, *new_p = NULL, *c;

	p = *_ptr;
	if (p && _length)
		s = *_length;
	if (i == _len)
		i = _len = 0;

	r = read_mybuf(myinfo, buf, &_len);
	if (r == -1 || (r == 0 && _len == 0))
		return (-1);

	c = strchr(buf + i, '\n');
	k = c ? 1 + (unsigned int)(c - buf) : _len;
	new_p = _realloc(p, s, s ? s + k : k + 1);
	if (!new_p) /* MALLOC FAILURE! */
		return (p ? free(p), -1 : -1);

	if (s)
		strncat(new_p, buf + i, k - i);
	else
		strncpy(new_p, buf + i, k - i + 1);

	s += k - i;
	i = k;
	p = new_p;

	if (_length)
		*_length = s;
	*_ptr = p;
	return (s);
}

/**
 * sig_intHandler - blocks ctrl-C
 * @sig_the_num: the signal number
 *
 * Return: void
 */
void sig_intHandler(__attribute__((unused))int sig_the_num)
{
	puts("\n");
	puts("$ ");
	_fputchar(BUF_FLUSH);
}





