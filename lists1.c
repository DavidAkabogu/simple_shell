#include "shell.h"

/**
 * add_replacement_variable_node - adds a variable at the end of
 *					a replacement_variable_t list.
 * @head: head of the linked list.
 * @lvar: length of the variable.
 * @val: value of the variable.
 * @lval: length of the value.
 * Return: returns a pointer to the head node
 */
replacement_variable_t *add_replacement_variable_node(
		replacement_variable_t **head, int lvar, char *val, int lval)
{
	replacement_variable_t *new, *temp;

	new = malloc(sizeof(replacement_variable_t));
	if (new == NULL)
		return (NULL);

	new->len_var = lvar;
	new->val = val;
	new->len_val = lval;

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
 * free_replacement_variable_list - this function frees
 *					a replacement_variable_t list
 * @head: head of the linked list.
 */
void free_replacement_variable_list(replacement_variable_t **head)
{
	replacement_variable_t *temp, *curr;

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
