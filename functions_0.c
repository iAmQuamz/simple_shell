#include "shell.h"

/**
 * _puts - Prints a string to the standard output stream
 * @str: The string to print
 *
 * Return: Void
 */
void _puts(char *str)
{
	size_t len;
	ssize_t num_written;

	len = _strlen(str);
	num_written = write(STDOUT_FILENO, str, len);
	if (num_written == -1)
	{
		perror("write");
	}
}

/**
 * _puterror - Prints an error message to the standard error stream
 * @err: The error message to print
 *
 * Return: Void
 */
void _puterror(char *err)
{
	size_t len;
	ssize_t num_written;

	len = _strlen(err);
	num_written = write(STDERR_FILENO, err, len);
	if (num_written == -1)
	{
		perror("write");
	}
}
/**
 * execute - Execute a command with arguments.
 * @argv: An array of strings containing the command and its arguments.
 *
 * Return: The exit status of the executed command.
 */
int execute(char **argv)
{
	pid_t id;
	int status = 0;
	char *cmd_path, *envp[2];

	if (argv == NULL || *argv == NULL)
		return (status);
	if (check_for_builtin(argv))
		return (status);
	id = fork();
	if (id < 0)
	{
		_puterror("fork");
		return (1);
	}
	if (id == -1)
		perror(argv[0]), free_tokens(argv), free_prev_input();
	if (id == 0)
	{
		envp[0] = pathfinder();
		envp[1] = NULL;
		cmd_path = NULL;
		if (argv[0][0] != '/')
			cmd_path = find_in_path(argv[0]);
		if (cmd_path == NULL)
			cmd_path = argv[0];
		if (execve(cmd_path, argv, envp) == -1)
		{
			perror(argv[0]), free_tokens(argv), free_prev_input();
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		do {
			waitpid(id, &status, WUNTRACED);
		} while (!WIFEXITED(status) && !WIFSIGNALED(status));
	}
	return (status);
}

/**
 * get_line - reads input
 * Return: input
 */
void *get_line(void)
{
	static char buffer[BUFFER_SIZE];
	static int buffer_pos, buffer_size;
	char *string_of_input = NULL;
	char cr_char;
	int length_of_input = 0;
	/* ____ */
	while (1)
	{
		if (buffer_pos >= buffer_size)
		{
			buffer_size = read(STDIN_FILENO, buffer, BUFFER_SIZE);
			buffer_pos = 0;
			if (buffer_size == 0)
				return (string_of_input);
			else if (buffer_size < 0)
			{
				perror("read");
				return (NULL);
			}
		}

		cr_char = buffer[buffer_pos];

		buffer_pos++;

		if (cr_char == '\n')
		{
			string_of_input = realloc(string_of_input, length_of_input + 1);
			string_of_input[length_of_input] = '\0';
			return (string_of_input);
		}
		else
		{
			string_of_input = realloc(string_of_input, length_of_input + 1);
			string_of_input[length_of_input] = cr_char;
			length_of_input++;
		}
	}
}
