#include "shell.h"

/**
 * _getenv - Get the value of an environment variable
 * @name: Name of the environment variable
 *
 * Return: Value of the environment variable, or NULL if it doesn't exist
 */
char *_getenv(const char *name)
{
	char **env;
	size_t name_len = _strlen(name);

	for (env = environ; *env != NULL; env++)
	{
		if (_strncmp(*env, name, name_len) == 0 && (*env)[name_len] == '=')
		{
			return (&(*env)[name_len + 1]);
		}
	}

	return (NULL);
}
static char *prev_input;
/**
 * get_input - Read the line of input from user.
 *
 * Return: Pointer to a buffer conatining the user's input.
*/
char *get_input(void)
{
	char *input = NULL;
	size_t input_size = 0;
	ssize_t numread;

	do {
		/* print $ */
		prompt();

		/* get line of input */
		numread = getline(&input, &input_size, stdin);

		/* error check*/
		if (numread == -1)
		{
			free(input);
			_puts("\n");
			return (NULL);
		}

		/* rmv trailing space*/
		input[numread - 1] = '\0';

	} while (input[0] == '\0' || isspace(input[0]));

	/* update previous input */
	prev_input = input;
	return (input);
}

/**
 * free_prev_input - Frees the most recent input entered by the user.
 *
 * This function frees the memory allocated for the most recent input string
 * entered by the user. It should be called after the input string is no longer
 * needed.
 */
void free_prev_input(void)
{
	free(prev_input);
	prev_input = NULL;
}
/**
 * pathfinder - PATH env var value.
 *
 * Return: Pointer to $PATH.
 */
char *pathfinder(void)
{
	return (_getenv("PATH"));
}
/**
 * prompt - shell prompt stdout.
 *
 */
void prompt(void)
{
	_puts(PROMPT);
	fflush(stdout);
}
