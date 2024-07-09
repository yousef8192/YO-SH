#ifndef _YOSH_OPERATIONS_H
#define _YOSH_OPERATIONS_H	1

#define YOSH_RL_BUFSIZE 1024
#define YOSH_TOK_BUFSIZE 64
#define YOSH_TOK_DELIM " \t\r\n\a"

// start the shell in a child process 
// wait() for it in the parent process so that it doesn't become a zombie process
int yosh_launch(char **args){

    pid_t pid;
    int status;

    pid = fork();

    // Child proc
    if (pid == 0) {
        if (execvp(args[0], args) == -1) {
            perror("yosh");
        }
        exit(EXIT_FAILURE);
    } 

    // forking is unsucessful
    else if (pid < 0) {
        perror("yosh");
    } 

    // Parent proc
    else {
        do {
            waitpid(pid, &status, WUNTRACED);
        } while (!WIFEXITED(status) && !WIFSIGNALED(status));
    }

    return 1;
}

// execute the given command with its arguments
// return 1 if the shell should continue running, and 0 if it should terminate
int yosh_execute(char **args){

    // if an empty cmd is entered return 1
    if (args[0] == NULL) {
        return 1;
    }

    // check if the input cmd is one of the built-in ones
    // execute its corresponding func we defined and return what it returns
    for (int i = 0; i < yosh_num_builtins(); i++) {
        if (strcmp(args[0], builtin_str[i]) == 0) {
            return (*builtin_func[i])(args);
        }
    }

    // else (i.e. cmd isn't a built-in one) execute the entered cmd using the execve sysCall
    return yosh_launch(args);
}

// here we read a line of input from stdin and return it
char *yosh_read_line(void){

    int bufsize = YOSH_RL_BUFSIZE;
    int position = 0;
    char *buffer = malloc(sizeof(char) * bufsize);
    int c;

    if (!buffer) {
        fprintf(stderr, "yosh: allocation error\n");
        exit(EXIT_FAILURE);
    }

    while (1) {
        // read a character
        c = getchar();

        if (c == EOF) {
            exit(EXIT_SUCCESS);
        } 
        else if (c == '\n') {
            buffer[position] = '\0';
            return buffer;
        } 
        else {
            buffer[position] = c;
        }
        position++;

        // reallocate if we exceeded the buffer
        if (position >= bufsize) {
            bufsize += YOSH_RL_BUFSIZE;
            buffer = realloc(buffer, bufsize);
            if (!buffer) {
            fprintf(stderr, "yosh: allocation error\n");
            exit(EXIT_FAILURE);
            }
        }
    }
}

// here we split the input string into multiple tokens
char **yosh_split_line(char *line){

    int bufsize = YOSH_TOK_BUFSIZE, position = 0;
    char **tokens = malloc(bufsize * sizeof(char*));
    char *token, **tokens_backup;

    if (!tokens) {
        fprintf(stderr, "yosh: allocation error\n");
        exit(EXIT_FAILURE);
    }

    token = strtok(line, YOSH_TOK_DELIM);
    while (token != NULL) {
        tokens[position] = token;
        position++;

        if (position >= bufsize) {
            bufsize += YOSH_TOK_BUFSIZE;
            tokens_backup = tokens;
            tokens = realloc(tokens, bufsize * sizeof(char*));
            if (!tokens) {
                free(tokens_backup);
                fprintf(stderr, "yosh: allocation error\n");
                exit(EXIT_FAILURE);
            }
        }

        token = strtok(NULL, YOSH_TOK_DELIM);
    }
    tokens[position] = NULL;
    return tokens;
}

// here we loop for getting input and executing it
void yosh_loop(void){

    char *line;
    char **args;
    int status;

    do {
        printf("> ");
        line = yosh_read_line();
        args = yosh_split_line(line);
        status = yosh_execute(args);

        free(line);
        free(args);
    } while (status);

}


#endif /* "yosh_operations.h" included.  */
