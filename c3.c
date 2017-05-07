#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFSIZE 256

/*
This program repeatedly reads its stdin and writes this to stdout
with a line number prepended (i.e. added to the beginning)
*/

int main(int ac,char**av)
{

	char buffer[BUFSIZE], temp[BUFSIZE];
	int i = 0;
    while(fgets(buffer, BUFSIZE , stdin) != NULL)
    {
    	sprintf(temp, "%d %s", ++i, buffer);
        fprintf(stdout, "%s", temp);
    }

}
