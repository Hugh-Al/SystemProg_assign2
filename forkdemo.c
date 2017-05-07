#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main( void )
{
	int c1id, c2id, c3id;
    printf( "[dad] pid %d\n", getpid() );

    for ( int i = 0; i < 3; i++ )
        if ( fork() == 0 )
        {
            printf( "[son] pid %d from pid %d\n", getpid(), getppid() );
            exit( 0 );
        }

    for ( int i = 0; i < 3; i++ ){
        wait( NULL );
    }
}