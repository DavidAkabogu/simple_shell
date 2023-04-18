#include "shell.h"

/**
 * add_separator_node_end - this function adds a separator found at the end of
 *				a separator_list_t.
 * @head: head of the linked list.
 * @sep: separator found (; | &).
 * Return: returns a pointer to the head node
 */
separator_list_t *add_separator_node_end(separator_list_t **head, char sep)
{
	separator_list_t *new, *temp;

	new = malloc(sizeof(separator_list_t));
	if (new == NULL)
		return (NULL);

	new->separator = sep;
	new->next = NULL;
	temp = *head;

	if (temp == NULL)
	{
		*head = new;
	}
	else
	{
		while (temp->next != NULL)
			temp = temp->next;
		temp->next = new;
	}

	return (*head);
}

/**
 * free_separator_list - frees a sep_list
 * @head: head of the linked list.
 */
void free_separator_list(separator_list_t **head)
{
	separator_list_t *temp, *curr;

	if (head != NULL)
	{
		curr = *head;
		while ((temp = curr) != NULL)
		{
			curr = curr->next;
			free(temp);
		}
		*head = NULL;
	}
}

/**
 * add_command_node_end - this function adds a command line at the end of a
 *				command_list_t.
 * @head: head of the linked list.
 * @line: command line.
 * Return: returns a pointer to the head node
 */
command_list_t *add_command_node_end(command_list_t **head, char *line)
{
	command_list_t *new, *temp;

	new = malloc(sizeof(command_list_t));
	if (new == NULL)
		return (NULL);

	new->line = line;
	new->next = NULL;
	temp = *head;

	if (temp == NULL)
	{
		*head = new;
	}
	else
	{
		while (temp->next != NULL)
			temp = temp->next;
		temp->next = new;
	}

	return (*head);
}

/**
 * free_command_list - this function frees a command_list_t
 * @head: head of the linked list.
 */
void free_command_list(command_list_t **head)
{
	command_list_t *temp, *curr;

	if (head != NULL)
	{
		curr = *head;
		while ((temp = curr) != NULL)
		{
			curr = curr->next;
			free(temp);
		}
		*head = NULL;
	}
}
