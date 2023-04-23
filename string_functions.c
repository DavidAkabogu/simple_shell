#include "shell.h"

/**
 * _strcat - tis function pointer concatenates two strings
 * @dest: destination pointer
 * @src: source pointer
 * Return: returns concatenated pointer
 */
char *_strcat(char *dest, const char *src)
{
	/* Find the end of the destination string */
	char *ptr = dest;

	while (*ptr != '\0')
		ptr++;

	/* Append the source string to the destination string */
	while (*src != '\0')
	{
		*ptr = *src;
		ptr++;
		src++;
	}
	/* Add a null terminator to the end of the concatenated string */
	*ptr = '\0';

	return (dest);
}
/**
 * *_strcpy - this function copies the string pointed to by src
 *		to the buffer pointed to by dest.
 * @dest: destination pointer
 * @src: source pointer
 * Return: returns a pointer to the destination string
 */
char *_strcpy(char *dest, char *src)
{

	size_t i;

	for (i = 0; src[i] != '\0'; i++)
		dest[i] = src[i];

	dest[i] = '\0';

	return (dest);
}
/**
 * _strcmp - this function compares two strings.
 * @s1: string to be compared
 * @s2: string to be compared
 * Return: returns an integer
 */
int _strcmp(char *s1, char *s2)
{
	while (*s1 != '\0' && *s2 != '\0')
	{
		if (*s1 != *s2)
		{
			return ((*s1 > *s2) ? 1 : -1);
		}
		s1++;
		s2++;
	}
	if (*s1 == '\0' && *s2 == '\0')
	{
		return (0);
	}
	return ((*s1 == '\0') ? -1 : 1);
}
/**
 * _strchr - this function locates a character in a string,
 * @s: string.
 * @c: character.
 * Return: returns a pointer to the first occurrence of c in string s
 *		or NULL if c is not found
 */
char *_strchr(char *s, char c)
{
	while (*s != '\0' && *s != c)
		s++;

	if (*s == c)
	{
		return (s);
	}
	else
	{
		return (NULL);
	}
}
/**
 * _strspn - this function gets the length of a prefix substring.
 * @s: string of characters.
 * @accept: bytes in initial segment of s
 * Return: returns number of bytes in initial segment of s which consists of
 *		only bytes from accept
 */
int _strspn(char *s, char *accept)
{
	int i, j, found;

	for (i = 0; s[i] != '\0'; i++)
	{
		found = 0;
		for (j = 0; accept[j] != '\0'; j++)
		{
			if (s[i] == accept[j])
			{
				found = 1;
				break;
			}
		}
		if (found == 0)
			return (i);
	}
	return (i);
}
