#include "shell.h"

/**
 * shell_clear - clean slate on terminal screen.
 * @args: args array
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
