#include <stdio.h>
#include <signal.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

#define MAXARGS 20
#define ARGLEN 100

int execute( char *arglist[] );

int main() {
    char *arglist[MAXARGS+1];
    int numargs;
    char argbuf[ARGLEN];
    char *makestring();

    numargs = 0;
    while ( numargs < MAXARGS ) {
        printf("Arg[%d]? ", numargs);
        if ( fgets(argbuf, ARGLEN, stdin) && *argbuf != '\n' ) {
            arglist[numargs++] = makestring(argbuf);
        } else {
            if ( numargs > 0 ) {
                arglist[numargs] = NULL;
                execute(arglist); /* NOTE: execvp will replace this process on success */
                /* if execvp fails, we return here and continue */
                numargs = 0;
            }
        }
    }
    return 0;
}

/* use execvp to run command */
int execute( char *arglist[] ) {
    execvp(arglist[0], arglist);
    perror("execvp failed");
    return -1;
}

/* trim newline and create storage for the string */
char * makestring( char *buf ) {
    char *cp;
    buf[strlen(buf)-1] = '\0';
    cp = malloc(sizeof(char) * (strlen(buf) + 1));
    if (cp == NULL) {
        fprintf(stderr, "no memory\n");
        exit(1);
    }
    strcpy(cp, buf);
    return cp;
}
