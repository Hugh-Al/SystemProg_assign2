#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFSIZE 256

/*
This program reapeatly reads its stdin, converts the upper case of
the input to lower case, and writes this to stdout.
*/

int main(int ac,char**av)
{

	char buffer[BUFSIZE];
	int i;
    while(fgets(buffer, BUFSIZE , stdin) != NULL)
    {
    	for(i = 0; buffer[i]; i++){
  			buffer[i] = tolower(buffer[i]);
		}
        fprintf(stdout, "%s", buffer);
    }

    return 0;

}
