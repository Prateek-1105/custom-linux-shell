/*
Task: Build the base skeleton of a Custom Linux Shell

Write a C program that creates a REPL (Read, Evaluate, Print, Loop) environment.

Include <stdio.h>, <stdlib.h>, and <string.h>.
Inside int main(), create an infinite loop using: while(1) { ... }
Inside the loop, print your custom shell prompt first:
printf("prateek@customshell> ");
(Note: Do not add \n here, so the user types their command on the exact same line).
Declare a character array char command[100]; and read the user's input from the keyboard using:
fgets(command, 100, stdin);
Remove the hidden 'Enter' key (\n) from the input string so it can be compared correctly:
command[strlen(command) - 1] = '\0';
Evaluate the command. Check if the user wants to quit the shell:
if (strcmp(command, "exit") == 0) {
printf("Shell shutting down...\n");
break;
}
If the command is not 'exit', simply print what the user typed (we will add real OS execution later):
printf("Command received: %s\n", command);



#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int main() {
    while(1) {
        printf("prateek@customshell> ");
        char command[100];
        fgets(command, 100, stdin);
        command[strlen(command)-1] = '\0';
        if (strcmp(command, "exit") == 0) {
            printf("Shell shutting down...\n");
            break;
        }
        else {
            printf("Command received: %s\n", command);
        }
    }
    return 0;
} */




/*Task: Implement Process Cloning to Execute Commands

Update your existing shell code to execute single-word commands (like ls, pwd, or date) using system calls.

Requirements:

Include <unistd.h> (for system calls) and <sys/wait.h> (for process waiting).
Inside your while(1) loop, after getting the user input and removing the \n character (and making sure it's not "exit"), create a new process using fork().
Child Process Duty:
Prepare the argument array required by execvp. (Hint: It needs an array of strings where the first element is the command, and the last element MUST be NULL).
Call execvp to replace the child process with the entered command.
If execvp fails (for example, if the user types a wrong command), print a "Command not found" error and forcibly exit the child process so it doesn't continue the loop.
Parent Process Duty:
The parent (your main shell) must wait for the child process to complete its execution before showing the next prompt.*/

/*
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    while(1) {
        printf("prateek@customshell> ");
        char command[100];
        fgets(command, 100, stdin);
        command[strlen(command)-1] = '\0';
        if (strcmp(command, "exit") == 0) {
            break;
        }
        else {
            int pid = fork();
            if (pid == 0) {
                char *args[] = {command, NULL};
                execvp(command, args);
                printf("Command not found: %s\n", command);
                exit(1);
            }
            else {
                wait(NULL);
            }
        }
    }
    return 0;
}
*/



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