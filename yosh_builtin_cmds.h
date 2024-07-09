#ifndef _YOSH_BUILTIN_CMDS_H
#define _YOSH_BUILTIN_CMDS_H	1


// declarations for the used functions
int yosh_num_builtins();
int yosh_cd(char **args);
int yosh_help(char **args);
int yosh_exit(char **args);

// String array holding names of the built-in cmds
char *builtin_str[] = {
    "cd",
    "help",
    "exit"
};

// Corresponding functions for the built-in cmds
int (*builtin_func[]) (char **) = {
    &yosh_cd,
    &yosh_help,
    &yosh_exit
};

// func to return number of built-in commands defined
int yosh_num_builtins() {
    return sizeof(builtin_str) / sizeof(char *);
}

// cd function
int yosh_cd(char **args){
    if (args[1] == NULL) {
        fprintf(stderr, "yosh: expected argument to \"cd\"\n");
    } 
    else {
        if (chdir(args[1]) != 0) {
            perror("yosh");
        }
    }
    return 1;
}

// help function
int yosh_help(char **args){
    int i;
    printf("------- Welcome to YOSH shell help menu!!\n");
    printf("------- To use the shell type your desired commands and hit enter.\n");
    printf("------- Example Commands you can run:\n");
    printf("            > Custom built-in yosh commands: help/exit/...\n");
    printf("            > Other external commands: ls/vim/...");

    // for (i = 0; i < yosh_num_builtins(); i++) {
    //     printf("/%s", builtin_str[i]);
    // }
    // printf("/...");


    printf("\n------- If you need more information about a certain command, try command_name --help or man command_name.\n");
    return 1;
}

// exit function
int yosh_exit(char **args){
    return 0;
}



#endif /* "yosh_builtin_cmds.h" included.  */
