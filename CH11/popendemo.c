/* popendemo.c
 *	demonstrates how to open a program for standard i/o
 *	important points:
 *		1. popen() returns a FILE *, just like fopen()
 *		2. the FILE * it returns can be read/written
 *		   with all the standard functions
 *		3. you need to use pclose() when done
 */
#include	<stdio.h>
#include	<stdlib.h>

int main()
{
	FILE	*fp;
	char	buf[100];
	int	i = 0;

	fp = popen( "who|sort", "r" );		/* open the command  */

	while ( fgets( buf, 100, fp ) != NULL )	/* read from command */
		printf("%3d %s", i++, buf );    /* print data        */

	pclose( fp );     			/* IMPORTANT!	     */
	return 0;
}
