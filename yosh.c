/*
 *
 *  @author         Yousef Mohammed
 *  @description    YOSH - a simple shell program
 *  @github         ????
 *
 * */


#include <sys/wait.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "yosh_builtin_cmds.h"
#include "yosh_operations.h"


// main function for executing the shell
// argc is the argument count
// argv is the argument vector
int main(int argc, char **argv){

  // Run command loop.
  yosh_loop();

  // Perform any shutdown/cleanup.

  return EXIT_SUCCESS;
}

