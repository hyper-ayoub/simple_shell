#include "shell.h"

/**
 * my_free - Frees a pointer and sets it to NULL.
 * @ptr: Address of the pointer to free.
 *
 * Return: 1 if freed, otherwise 0.
 */
int my_free(void **ptr)
{
    if (ptr && *ptr)
    {
        free(*ptr);
        *ptr = NULL;
        return (1);
    }
    return (0);
}

