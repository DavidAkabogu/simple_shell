#include "shell.h"

/**
 * reverse_string - this function reverses a string.
 * @s: input string.
 */
void reverse_string(char *s)
{
	int i, len = _strlen(s);
	char temp;

	for (i = 0; i < len / 2; i++)
	{
		temp = s[i];
		s[i] = s[len - 1 - i];
		s[len - 1 - i] = temp;
	}
}
