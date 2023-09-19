#include "shell.h"

/**
*my_strlen - returns the length of a string
*@s: the string whose length to check
*
*Return: integer length of string
*/
int my_strlen(char *s)
{
    int i = 0;

    if (!s) 
        return (0);

    while (*s++)
        i++;
    return (i);        
}

/**
*my_strcmp - performs lexicogarphic comparison of the two strangs.
*@s2: the first strang
*@s3: the second strang
*
*Return: negative if s2 < s3, positive if s2 > s3, zero if s2 == s3
*/
int my_strcmp(char *s2, char *s3)
{
    while (*s2 && *s3)
	{
		if (*s2 != *s3)
			return (*s2 - *s3);
		s2++;
		s3++;
	}
	if (*s2 == *s3)
		return (0);
	else
		return (*s2 < *s3 ? -1 : 1);
}

/**
*mystrats_with - checks if needle strats with baystack
*@baystack: string to search
*@needle: the substring to find
*
*Return: the address of next char of baystack or NUll
*/
char *mystrats_with (const char *baystack, const char *needle)
{
    while (*needle)
        if (*needle++ != *baystack++)
            return (NULL);
    return ((char *)baystack);      
}

/**
 * my_strcat - concatenates of the two strings
 * @mydest: the destination buffer
 * @mysrc: the source buffer
 *
 * Return: pointer to destination buffer
 */
char *my_strcat(char *mydest, char *mysrc)
{
	char *ret0 = mydest;

	while (*mydest)
		mydest++;
	while (*mysrc)
		*mydest++ = *mysrc++;
	*mydest = *mysrc;
	return (ret0);
}

