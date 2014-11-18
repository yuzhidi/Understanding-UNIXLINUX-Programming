/* shm_tc.c : the time client using shared memory, a bizarre application  */

#include	<stdio.h>
#include	<sys/shm.h>
#include	<time.h>

#define	TIME_MEM_KEY	99		/* kind of like a port number */
#define	SEG_SIZE	((size_t)100)		/* size of segment	*/
#define oops(m,x)  { perror(m); exit(x); }

main()
{
	int	seg_id;
	char	*mem_ptr, *ctime();
	long	now;

	/* create a shared memory segment */

	seg_id = shmget( TIME_MEM_KEY, SEG_SIZE, 0777 );
	if ( seg_id == -1 )
		oops("shmget",1);

	/* attach to it and get a pointer to where it attaches */

	mem_ptr = shmat( seg_id, NULL, 0 );
	if ( mem_ptr == ( void *) -1 )
		oops("shmat",2);

	printf("The time, direct from memory: ..%s", mem_ptr);

	shmdt( mem_ptr );		/* detach, but not needed here */
}
