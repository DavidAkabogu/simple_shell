#include "shell.h"

/**
 * swap_characters - this function swaps | and & for non-printed chars
 * @input: input string
 * @bool: type of swap
 * Return: swapped string
 */
char *swap_characters(char *input, int bool)
{
	int i;

	if (bool == 0)
	{
		for (i = 0; input[i]; i++)
		{
			if (input[i] == '|')
			{
				if (input[i + 1] != '|')
					input[i] = 16;
				else
					i++;
			}

			if (input[i] == '&')
			{
				if (input[i + 1] != '&')
					input[i] = 12;
				else
					i++;
			}
		}
	}
	else
	{
		for (i = 0; input[i]; i++)
		{
			input[i] = (input[i] == 16 ? '|' : input[i]);
			input[i] = (input[i] == 12 ? '&' : input[i]);
		}
	}
	return (input);
}

/**
 * add_nodes_to_list - this function adds separators and cmd lines in the lists
 * @head_s: head of separator list
 * @head_l: head of command lines list
 * @input: input string
 */
void add_nodes_to_list(
		separator_list_t **head_s, command_list_t **head_l, char *input)
{
	int i;
	char *line;

	input = swap_characters(input, 0);

	for (i = 0; input[i]; i++)
	{
		if (input[i] == ';')
			add_separator_node_end(head_s, input[i]);

		if (input[i] == '|' || input[i] == '&')
		{
			add_separator_node_end(head_s, input[i]);
			i++;
		}
	}

	line = _strtok(input, ";|&");
	do {
		line = swap_characters(line, 1);
		add_command_node_end(head_l, line);
		line = _strtok(NULL, ";|&");
	} while (line != NULL);

}

/**
 * move_to_next - go to the next command line stored
 * @list_s: separator list
 * @list_l: command line list
 * @datash: data structure
 */
void move_to_next(
		separator_list_t **list_s, command_list_t **list_l, shell_data_t *datash)
{
	int loop_sep;
	separator_list_t *ls_s;
	command_list_t *ls_l;

	loop_sep = 1;
	ls_s = *list_s;
	ls_l = *list_l;

	while (ls_s != NULL && loop_sep)
	{
		if (datash->status == 0)
		{
			if (ls_s->separator == '&' || ls_s->separator == ';')
				loop_sep = 0;
			if (ls_s->separator == '|')
				ls_l = ls_l->next, ls_s = ls_s->next;
		}
		else
		{
			if (ls_s->separator == '|' || ls_s->separator == ';')
				loop_sep = 0;
			if (ls_s->separator == '&')
				ls_l = ls_l->next, ls_s = ls_s->next;
		}
		if (ls_s != NULL && !loop_sep)
			ls_s = ls_s->next;
	}

	*list_s = ls_s;
	*list_l = ls_l;
}

/**
 * split_commands_and_operators - splits command lines according to
 * the separators ;, | and &, and executes them
 * @datash: data structure
 * @input: input string
 * Return: 0 to exit, 1 to continue
 */
int split_commands_and_operators(shell_data_t *datash, char *input)
{

	separator_list_t *head_s, *list_s;
	command_list_t *head_l, *list_l;
	int loop;

	head_s = NULL;
	head_l = NULL;

	add_nodes_to_list(&head_s, &head_l, input);

	list_s = head_s;
	list_l = head_l;

	while (list_l != NULL)
	{
		datash->input = list_l->line;
		datash->args = split_input_line(datash->input);
		loop = execute_input_line(datash);
		free(datash->args);

		if (loop == 0)
			break;

		move_to_next(&list_s, &list_l, datash);

		if (list_l != NULL)
			list_l = list_l->next;
	}

	free_separator_list(&head_s);
	free_command_list(&head_l);

	if (loop == 0)
		return (0);
	return (1);
}

/**
 * split_input_line - tokenizes the input string
 * @input: input string.
 * Return: string splitted.
 */
char **split_input_line(char *input)
{
	size_t bsize;
	size_t i;
	char **tokens;
	char *token;

	bsize = TOKEN_BUFFER_SIZE;
	tokens = malloc(sizeof(char *) * (bsize));
	if (tokens == NULL)
	{
		write(STDERR_FILENO, ": allocation error\n", 18);
		exit(EXIT_FAILURE);
	}

	token = _strtok(input, TOKEN_DELIMITER);
	tokens[0] = token;

	for (i = 1; token != NULL; i++)
	{
		if (i == bsize)
		{
			bsize += TOKEN_BUFFER_SIZE;
			tokens = _reallocdp(tokens, i, sizeof(char *) * bsize);
			if (tokens == NULL)
			{
				write(STDERR_FILENO, ": allocation error\n", 18);
				exit(EXIT_FAILURE);
			}
		}
		token = _strtok(NULL, TOKEN_DELIMITER);
		tokens[i] = token;
	}

	return (tokens);
}
