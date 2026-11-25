



#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    while(1) {
        char cwd[1024];
        if (getcwd(cwd, sizeof(cwd)) != NULL) {
            printf("prateek@customshell : %s > ", cwd);
        }
        else {
            printf("prateek@customshell> ");
        }
        
        char command[100];
        fgets(command, 100, stdin);
        command[strlen(command)-1] = '\0';

        char *args[100];
        int i = 0;
        char *token = strtok(command, " ");
        while (token != NULL) {
            args[i] = token;
            i++;
            token = strtok(NULL, " ");
        }
        args[i] = NULL;
        if (args[0]==0) {
            continue;
        }
        if (strcmp(args[0], "exit")==0) {
            break;
        }
        if (strcmp(args[0], "cd")==0) {
            if (args[1]==NULL) {
                printf("Error: Expected a folder name after 'cd'\n");
            }
            else {
                if (chdir(args[1]) != 0) {
                    printf("Folder not found!\n");
                }
            }
        }
        else {
            int pid = fork();
            if (pid == 0) {
                execvp(args[0], args);
                printf("Command not found\n");
                exit(1);
            }
            else {
                wait(NULL);
            }
        }
    }

    return 0;
} 