#ifndef _MAIN_H_
#define _MAIN_H_

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
extern char **environ;
int cmd_input(char **line, char *filename);
int cmd_run(char **commands, char *filename);
int cmd_flags(char **commands, char *filename);
int path_check(char *path_command);
char *cmd_path(char *execute_command);
void cmd_assembly(char *directory, char *command, char **output);
void cmd_env(void);

#endif
