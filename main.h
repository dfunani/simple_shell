#ifndef _MAIN_H_
#define _MAIN_H_

#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define LSH_TOK_BUFSIZE 64
#define LSH_TOK_DELIM " \t\r\n\a"

void run_cmd();
int execute_cmd(char **args);
char **split_line(char *line);
char *read_line(void);
int launch_cmd(char **args);
int builtins_handler(void);
int builtins_cd(char **args);
int builtins_help(char **args);
int builtins_exit(char **args);
extern char *builtin_str[3];

extern int (*builtin_func[]) (char **);
#endif
