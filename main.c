#include "main.h"
char *builtin_str[] = {
	"cd",
	"help",
	"exit"
};

int (*builtin_func[]) (char **) = {
	&builtins_cd,
	&builtins_help,
	&builtins_exit
};
/**
 * main - entry
 * @argc: count
 * @argv: inputs
 *
 * Return: 0
 *
 */

int main(int __attribute__((unused)) argc, char __attribute__((unused)) **argv)
{
	run_cmd();

	return EXIT_SUCCESS;
}
