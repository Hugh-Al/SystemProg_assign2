#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

void set_read(int* lpipe)
{
    dup2(lpipe[0], STDIN_FILENO);
    close(lpipe[0]); // we have a copy already, so close it
    close(lpipe[1]); // not using this end
}
  
void set_write(int* rpipe)
{
    dup2(rpipe[1], STDOUT_FILENO);
    close(rpipe[0]); // not using this end
    close(rpipe[1]); // we have a copy already, so close it
}

void fork_and_chain(int* lpipe, int* rpipe, char* cmd)
{
	int pid;
	
	switch (pid = fork()){	
	case 0: /* child */
		if(lpipe) // there's a pipe from the previous process
            		set_read(lpipe);
		if(rpipe) // there's a pipe to the next process
			set_write(rpipe);
		execlp( "./c1", NULL );

	default: /* parent does nothing */
		break;

	case -1:
		perror("fork");
		exit(1);
	

	}
}


int main(){

	// two pipes: one from the previous in the chain, one to the next in the chain
	int lpipe[2], rpipe[2];

	// create the first output pipe
	pipe(rpipe);

	// first child takes input from somewhere else
	fork_and_chain(NULL, rpipe, "./c1");

	// output pipe becomes input for the next process.
	lpipe[0] = rpipe[0];
	lpipe[1] = rpipe[1];


	    pipe(rpipe); // make the next output pipe
	    fork_and_chain(lpipe, rpipe, "./c2");
	    close(lpipe[0]); // both ends are attached, close them on parent
	    close(lpipe[1]);
	    lpipe[0] = rpipe[0]; // output pipe becomes input pipe
	    lpipe[1] = rpipe[1];

	// fork the last one, its output goes somewhere else      
	fork_and_chain(lpipe, NULL, "./c3");
	close(lpipe[0]);
	close(lpipe[1]);
	wait(NULL);

}
