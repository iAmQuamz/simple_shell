#include "shell.h"

/**
 * shell_cd - change working dir of shell
 * @args: args
 */
void shell_cd(char **args)
{
	char *directories = args[1];
	int rett;

	/* If no argument is provided, change to HOME directory */
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
