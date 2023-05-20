#include "shell.h"

/**
 * shell_cd - change working dir of shell
 * @args: args
 */
void shell_cd(char **args)
{
	char *directories = args[1];
	int ret;

	/* If no argument is provided, change to HOME directory */
	if (directories == NULL)
	{
		dir = _getenv("HOME");
		if (directories == NULL)
		{
			_puts("cd: No HOME directory found\n");
			return;
		}
	}

	ret = chdir(directories);
	if (ret == -1)
	{
		perror("cd");
	}
}
