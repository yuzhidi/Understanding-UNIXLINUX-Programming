/* sigdemo2.c - shows how to ignore a signal
 *            - press Ctrl-\ to kill this one
 */

#include	<stdio.h>
#include	<signal.h>

main()
{
	signal( SIGINT, SIG_IGN );

	printf("you can't stop me!\n");
	while( 1 )
	{
		sleep(1);
		printf("haha\n");
	}
}

