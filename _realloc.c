#include "shell.h"

/**
 * custom_memset - Fills memory with a constant byte.
 * @mem: The pointer to the memory area.
 * @value: The byte to fill @mem with.
 * @size: The amount of bytes to be filled.
 *
 * Return: A pointer to the memory area @mem.
 */
char *custom_memset(char *mem, char value, unsigned int size)
{
    unsigned int i;

    for (i = 0; i < size; i++)
        mem[i] = value;

    return (mem);
}

/**
 * free_string_array - Frees an array of strings.
 * @str_array: The array of strings to free.
 */
void free_string_array(char **str_array)
{
    char **temp = str_array;

    if (!str_array)
        return;

    while (*str_array)
        free(*str_array++);

    free(temp);
}

/**
 * custom_realloc - Reallocates a block of memory.
 * @ptr: Pointer to the previous malloc'ed block.
 * @old_size: Byte size of the previous block.
 * @new_size: Byte size of the new block.
 *
 * Return: Pointer to the reallocated block.
 */
void *custom_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
    char *new_ptr;

    if (!ptr)
        return (malloc(new_size));

    if (!new_size)
        return (free(ptr), NULL);

    if (new_size == old_size)
        return (ptr);

    new_ptr = malloc(new_size);

    if (!new_ptr)
        return (NULL);

    old_size = old_size < new_size ? old_size : new_size;

    while (old_size--)
        new_ptr[old_size] = ((char *)ptr)[old_size];

    free(ptr);
    return (new_ptr);
}

