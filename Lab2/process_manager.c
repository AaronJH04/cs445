#include <unistd.h>
#include <wait.h>
#include <stdio.h>
#include <stdlib.h>

int main() {
    pid_t pids[10];
    char *commands[10][4] = {
        {"echo", "Hello + Aaron", NULL},
        {"ls", "-l", NULL},
        {"date", NULL},
        {"whoami", NULL},
        {"uname", "-a", NULL},
        {"pwd", NULL},
        {"uptime", NULL},
        {"hostname", NULL},
        {"id", NULL},
        {"cal", NULL}
    };

    for (int i = 0; i < 10; i++) {
        pid_t pid = fork();
        if (pid < 0) {
            perror("fork failed");
            exit(EXIT_FAILURE);
        } else if (pid == 0) {
            printf("Child PID: %d, Command: %s\n", getpid(), commands[i][0]);
            execvp(commands[i][0], commands[i]);
            perror("exec failed");
            exit(EXIT_FAILURE);
        } else {
            pids[i] = pid;
        }
    }

    for (int i = 0; i < 10; i++) {
        int status;
        pid_t wpid = waitpid(pids[i], &status, 0);
        if (wpid == -1) {
            perror("waitpid failed");
            continue;
        }
        if (WIFEXITED(status)) {
            printf("Child PID %d exited with status %d\n", wpid, WEXITSTATUS(status));
        } else if (WIFSIGNALED(status)) {
            printf("Child PID %d was terminated by signal %d\n", wpid, WTERMSIG(status));
        } else {
            printf("Child PID %d ended abnormally\n", wpid);
        }
    }

    return 0;
}
