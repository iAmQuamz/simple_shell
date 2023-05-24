 #include "shell.h"

/**
 * check_for_builtin - check cmd if builtin
 * @args: array args
 *
 * Return: 1 if true/ 0 if otherwise
 */
int check_for_builtin(char **args)
{
	if (!args[0])
		return (0);
	if (!_strcmp(args[0], "exit"))
		shell_exit(args);
	else if (!_strcmp(args[0], "env"))
		shell_env();
	else if (!_strcmp(args[0], "setenv"))
		shell_setenv(args);
	else if (!_strcmp(args[0], "unsetenv"))
		shell_unsetenv(args);
	else if (!_strcmp(args[0], "help"))
		shell_help();
	else if (!_strcmp(args[0], "cd"))
		shell_cd(args);
	else if (!_strcmp(args[0], "clear"))
		shell_clear(args);
	else
		return (0);
	return (1);
}
#include "shell.h"

/**
 * shell_cd - change dir of shell
 * @args: args
 */
void shell_cd(char **args)
{
	char *directories = args[1];
	int rett;

	/* !args change dir to home */
	if (directories == NULL)
	{
		directories = _getenv("HOME");
		if (directories == NULL)
		{
			_puts("cd: No HOME directory found\n");
			return;
		}
	}

	rett = chdir(directories);
	if (rett == -1)
	{
		perror("cd");
	}
}
#include "shell.h"

/**
 * shell_clear - clear terminal
 * @args: args
 *
 * Return: 1-continue
 *         0 to exit.
*/
int shell_clear(char **args)
{
	(void)args; /* avoid "unsued parameter" warning */
	_puts("\033[2J\033[H");
	return (1);
}
