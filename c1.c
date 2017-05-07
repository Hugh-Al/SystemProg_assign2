#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFSIZE 256

/*
This program repeatedly prompts the user for input,
reads this input in and writes it to stdout. You may send your
prompts to stderr.
*/

int main(int ac,char**av)
{
	
	char str[100];
	int i;
	for(i = 0; i < 3; i++){
	fprintf(stderr, "Please enter the next line of input:\n");
	   fgets(str, 100, stdin);
	   //puts( str );
	   fprintf(stdout, "%s", str);
	}

   

   return 0;

}


