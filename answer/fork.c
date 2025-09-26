#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(void) {
    pid_t pid = fork();
    if (pid < 0) {
        fprintf(stderr, "Fork Failed\n");
        return 1;
    } else if (pid == 0) {
        /* child: run "ls -lt" */
        execlp("ls", "ls", "-lt", (char *)NULL);
        /* if execlp returns, it failed */
        perror("execlp failed");
        exit(1);
    } else {
        /* parent: wait for child to finish */
        waitpid(pid, NULL, 0);
        printf("Child process is done\n");
    }
    return 0;
}
