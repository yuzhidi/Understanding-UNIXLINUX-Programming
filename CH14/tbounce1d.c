/* tbounce1d.c: controlled animation using two threads 
 *	note	one thread handles animation
 *		other thread handles keyboard input
 *	compile	cc tbounce1d.c -lcurses -lpthread -o tbounce1d
 */

#include	<stdio.h>
#include	<curses.h>
#include	<pthread.h>
#include	<stdlib.h>
#include	<unistd.h>

/* shared variables both threads use. These need a mutex. */

#define	MESSAGE	" hello "

int	row;	/* current row		*/
int	col;	/* current column	*/
int	dir;	/* where we are going	*/
int	delay;	/* delay between moves	*/

main()
{
	int	ndelay;		/* new delay		*/
	int	c;		/* user input		*/
	pthread_t msg_thread;	/* a thread		*/
	void	*moving_msg();

	initscr();		/* init curses and tty	*/
	crmode();
	noecho();
	clear();

	row   = 10;		/* start here		*/
	col   = 0;
	dir   = 1;		/* add 1 to row number	*/
	delay = 200;		/* 200ms = 0.2 seconds  */

	if ( pthread_create(&msg_thread,NULL,moving_msg,MESSAGE) ){
		fprintf(stderr,"error creating thread");
		endwin();
		exit(0);
	}

	while(1) {
		ndelay = 0;
		c = getch();
		if ( c == 'Q' ) break;
		if ( c == ' ' ) dir = -dir;
		if ( c == 'f' && delay > 2 ) ndelay = delay/2;
		if ( c == 's' ) ndelay = delay * 2 ;
		if ( ndelay > 0 )
			delay = ndelay ;
	}
	pthread_cancel(msg_thread);
	endwin();
}

void *moving_msg(char *msg)
{
	while( 1 ) {
		usleep(delay*1000);	/* sleep a while 	*/
		move( row, col );	/* set cursor position	*/
		addstr( msg );		/* redo message		*/
		refresh();		/* and show it		*/

		/* move to next column and check for bouncing	*/

		col += dir;		/* move to new column	*/

		if ( col <= 0 && dir == -1 )
			dir = 1;
		else if (  col+strlen(msg) >= COLS && dir == 1 )
			dir = -1;

	}
}
