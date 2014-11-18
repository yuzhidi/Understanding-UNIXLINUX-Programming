/****************************************************************************
 * lclnt2.c
 * License server client version 2
 *  link with lclnt_funcs2.o dgram.o
 */

#include <stdio.h>

int main(int ac, char *av[])
{
	setup();
	if (get_ticket() != 0 )
		exit(0);	

	do_regular_work();

	release_ticket();
	shut_down();

}
/****************************************************************************
 * do_regular_work  the main work of the application goes here
 */
do_regular_work()
{
	printf("SuperSleep version 1.0 Running - Licensed Software\n");
	sleep(15);	/* our patented sleep algorithm */

	if ( validate_ticket() != 0 ){
		printf("Server errors. Please Try later.\n");
		return;
	}
	sleep(15);
}

