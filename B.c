Q.2) Write a C program which creates a child process to run linux/unix command or any user defined program. The parent process sets the signal handler for death of child signal and Alarm signal. If a child process does not complete its execution in 5 seconds then parent process kills child process.

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>
#include <time.h>

pid_t child_pid;

void child_exit_handler(int sig) {
    printf("Child process terminated.\n");
    exit(0);
}

void alarm_handler(int sig) {
    printf("Child process did not complete in time. Killing child...\n");
    kill(child_pid, SIGKILL);
}

int main() {
    signal(SIGCHLD, child_exit_handler);
    signal(SIGALRM, alarm_handler);

    child_pid = fork();

    if (child_pid == 0) {
        // Child process runs the 'sleep' command for 10 seconds
        execlp("sleep", "sleep", "10", NULL);
        perror("execlp failed");
    } else if (child_pid > 0) {
        // Parent process sets an alarm for 5 seconds
        alarm(5);
        wait(NULL);  // Wait for the child to finish or be killed
    } else {
        perror("fork failed");
    }

    return 0;
}

(If the child process does not finish within 5 seconds)
Child process did not complete in time. Killing child...

(If the child finishes within 5 seconds)
Child process terminated.
