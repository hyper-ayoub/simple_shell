#include "shell.h"

/**
 **my_memset - fills memory with a constant byte
 *@s: the pointer to the memory area
 *@b: the byte to fill *s with
 *@n: the amount of bytes to be filled
 *Return: (s) a pointer to the memory area s
 */
char *my_memset(char *s, char b, unsigned int n)
{
	unsigned int i;

	for (i = 0; i < n; i++)
		s[i] = b;
	return (s);
}

/**
 * myfree - frees a string of strings
 * @ppp: string of strings
 */
void myfree(char **ppp)
{
	char **b = ppp;

	if (!ppp)
		return;
	while (*ppp)
		free(*ppp++);
	free(b);
}

/**
 * my_realloc - reallocates a block of memory
 * @ptr1: pointer to previous malloc'ated block
 * @myold_size: byte size of previous block
 * @mynew_size: byte size of new block
 *
 * Return: pointer to da ol block nameen.
 */
void *my_realloc(void *ptr1, unsigned int myold_size, unsigned int mynew_size)
{
	char *p1;

	if (!ptr1)
		return (malloc(mynew_size));
	if (!mynew_size)
		return (free(ptr1), NULL);
	if (mynew_size == myold_size)
		return (ptr1);

	p1 = malloc(mynew_size);
	if (!p1)
		return (NULL);

	myold_size = myold_size < mynew_size ? myold_size : mynew_size;
	while (myold_size--)
		p1[myold_size] = ((char *)ptr1)[myold_size];
	free(ptr1);
	return (p1);
}

