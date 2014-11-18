/* bounce1d.c
 *	purpose	animation with user controlled speed and direction
 *	note	the handler does the animation
 *		the main program reads keyboard input
 *	compile	cc bounce1d.c set_ticker.c -lcurses -o bounce1d
 */
#include	<stdio.h>
#include	<curses.h>
#include	<signal.h>

/* some global settings main and the handler use */

#define	MESSAGE	"hello"
#define BLANK   "     "

int	row;	/* current row		*/
int	col;	/* current column	*/
int	dir;	/* where we are going	*/

int main()
{
	int	delay;		/* bigger => slower	*/
	int	ndelay;		/* new delay		*/
	int	c;		/* user input		*/
	void	move_msg(int);	/* handler for timer	*/

	initscr();
	crmode();
	noecho();
	clear();

	row   = 10;		/* start here		*/
	col   = 0;
	dir   = 1;		/* add 1 to row number	*/
	delay = 200;		/* 200ms = 0.2 seconds  */

	move(row,col);		/* get into position	*/
	addstr(MESSAGE);	/* draw message		*/
	signal(SIGALRM, move_msg );
	set_ticker( delay );

	while(1)
	{
		ndelay = 0;
		c = getch();
		if ( c == 'Q' ) break;
		if ( c == ' ' ) dir = -dir;
		if ( c == 'f' && delay > 2 ) ndelay = delay/2;
		if ( c == 's' ) ndelay = delay * 2 ;
		if ( ndelay > 0 )
			set_ticker( delay = ndelay );
	}
	endwin();
	return 0;
}

void move_msg(int signum)
{
	signal(SIGALRM, move_msg);	/* reset, just in case	*/
	move( row, col );
	addstr( BLANK );
	col += dir;			/* move to new column	*/
	move( row, col );		/* then set cursor	*/
	addstr( MESSAGE );		/* redo message		*/
	refresh();			/* and show it		*/

	/*
	 * now handle borders
	 */
	if ( dir == -1 && col <= 0 )
		dir = 1;
	else if ( dir == 1 && col+strlen(MESSAGE) >= COLS )
		dir = -1;
}
