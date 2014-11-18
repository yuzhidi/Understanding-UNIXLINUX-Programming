/*  forkdemo3.c - shows how the return value from fork()
 *                allows a process to determine whether
 *                it is a child or process
 */

#include	<stdio.h>

main()
{
	int	fork_rv;

	printf("Before: my pid is %d\n", getpid());

	fork_rv = fork();		/* create new process	*/

	if ( fork_rv == -1 )		/* check for error	*/
		perror("fork");

	else if ( fork_rv == 0 )
		printf("I am the child.  my pid=%d\n", getpid());
	else
		printf("I am the parent. my child is %d\n", fork_rv);
}
