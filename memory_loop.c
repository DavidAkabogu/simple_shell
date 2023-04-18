#include "shell.h"

/**
 * _memcpy - this function copies information between void pointers.
 * @newptr: destination pointer.
 * @ptr: source pointer.
 * @size: size of the new pointer.
 */
void _memcpy(void *newptr, const void *ptr, unsigned int size)
{
	unsigned int i;
	char *dest = (char *) newptr;
	const char *src = (const char *) ptr;

	for (i = 0; i < size; i++)
		dest[i] = src[i];
}

/**
 * _realloc - this function reallocates a memory block.
 * @ptr: pointer to the memory previously allocated.
 * @old_size: size, in bytes, of the allocated space for ptr.
 * @new_size: new size, in bytes, of the new memory block.
 * Return: returns a pointer or NULL if function fails
 */
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
	void *newptr;

	if (new_size == 0)
	{
		free(ptr);
		return (NULL);
	}

	if (new_size == old_size)
		return (ptr);

	newptr = malloc(new_size);
	if (newptr == NULL)
		return (NULL);

	if (ptr == NULL)
	{
		ptr = malloc(new_size);
		return (ptr);
	}
	else if (ptr != NULL)
	{
		_memcpy(newptr, ptr, old_size);
		free(ptr);
	}

	return (newptr);
}

/**
 * _reallocdp - this function reallocates a memory block of a double pointer.
 * @ptr: double pointer to the memory previously allocated.
 * @old_size: size, in bytes, of the allocated space of ptr.
 * @new_size: new size, in bytes, of the new memory block.
 * Return: returns a pointer or NULL if function fails
 */
char **_reallocdp(char **ptr, unsigned int old_size, unsigned int new_size)
{
	char **newptr;
	unsigned int i;

	if (ptr == NULL)
	{
		ptr = malloc(sizeof(char *) * new_size);
		return (ptr);
	}

	if (new_size == old_size)
		return (ptr);

	newptr = malloc(sizeof(char *) * new_size);
	if (newptr == NULL)
		return (NULL);

	for (i = 0; i < old_size; i++)
		newptr[i] = ptr[i];

	for (i = old_size; i < new_size; i++)
		newptr[i] = NULL;

	free(ptr);

	return (newptr);
}

/**
 * remove_comment - this function deletes comments from the input
 * @in: input string
 * Return: input without comments
 */
char *remove_comment(char *in)
{
	int i, up_to;

	up_to = 0;
	for (i = 0; in[i]; i++)
	{
		if (in[i] == '#')
		{
			if (i == 0)
			{
				free(in);
				return (NULL);
			}

			if (in[i - 1] == ' ' || in[i - 1] == '\t' || in[i - 1] == ';')
				up_to = i;
		}
	}

	if (up_to != 0)
	{
		in = _realloc(in, i, up_to + 1);
		in[up_to] = '\0';
	}

	return (in);
}

/**
 * run_shell_loop - Loop of shell
 * @datash: data relevant (av, input, args)
 */
void run_shell_loop(shell_data_t *datash)
{
	int loop, i_eof;
	char *input;

	loop = 1;
	while (loop == 1)
	{
		write(STDIN_FILENO, "^-^ ", 4);
		input = read_input_line(&i_eof);
		if (i_eof != -1)
		{
			input = remove_comment(input);
			if (input == NULL)
				continue;

			if (check_for_syntax_errors(datash, input) == 1)
			{
				datash->status = 2;
				free(input);
				continue;
			}
			input = replace_variable(input, datash);
			loop = split_commands_and_operators(datash, input);
			datash->counter += 1;
			free(input);
		}
		else
		{
			loop = 0;
			free(input);
		}
	}
}
