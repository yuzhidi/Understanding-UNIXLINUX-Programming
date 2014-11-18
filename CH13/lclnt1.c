/****************************************************************************
 * lclnt1.c
 * License server client version 1
 *  link with lclnt_funcs1.o dgram.o
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
	sleep(10);	/* our patented sleep algorithm */
}

