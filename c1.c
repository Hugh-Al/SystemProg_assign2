#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <signal.h>

#define BUFSIZE 256

/*
This program repeatedly prompts the user for input,
reads this input in and writes it to stdout. You may send your
prompts to stderr.
*/

int main(int ac,char**av)
{
	char str[100];
	do{
	   fprintf(stderr, "Please enter the next line of input:\n");
	   fgets(str, 100, stdin);
	   str[strcspn(str, "\n")] = '\0';
	   if (strcmp(str, "QUIT") != 0){
		fprintf(stdout, "%s\n", str);
	   }
	}while(strcmp(str, "QUIT") != 0);

   return 0;

}


