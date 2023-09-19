
#include "shell.h"

/**
 **my_strncpy - copie a string
 *@mydest: destination string to be copied to
 *@mysrc: source string
 *@n: amount of characters to be copied
 *Return: the concatenated string
 */
char *my_strncpy(char *mydest, char *mysrc, int n)
{
	int i, k;
	char *s = mydest;

	i = 0;
	while (mysrc[i] != '\0' && i < n - 1)
	{
		mydest[i] = mysrc[i];
		i++;
	}
	if (i < n)
	{
		k = i;
		while (k < n)
		{
			mydest[k] = '\0';
			k++;
		}
	}
	return (s);
}

/**
 **my_strncat - concatenates two strings
 *@mydest: first string
 *@mysrc: second string
 *@n: amount of the bytes to be maximally used
 *Return: the concatenated string
 */
char *my_strncat(char *mydest, char *mysrc, int n)
{
	int i, k;
	char *s = mydest;

	i = 0;
	k = 0;
	while (mydest[i] != '\0')
		i++;
	while (mysrc[k] != '\0' && k < n)
	{
		mydest[i] = mysrc[k];
		i++;
		k++;
	}
	if (k < n)
		mydest[i] = '\0';
	return (s);
}

/**
 **my_strchr - locates a character in a string
 *@s: string to be parsed
 *@a: character to look for
 *Return: (s) a pointer to the memory area s.
 */
char *my_strchr(char *s, char a)
{
	do {
		if (*s == a)
			return (s);
	} while (*s++ != '\0');

	return (NULL);
}
