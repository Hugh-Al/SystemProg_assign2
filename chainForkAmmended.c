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

void fork_and_chain(int* lpipe, int* rpipe)
{
    if(!fork())
    {
        if(lpipe) // there's a pipe from the previous process
            set_read(lpipe);
        // else you may want to redirect input from somewhere else for the start
        if(rpipe) // there's a pipe to the next process
            set_write(rpipe);
        // else you may want to redirect out to somewhere else for the end

        // blah do your stuff
        // and make sure the child process terminates in here
        // so it won't continue running the chaining code
    }
}


int main(){

	// two pipes: one from the previous in the chain, one to the next in the chain
	int lpipe[2], rpipe[2];

	// create the first output pipe
	pipe(rpipe);

	// first child takes input from somewhere else
	fork_and_chain(NULL, rpipe);

	// output pipe becomes input for the next process.
	lpipe[0] = rpipe[0];
	lpipe[1] = rpipe[1];

	// chain all but the first and last children
	for(i = 1; i < N - 1; i++)
	{
	    pipe(rpipe); // make the next output pipe
	    fork_and_chain(lpipe, rpipe);
	    close(lpipe[0]); // both ends are attached, close them on parent
	    close(lpipe[1]);
	    lpipe[0] = rpipe[0]; // output pipe becomes input pipe
	    lpipe[1] = rpipe[1];
	}

	// fork the last one, its output goes somewhere else      
	fork_and_chain(lpipe, NULL);
	close(lpipe[0]);
	close(lpipe[1]);

}