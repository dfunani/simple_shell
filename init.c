#include "main.h"

/**
 * cmd_run - a function that execute commands
 * @commands: commands
 * @filename: filename
 *
 * Return: Nothing.
 */

int cmd_run(char **commands, char *filename)
{
	pid_t pid;
	int status = 0;

	pid = fork();
	if (pid == 0 && commands[0])
	{
		if (execve(commands[0], commands, environ) != -1)
			return (0);
		dprintf(STDERR_FILENO, "%s: cannot access '%s': No such file or directory\n",
				commands[0], filename);
		exit(2);
	}
	else if (pid == -1)
		perror("Error");

	waitpid(pid, &status, 0);
	return (1);
}

/**
 * cmd_env - implements the env built-in
 * Description prints the current environment
 * Return: 0
 */
void cmd_env(void)
{
	int i = 0;

	for (; environ[i]; i++)
		printf("%s\n", environ[i]);
}
