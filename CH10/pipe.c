/* pipe.c		
 *	* Demonstrates how to create a pipeline from one process to another
 *	* Takes two args, each a command, and connects
 *	  av[1]'s output to input of av[2]
 *	* usage: pipe command1 command2
 *	  effect: command1 | command2
 *	* Limitations: commands do not take arguments
 *	* uses execlp() since known number of args
 *	* Note: exchange child and parent and watch fun
 */
#include	<stdio.h>
#include	<unistd.h>

#define	oops(m,x)	{ perror(m); exit(x); }

main(int ac, char **av)
{
	int	thepipe[2],			/* two file descriptors	*/
		newfd,				/* useful for pipes	*/
		pid;				/* and the pid		*/

	if ( ac != 3 ){
		fprintf(stderr, "usage: pipe cmd1 cmd2\n");
		exit(1);
	}
	if ( pipe( thepipe ) == -1 )		/* get a pipe		*/
		oops("Cannot get a pipe", 1);

	/* ------------------------------------------------------------ */
	/*	now we have a pipe, now let's get two processes		*/

	if ( (pid = fork()) == -1 )			/* get a proc	*/
		oops("Cannot fork", 2);

	/* ------------------------------------------------------------ */
	/* 	Right Here, there are two processes			*/
	/*             parent will read from pipe			*/

	if ( pid > 0 ){			/* parent will exec av[2]	*/
		close(thepipe[1]);	/* parent doesn't write to pipe	*/

		if ( dup2(thepipe[0], 0) == -1 )
			oops("could not redirect stdin",3);

		close(thepipe[0]);	/* stdin is duped, close pipe	*/
		execlp( av[2], av[2], NULL);
		oops(av[2], 4);
	}

	/*	 child execs av[1] and writes into pipe			*/

	close(thepipe[0]);		/* child doesn't read from pipe	*/

	if ( dup2(thepipe[1], 1) == -1 )
		oops("could not redirect stdout", 4);

	close(thepipe[1]);		/* stdout is duped, close pipe	*/
	execlp( av[1], av[1], NULL);
	oops(av[1], 5);
}
