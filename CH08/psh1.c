/*	prompting shell version 1
 *		Prompts for the command and its arguments.
 *		Builds the argument vector for the call to execvp.
 *		Uses execvp(), and never returns.
 */

#include	<stdio.h>
#include	<signal.h>
#include	<string.h>

#define	MAXARGS		20				/* cmdline args	*/
#define	ARGLEN		100				/* token length	*/

int main()
{
	char	*arglist[MAXARGS+1];		/* an array of ptrs	*/
	int	numargs;			/* index into array	*/
	char	argbuf[ARGLEN];			/* read stuff here	*/
	char	*makestring();			/* malloc etc		*/

	numargs = 0;
	while ( numargs < MAXARGS )
	{					
		printf("Arg[%d]? ", numargs);
		if ( fgets(argbuf, ARGLEN, stdin) && *argbuf != '\n' )
			arglist[numargs++] = makestring(argbuf);
		else
		{
			if ( numargs > 0 ){		/* any args?	*/
				arglist[numargs]=NULL;	/* close list	*/
				execute( arglist );	/* do it	*/
				numargs = 0;		/* and reset	*/
			}
		}
	}
	return 0;
}

int execute( char *arglist[] )
/*
 *	use execvp to do it
 */
{
	execvp(arglist[0], arglist);		/* do it */
	perror("execvp failed");
	exit(1);
}

char * makestring( char *buf )
/*
 * trim off newline and create storage for the string
 */
{
	char	*cp, *malloc();

	buf[strlen(buf)-1] = '\0';		/* trim newline	*/
	cp = malloc( strlen(buf)+1 );		/* get memory	*/
	if ( cp == NULL ){			/* or die	*/
		fprintf(stderr,"no memory\n");
		exit(1);
	}
	strcpy(cp, buf);		/* copy chars	*/
	return cp;			/* return ptr	*/
}
