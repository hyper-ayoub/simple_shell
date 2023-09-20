#include "shell.h"
#include <string.h> /* Add this line to include the string.h header. */

/**
 * myadd_node1 - adds the  node to the start of the list
 * @h:  the address of pointer to head node
 * @str: str field of node
 * @num: node index used by  the history
 *
 * Return: size of list
 */
list_t *myadd_node1(list_t **h, const char *str, int num)
{
	list_t *first_h;

	if (!h)
		return (NULL);
	first_h = malloc(sizeof(list_t));
	if (!first_h)
		return (NULL);
	memset((void *)first_h, 0, sizeof(list_t));
	first_h->num = num;
	if (str)
	{
		first_h->str = strdup(str); /* Change _strdup to strdup */
		if (!first_h->str)
		{
			free(first_h);
			return (NULL);
		}
	}
	first_h->next = *h;
	*h = first_h;
	return (first_h);
}

/**
 * add_node1_end - adds the node to the end of the list
 * @h: the address of pointer to head node
 * @str: str field of node
 * @num: node index used by the history
 *
 * Return: size of list
 */
list_t *add_node1_end(list_t **h, const char *str, int num)
{
	list_t *first_node1, *node1;

	if (!h)
		return (NULL);

	node1 = *h;
	first_node1 = malloc(sizeof(list_t));
	if (!first_node1)
		return (NULL);
	memset((void *)first_node1, 0, sizeof(list_t));
	first_node1->num = num;
	if (str)
	{
		first_node1->str = strdup(str); /* Change _strdup to strdup */
		if (!first_node1->str)
		{
			free(first_node1);
			return (NULL);
		}
	}
	if (node1)
	{
		while (node1->next)
			node1 = node1->next;
		node1->next = first_node1;
	}
	else
		*h = first_node1;
	return (first_node1);
}

/**
 * free_list1 - frees all nodes of a list
 * @h_ptr:  the address of pointer to head node
 *
 * Return: void
 */
void free_list1(list_t **h_ptr)
{
	list_t *node1, *first_node1, *h;

	if (!h_ptr || !*h_ptr)
		return;
	h = *h_ptr;
	node1 = h;
	while (node1)
	{
		first_node1 = node1->next;
		free(node1->str);
		free(node1);
		node1 = first_node1;
	}
	*h_ptr = NULL;
}

/**
 * print_ls_str - prints only the str element of a list_t linked list
 * @p:  the pointer to first node
 *
 * Return: size of list
 */
size_t print_ls_str(const list_t *p)
{
	size_t i = 0;

	while (p)
	{
		puts(p->str ? p->str : "(nil)");
		puts("\n");
		p = p->next;
		i++;
	}
	return (i);
}

/**
 * dlt_node1_in_index - deletes node at given index
 * @h:  the address of pointer to first node
 * @index:  the index of node to delete
 *
 * Return: 1 on success, 0 on failure
 */
int dlt_node1_in_index(list_t **h, unsigned int index)
{
	list_t *node1, *first_node1;
	unsigned int i = 0;

	if (!h || !*h)
		return (0);

	if (!index)
	{
		node1 = *h;
		*h = (*h)->next;
		free(node1->str);
		free(node1);
		return (1);
	}
	node1 = *h;
	while (node1)
	{
		if (i == index)
		{
			first_node1->next = node1->next;
			free(node1->str);
			free(node1);
			return (1);
		}
		i++;
		first_node1 = node1;
		node1 = node1->next;
	}
	return (0);
}
