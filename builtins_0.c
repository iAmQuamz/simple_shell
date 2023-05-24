 #include "shell.h"
/**
 * shell_env - prints env variables.
 *
 * Return: void
 */
int shell_env(void)
{
	int j;

	for (j = 0; environ[j]; j++)
	{
		_puts(environ[j]);
		_putchar('\n');
	}

	return (0);
}
/**
 * shell_exit - exit shell.
 * @args: args
 *
 */
void shell_exit(char **args)
{
	int status = 0;

	if (args[1] != NULL)
	{
		status = _atoi(args[1]);
	}
	free_tokens(args);
	free_prev_input();
	exit(status);
}
/**
 * shell_help - displays help info built-in cmds
 */
void shell_help(void)
{
	_puts("\nShell Version 1.0.0\n\n");
	_puts("Usage: ./hsh\n\n");
	_puts("Shell built-in commands:\n\n");
	_puts("help\t\tDisplay this help information\n\n");
	_puts("cd [dir]\tChange the current working directory\n\n");
	_puts("env\t\tDisplay the environment variables\n\n");
	_puts("setenv\t\tSet an environment variable\n\n");
	_puts("unsetenv\tUnset an environment variable\n\n");
	_puts("exit\t\tExit the shell\n\n");
}
/**
 * shell_setenv - Set value env var
 * @args: Args
 *
 * Return: Nothing
 */
int shell_setenv(char **args)
{
	char *name, *value;

	if (args[1] == NULL || args[2] == NULL)
	{
		_puterror("Usage: setenv VARIABLE VALUE\n");
		return (-1);
	}

	name = args[1];
	value = args[2];

	if (setenv(name, value, 1) != 0)
	{
		_puterror("setenv");
		return (-1);
	}
	return (0);
}

/**
 * shell_unsetenv - Unset env var
 * @args: Arguments (name of envir var)
 *
 * Return: void
 */
int shell_unsetenv(char **args)
{
	char *name;

	if (args[1] == NULL)
	{
		_puterror("Usage: unsetenv VARIABLE\n");
		return (-1);
	}

	name = args[1];

	if (unsetenv(name) != 0)
	{
		_puterror("unsetenv");
	}
	return (0);
}
