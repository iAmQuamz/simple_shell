#include "shell.h"
/**
 * get_line - readsinput from SI
 * Return: string
 */
void *get_line(void)
{
	static char buffer[BUFFER_SIZE];
	static int buffer_pos, buffer_size;
	char *string_of_input = NULL;
	char cr_char;
	int length_of_input = 0;

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

