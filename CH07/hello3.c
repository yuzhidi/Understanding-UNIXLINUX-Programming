/* hello3.c
 *	purpose	 using refresh and sleep for animated effects
 *	outline	 initialize, draw stuff, wrap up
 */
#include	<stdio.h>
#include	<curses.h>

main()
{
	int	i;

	initscr();
	   clear();
	   for(i=0; i<LINES; i++ ){
		move( i, i+i );
		if ( i%2 == 1 ) 
			standout();
		addstr("Hello, world");
		if ( i%2 == 1 ) 
			standend();
		sleep(1);
		refresh();
	   }
	endwin();
}
