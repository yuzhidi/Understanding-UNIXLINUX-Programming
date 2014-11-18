/* who3.c - who with buffered reads
 *	  - surpresses empty records
 *	  - formats time nicely
 *	  - buffers input (using utmplib)
 */
#include	<stdio.h>
#include	<sys/types.h>
#include	<utmp.h>
#include	<fcntl.h>
#include	<time.h>

#define	SHOWHOST

void show_info(struct utmp *);
void showtime(time_t);

int main()
{
	struct utmp	*utbufp,	/* holds pointer to next rec	*/
			*utmp_next();	/* returns pointer to next	*/

	if ( utmp_open( UTMP_FILE ) == -1 ){
		perror(UTMP_FILE);
		exit(1);
	}
	while ( ( utbufp = utmp_next() ) != ((struct utmp *) NULL) )
		show_info( utbufp );
	utmp_close( );
	return 0;
}
/*
 *	show info()
 ...
