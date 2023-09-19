#ifndef _SHELL_H_
#define _SHELL_H_
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <limits.h>
#include <fcntl.h>
#include <errno.h>
#include "shell.h"



#define CMD_NORM	0
#define CMD_OR		1
#define CMD_AND		2
#define CMD_CHAIN	3


#define READ_BUF_SIZE 1024
#define WRITE_BUF_SIZE 1024
#define BUF_FLUSH -1


#define USE_GETLINE 0
#define USE_STRTOK 0


#define CONVERT_LOWERCASE	1
#define CONVERT_UNSIGNED	2

#define HIST_FILE	".simple_shell_history"
#define HIST_MAX	4096

extern char **environ;
/**
 * struct liststr - singly linked list
 * @num: the number field
 * @str: a string
 * @next: points to the next node
 */
typedef struct liststr
{
	int num;
	char *str;
	struct liststr *next;
} list_t;

/**
 * struct passinfo - Structure for passing arguments to a function pointer
 *
 * This structure is designed to provide a consistent prototype for a function
 * pointer by encapsulating various arguments that may be needed.
 *
 * @arg:          A string generated from getline containing arguments.
 * @arv:          An array of strings generated from arg.
 * @path:         A string representing the path for the current command.
 * @arc:          The argument count.
 * @line_count:   The error count.
 * @err_num:      The error code for exit() calls.
 * @linecount_flag:  A flag indicating whether to count this line of input.
 * @fname:        The program filename.
 * @env:          Linked list local copy of environ.
 * @environ:      Custom modified copy of environ from the linked list env.
 * @history:      The history node.
 * @alias:        The alias node.
 * @env_changed:  Flag indicating if environ was changed.
 * @status:       The return status of the last executed command.
 * @cmd_buf:      Address of pointer to cmd_buf, used for chaining.
 * @cmd_buf_type: Command type (CMD_type) such as ||, &&, or ;.
 * @readfd:       The file descriptor from which to read line input.
 * @histcount:    The history line number count.
 */

typedef struct passinfo
{
	char *arg;
	char **argv;
	char *path;
	int argc;
	unsigned int line_count;
	int err_num;
	int linecount_flag;
	char *fname;
	list_t *env;
	list_t *history;
	list_t *alias;
	char **environ;
	int env_changed;
	int status;

	char **cmd_buf; 
	int cmd_buf_type; 
	int readfd;
	int histcount;
} info_t;

#define INFO_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
	0, 0, 0}

/**
 *struct builtin - contains a builtin string and related function
 *@type: the builtin command flag
 *@func: the function
 */
typedef struct builtin
{
	char *type;
	int (*func)(info_t *);
} builtin_table;



int my_strlen(char *);
int my_strcmp(char *, char *);
char *mystrats_with(const char *, const char *);
char *my_strcat(char *, char *);


char *my_strcpy(char *, char *);
char *my_strdup(const char *);
void my_puts(char *);
int my_putchar(char);


char *my_strncpy(char *, char *, int);
char *my_strncat(char *, char *, int);
char *my_strchr(char *, char);


char **firststrtow(char *, char *);
char **secondstrtow(char *, char);


char *my_memset(char *, char, unsigned int);
void myfree(char **);
void *my_realloc(void *, unsigned int, unsigned int);


int afree(void **);


int interactivemode (info_t *);
int my_delim(char, char *);
int my_alpha(int);
int my_atoi(char *);


int my_erratoi1(char *);
void prt_error1(info_t *,char *);
int prt_d1(int, int);
char *cnv_number(long int, int, int);
void rmv_comments(char *);


list_t *myadd_node1(list_t **, const char *, int);
list_t *myadd_node1_end(list_t **, const char *, int);
size_t print_ls_str(const list_t *);
int dlt_node1_in_index(list_t **, unsigned int);
void free_list1(list_t **);


size_t list1len(const list_t *);
char **list1_str(list_t *);
size_t print_ls1(const list_t *);
list_t *node1_starts(list_t *, char *, char);
ssize_t get_node1(list_t *, list_t *);

void rputs(char *);
int f_putchar(char);
int put_fd(char d, int myfd);
int puts_fd(char *str, int myfd);


void clear1_myinfo1(info_t *);
void set1_myinfo1(info_t *, char **);
void free1_myinfo1(info_t *, int);


char *get_env(info_t *, const char *);
int env(info_t *);
int set_env(info_t *);
int remove_setenv(info_t *);
int populate1_env_ls1(info_t *);


char **_getmyenv(info_t *);
int dlt_setenv(info_t *, char *);
int set_myenv(info_t *, char *, char *);

char *get_myhistoryfile(info_t *myinfo);
int write_myhistory(info_t *myinfo);
int read_myhistory(info_t *myinfo);
int build_myhistoryls(info_t *myinfo, char *buf, int mylinecount);
int refresh_sequence_numbers(info_t *myinfo);


int my_exit1(info_t *);
int my_cd1(info_t *);
int my_help1(info_t *);


int my_history1(info_t *);
int my_alias(info_t *); 
int get_node1_index(list_t *list, int index);
int unset_alias(info_t *myinfo, char *str);


int my_cmd(info_t *, char *);
char *dupli_mychars(char *, int, int);
char *find_mypath(info_t *, char *, char *);

int my_chain(info_t *, char *, size_t *);
void checkk_mychain(info_t *, char *, size_t *, size_t, size_t);
int replace_myalias(info_t *);
int replace_str(char **, char *);
int rplc_myvars(info_t *);


ssize_t _get_input(info_t *);
int get_myline(info_t *, char **, size_t *);
void sigintHandler(int);

int _hsh(info_t *, char **);
int find_the_builtin(info_t *);
void find_the_cmd(info_t *);
void fork_the_cmd(info_t *);

#endif
