#include "shell.h"

/**
 * _strdup - this function duplicates a str in the heap memory.
 * @s: string parameter to be passed
 * Return: returns the duplicated string
 */
char *_strdup(const char *s)
{
	size_t len = _strlen(s) + 1;
	char *copy = malloc(sizeof(char) * len);

	if (copy != NULL)
		_memcpy(copy, s, len);

	return (copy);
}

/**
 * _strlen - this function returns the lenght of a string.
 * @s: string parameter to be passed
 * Return: returns the length of the string
 */
int _strlen(const char *s)
{
	int len = 0;

	while (*s != '\0')
	{
		len++;
		s++;
	}
	return (len);
}

/**
 * cmp_chars - this function compares characters of strings
 * @str: input string
 * @delim: delimiter
 * Return: 1 if strings are equal and 0 if otherwise
 */
int cmp_chars(char str[], const char *delim)
{
	unsigned int i, j, k = 0;

	for (i = 0; str[i]; i++)
	{
		for (j = 0; delim[j]; j++)
		{
			if (str[i] == delim[j])
			{
				k++;
				break;
			}
		}
	}
	return ((i == k) ? 1 : 0);
}

/**
 * _strtok - splits a string by some delimiter.
 * @str: input string.
 * @delim: delimiter.
 * Return: string splited.
 */
char *_strtok(char str[], const char *delim)
{
	char *current_char;
	unsigned int i, is_token_found;
	static char *token_start, *token_end;

	if (str != NULL)
	{
		if (cmp_chars(str, delim))
			return (NULL);
		token_start = str; /* Store first address */
		i = _strlen(str);
		token_end = &str[i]; /* Store last address */
	}
	current_char = token_start;
	if (current_char == token_end) /* Reaching the end */
		return (NULL);

	for (is_token_found = 0; *token_start; token_start++)
	{
		/* Breaking loop finding the next token */
		if (token_start != current_char)
			if (*token_start && *(token_start - 1) == '\0')
				break;
		/* Replacing delimiter for null char */
		for (i = 0; delim[i]; i++)
		{
			if (*token_start == delim[i])
			{
				*token_start = '\0';
				if (token_start == current_char)
					current_char++;
				break;
			}
		}
		if (is_token_found == 0 && *token_start) /* Str != Delim */
			is_token_found = 1;
	}
	if (is_token_found == 0) /* Str == Delim */
		return (NULL);
	return (current_char);
}

/**
 * _isdigit - this function checks if an input string paramater is a digit
 * @s: input string
 * Return: returns 1 if string is a number and 0 if otherwise
 */
int _isdigit(const char *s)
{
	unsigned int i;

	for (i = 0; s[i]; i++)
	{
		if (s[i] < 48 || s[i] > 57)
		{
			return (0);
		}
	}
	return (1);
}
