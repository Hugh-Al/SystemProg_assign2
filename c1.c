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
	//fprintf(stdout, "Please enter the next line of input:\n");
	 char str[100];
	 int i;
	 for(i = 0; i < 5; i++){
	 	printf( "Enter a value :");
   gets( str );

   printf( "\nYou entered: ");
   puts( str );
	 }

   

   return 0;

}


