#include "main.h"

/**
 * cmd_assembly - function that assembly command.
 * @directory: directory
 * @command: command
 * @output: output
 *
 * Return: Nothing.
 */

void cmd_assembly(char *directory, char *command, char **output)
{
	strcat(*output, directory);
	strcat(*output, "/");
	strcat(*output, command);
	strcat(*output, "\0");
}

/**
 * cmd_path - function that finds the path to execute command
 * @command: command
 *
 * Return: Nothing.
 */

char *cmd_path(char *command)
{
	int i = 0;
	char *token = NULL;
	char *ptr = NULL;
	struct stat sb;
	char *cache;

	while (environ[i])
	{
		cache = strdup(environ[i]);
		token = strtok(cache, "=");

		if (strcmp(token, "PATH") == 0)
		{
			token = strtok(NULL, "=");
			token = strtok(token, ":");

			while (token)
			{
				ptr = calloc(sizeof(char),
					     strlen(command) +
					     strlen(token) + 2);
				cmd_assembly(token, command, &ptr);

				if (stat(ptr, &sb) == 0)
				{
					command = ptr;
					free(cache);
					return (command);
				}
				free(ptr);
				token = strtok(NULL, ":");
			}
			free(cache);
			break;
		}
		free(cache);
		i++;
	}
	return (NULL);
}

/**
 * path_check - function that print the path
 * @path_command: command from path
 *
 * Return: Nothing.
 */
int path_check(char *path_command)
{
	int have_slash = 0;
	int index = 0;

	if (!path_command)
		return (0);
	while (path_command[index])
	{
		if (path_command[index] == '/')
			have_slash = 1;
		index += 1;
	}

	return (have_slash);
}

/**
 * cmd_flags - check commands before executing them
 * @commands: commands
 * @filename: filename
 *
 * Return: int as status.
 */
int cmd_flags(char **commands, char *filename)
{
	char *commandWithPath = NULL;
	int codestatus = 0;

	if (strcmp(commands[0], "env") == 0)
	{
		cmd_env();
		return (1);
	}

	if (!path_check(commands[0]))
	{
		commandWithPath = cmd_path(commands[0]);
		if (!commandWithPath)
		{
			dprintf(STDERR_FILENO,
				"%s: 1: %s: not found\n",
				filename, commands[0]);
			return (0);
		}
		commands[0] = commandWithPath;
	}

	if (access(commands[0], F_OK) == -1)
	{
		dprintf(STDERR_FILENO,
			"%s: 1: %s: not found\n", filename, commands[0]);
		return (0);
	}

	codestatus = cmd_run(&*commands, filename);

	if (commandWithPath)
		free(commandWithPath);

	return (codestatus);
}

/**
 * cmd_input - function that input command
 * @prompt: prompt
 * @filename: filename
 *
 * Return: Nothing.
 */
int cmd_input(char **prompt, char *filename)
{
	char *split_text;
	int index = 0;
	char *arguments[1024] = {NULL};
	int is_exit = 0;

	split_text = strtok(*prompt, " \t\n\r");
	while (split_text)
	{
		if (strlen(split_text) > 0)
		{
			arguments[index] = split_text;
			index += 1;
		}
		if (strcmp(split_text, "exit") == 0)
			is_exit = 1;
		split_text = strtok(NULL, " \t\n\r");
	}
	if (!arguments[0])
		return (0);
	if (!cmd_flags(arguments, filename))
	{
		free(*prompt);
		if (!isatty(STDIN_FILENO))
		{
			if (!is_exit)
				exit(127);
			exit(2);
		}
	}
	return (2);
}
