#include "shell.h"

/**
 * list_length - determines the length of a linked list
 * @h: pointer to the first node
 *
 * Return: size of the list
 */
size_t list_length(const list_t *h)
{
    size_t i = 0;

    while (h)
    {
        h = h->next;
        i++;
    }
    return (i);
}

/**
 * list_to_str_array - returns an array of strings from the list->data
 * @head: pointer to the first node
 *
 * Return: array of strings
 */
char **list_to_str_array(list_t *head)
{
    list_t *node = head;
    size_t i = list_length(head), j;
    char **strs;
    char *str;

    if (!head || !i)
        return (NULL);

    strs = malloc(sizeof(char *) * (i + 1));
    if (!strs)
        return (NULL);

    for (i = 0; node; node = node->next, i++)
    {
        str = malloc(_strlen(node->data) + 1);
        if (!str)
        {
            for (j = 0; j < i; j++)
                free(strs[j]);
            free(strs);
            return (NULL);
        }

        str = _strcpy(str, node->data);
        strs[i] = str;
    }

    strs[i] = NULL;
    return (strs);
}

/**
 * print_list_elements - prints all elements of a list_t linked list
 * @h: pointer to the first node
 *
 * Return: size of the list
 */
size_t print_list_elements(const list_t *h)
{
    size_t i = 0;

    while (h)
    {
        _puts(convert_number(h->num, 10, 0));
        _putchar(':');
        _putchar(' ');
        _puts(h->data ? h->data : "(nil)");
        _puts("\n");
        h = h->next;
        i++;
    }
    return (i);
}

/**
 * find_node_with_prefix - returns the node whose data starts with a prefix
 * @node: pointer to the list head
 * @prefix: string to match
 * @c: the next character after prefix to match
 *
 * Return: matching node or NULL
 */
list_t *find_node_with_prefix(list_t *node, char *prefix, char c)
{
    char *p = NULL;

    while (node)
    {
        p = starts_with(node->data, prefix);
        if (p && ((c == -1) || (*p == c)))
            return (node);
        node = node->next;
    }
    return (NULL);
}

/**
 * get_node_index - gets the index of a node
 * @head: pointer to list head
 * @node: pointer to the node
 *
 * Return: index of node or -1
 */
ssize_t get_node_index(list_t *head, list_t *node)
{
    size_t i = 0;

    while (head)
    {
        if (head == node)
            return (i);
        head = head->next;
        i++;
    }
    return (-1);
}

