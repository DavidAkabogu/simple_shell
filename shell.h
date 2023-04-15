#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <limits.h>
#include <signal.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <sys/types.h>

#define BUFFER_SIZE 1024
#define TOKEN_BUFFER_SIZE 128
#define TOKEN_DELIMITER " \t\r\n\a"

/* Pointer to an array of pointers to strings called the "environment" */
extern char **environ;

/**
 * struct shell_data - struct that contains all relevant data on runtime
 * @av: ARGument Vector
 * @input: command line written by the user
 * @args: tokens of the command line
 * @status: last status of the shell
 * @counter: lines counter
 * @_environ: environment variable
 * @pid: process ID of the shell
 */
typedef struct shell_data
{
	int counter;
	int status;
	char **av;
	char *input;
	char **args;
	char **_environ;
	char *pid;
} shell_data_t;

/**
 * struct separator_list_s - single linked list
 * @separator: ; | &
 * @next: next node
 * Description: single linked list to store separators
 */
typedef struct separator_list_s
{
	char separator;
	struct separator_list_s *next;
} separator_list_t;

/**
 * struct command_list_s - single linked list
 * @line: command line
 * @next: next node
 * Description: single linked list to store command lines
 */
typedef struct command_list_s
{
	char *line;
	struct command_list_s *next;
} command_list_t;

/**
 * struct replacement_variable_list - single linked list
 * @len_var: length of the variable
 * @val: value of the variable
 * @len_val: length of the value
 * @next: next node
 * Description: single linked list to store variables
 */
typedef struct replacement_variable_list
{
	char *val;
	int len_var;
	int len_val;
	struct replacement_variable_list *next;
} replacement_variable_t;

/**
 * struct builtin_s - Builtin struct for command args.
 * @name: The name of the command builtin i.e cd, exit, env
 * @f: data type pointer function.
 */
typedef struct builtin_s
{
	char *name;
	int (*f)(data_shell *datash);
} builtin_t;

/* memory_functions.c */
char **_reallocdp(char **ptr, unsigned int old_size, unsigned int new_size);
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size);
void _memcpy(void *newptr, const void *ptr, unsigned int size);

/* lists.c */
separator_list_t *add_separator_node_end(separator_list_t **head, char sep);
command_list_t *add_command_node_end(command_list_t **head, char *line);
void free_separator_list(separator_list_t **head);
void free_command_list(command_list_t **head);

/* lists1.c */
replacement_variable_t *add_replacement_variable_node(
		replacement_variable_t **head, int lvar, char *var, int lval);
void free_replacement_variable_list(replacement_variable_t **head);

/* string_functions.c */
int _strcmp(char *s1, char *s2);
int _strspn(char *s, char *accept);
char *_strcat(char *dest, const char *src);
char *_strcpy(char *dest, char *src);
char *_strchr(char *s, char c);

/* string_functions1.c */
int _strlen(const char *s);
int _isdigit(const char *s);
int cmp_chars(char str[], const char *delim);
char *_strtok(char str[], const char *delim);
char *_strdup(const char *s);

/* string_functions2.c */
void reverse_string(char *s);

/* check_syntax_error.c */
int check_repeated_char(char *input, int i);
int check_error_sep_op(char *input, int i, char last);
int check_first_char(char *input, int *i);
int check_for_syntax_errors(shell_data_t *datash, char *input);
void print_syntax_error(shell_data_t *datash, char *input, int i, int bool);

/* shell_loop.c */
char *remove_comment(char *in);
void run_shell_loop(shell_data_t *datash);

/* split.c */
char **split_input_line(char *input);
char *swap_characters(char *input, int bool);
int split_commands_and_operators(shell_data_t *datash, char *input);
void add_nodes_to_list(separator_list_t **head_s, command_list_t **head_l,
		char *input);
void move_to_next(separator_list_t **list_s, command_list_t **list_l,
		shell_data_t *datash);

/* replacement_variables.c */
char *replace_variable(char *input, shell_data_t *datash);
char *get_replaced_input(replacement_variable_t **head, char *input,
		char *new_input, int nlen);
int replace_variables(replacement_variable_t **h, char *in, char *st,
		shell_data_t *data);
void check_for_environment_variables(replacement_variable_t **h, char *in,
		shell_data_t *data);

/* get_input_line.c */
ssize_t get_input_line(char **lineptr, size_t *n, FILE *stream);
void read_input_line_from_buffer(char **lineptr, size_t *n, char *buffer,
		size_t j);

/* read_input_line.c */
char *read_input_line(int *i_eof);

/* execute_line */
int execute_input_line(shell_data_t *datash);

/* execute_commands.c */
char *find_command(char *cmd, char **_environ);
int execute_command(shell_data_t *datash);
int is_current_directory(char *path, int *i);
int is_command_executable(shell_data_t *datash);
int check_for_command_errors(char *dir, shell_data_t *datash);

/* environment.c */
int print_environment_variables(shell_data_t *datash);
char *get_environment_variable(const char *name, char **_environ);

/* environment1.c */
char *copy_info(char *name, char *value);
void set_env(char *name, char *value, shell_data_t *datash);
int _setenv(shell_data_t *datash);
int _unsetenv(shell_data_t *datash);

/* change_directory.c */
void change_to_directory(shell_data_t *datash);
void change_to_dot_directory(shell_data_t *datash);
void change_to_home_directory(shell_data_t *datash);
void change_to_previous_directory(shell_data_t *datash);

/* change_directory_shell.c */
int change_directory_shell(shell_data_t *datash);

/* standard_library.c */
int get_integer_length(int n);
char *convert_integer_to_string(int n);
int convert_string_to_integer(char *s);

/* error_messages.c */
char *cd_error_message(shell_data_t *, char *, char *, char *);
char *error_message_get_cd(shell_data_t *datash);
char *error_message_not_found(shell_data_t *datash);
char *error_message_exit_shell(shell_data_t *datash);

/* error_messages1.c */
char *error_message_get_alias(char **args);
char *error_message_env(shell_data_t *datash);
char *error_message_syntax(char **args);
char *error_message_permission(char **args);
char *error_message_path_126(shell_data_t *datash);

/* print_help.c */
void print_help_env(void);
void print_help_setenv(void);
void print_help_unsetenv(void);
void print_help_general(void);
void print_help_exit(void);

/* print_help1.c */
void print_help(void);
void print_help_alias(void);
void print_help_cd(void);

/* get_help.c */
int get_help(shell_data_t *datash);

/* get_error_code.c */
int get_error_code(shell_data_t *datash, int eval);

/* get_sigint.c */
void handle_sigint(int sig);

/* get_builtin_function */
int (*get_builtin_function(char *cmd))(shell_data_t *datash);

/* exit_command.c */
int exit_shell_program(shell_data_t *datash);

#endif
