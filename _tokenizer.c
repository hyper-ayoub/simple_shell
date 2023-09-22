#include "shell.h"

/**
 * split_string - splits a string into words using specified delimiters
 * @str: the input string
 * @delimiters: the delimiters used for splitting
 * Return: a pointer to an array of strings, or NULL on failure
 */
char **split_string(char *str, char *delimiters)
{
	int i, j, k, m, num_words = 0;
	char **tokens;

	if (str == NULL || str[0] == '\0')
		return (NULL);

	if (!delimiters)
		delimiters = " ";

	for (i = 0; str[i] != '\0'; i++)
		if (!is_delimiter(str[i], delimiters) && (is_delimiter(str[i + 1], delimiters) || !str[i + 1]))
			num_words++;

	if (num_words == 0)
		return (NULL);

	tokens = malloc((1 + num_words) * sizeof(char *));
	if (!tokens)
		return (NULL);

	for (i = 0, j = 0; j < num_words; j++)
	{
		while (is_delimiter(str[i], delimiters))
			i++;

		k = 0;
		while (!is_delimiter(str[i + k], delimiters) && str[i + k])
			k++;

		tokens[j] = malloc((k + 1) * sizeof(char));
		if (!tokens[j])
		{
			for (k = 0; k < j; k++)
				free(tokens[k]);
			free(tokens);
			return (NULL);
		}

		for (m = 0; m < k; m++)
			tokens[j][m] = str[i++];
		tokens[j][m] = '\0';
	}

	tokens[j] = NULL;
	return (tokens);
}

/**
 * split_string2 - splits a string into words using a single delimiter
 * @str: the input string
 * @delimiter: the delimiter used for splitting
 * Return: a pointer to an array of strings, or NULL on failure
 */
char **split_string2(char *str, char delimiter)
{
	int i, j, k, m, num_words = 0;
	char **tokens;

	if (str == NULL || str[0] == '\0')
		return (NULL);

	for (i = 0; str[i] != '\0'; i++)
		if ((str[i] != delimiter && str[i + 1] == delimiter) ||
		    (str[i] != delimiter && !str[i + 1]) || str[i + 1] == delimiter)
			num_words++;

	if (num_words == 0)
		return (NULL);

	tokens = malloc((1 + num_words) * sizeof(char *));
	if (!tokens)
		return (NULL);

	for (i = 0, j = 0; j < num_words; j++)
	{
		while (str[i] == delimiter && str[i] != delimiter)
			i++;

		k = 0;
		while (str[i + k] != delimiter && str[i + k] && str[i + k] != delimiter)
			k++;

		tokens[j] = malloc((k + 1) * sizeof(char));
		if (!tokens[j])
		{
			for (k = 0; k < j; k++)
				free(tokens[k]);
			free(tokens);
			return (NULL);
		}

		for (m = 0; m < k; m++)
			tokens[j][m] = str[i++];
		tokens[j][m] = '\0';
	}

	tokens[j] = NULL;
	return (tokens);
}

