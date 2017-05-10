#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>

//#define oops(m,x) {perror(m); exit(x);}
void oops(char *s1, char *s2)
/*
 *Output the error message and exit
 */

{
    fprintf(stderr,"Error: %s ", s1);
    perror(s2);
    exit(1);
}


main()
{
    int pipe1[2];
    int pipe2[2];
    int pid, status;
    int child1, child2, child3;

    if (pipe(pipe1) == -1){
        oops("Could not create right output pipe", pipe);
    }

    if ((child1 = fork()) == -1){
	oops("Could not create fork for first child", fork);
    }
    if (child1 == 0){       
        if ((dup2(pipe1[1], 1) == -1)){
            oops("Could not duplicate pipe", dup);	
	}
	if ((close(pipe1[1]) == -1) || (close(pipe1[0]) == -1)){
	    oops("Could not close pipe", pipe);	
	}
        execl( "./c1", "./c1", NULL );
    }
    pid = wait(&status);
    fprintf(stderr, "process %d exits with %d\n", pid, WEXITSTATUS(status));
    if (pipe(pipe2) == -1){
	oops("Could not create left input pipe", pipe);
    }

    if ((child2 = fork()) == -1){
	oops("Could not create fork for second child", fork);
    }
    if (child2 == 0){
        dup2(pipe1[0], 0);
        close(pipe1[0]);
        close(pipe1[1]);
        dup2(pipe2[1], 1);
        close(pipe2[1]);
        close(pipe2[0]);
        execl( "./c2", "./c2", NULL );
    }
    close(pipe1[1]);
    close(pipe1[0]);
    pid = wait(&status);
    fprintf(stderr, "process %d exits with %d\n", pid, WEXITSTATUS(status));

    if ((child3 = fork()) == -1){
	oops("Could not create fork for third child", fork);
    }
    if (child3 == 0){
        dup2(pipe2[0], 0);
        close(pipe2[0]);
        close(pipe2[1]);
        execl( "./c3", "./c3", NULL );
    }

    close(pipe2[1]);
    close(pipe2[0]);
    pid = wait(&status);
    fprintf(stderr, "process %d exits with %d\n", pid, WEXITSTATUS(status));
}
