/* shm_ts.c : the time server using shared memory, a bizarre application  */

#include	<stdio.h>
#include	<sys/shm.h>
#include	<time.h>

#define	TIME_MEM_KEY	99			/* like a filename      */
#define	SEG_SIZE	((size_t)100)		/* size of segment	*/
#define oops(m,x)  { perror(m); exit(x); }

main()
{
	int	seg_id;
	char	*mem_ptr, *ctime();
	long	now;
	int	n;

	/* create a shared memory segment */

	seg_id = shmget( TIME_MEM_KEY, SEG_SIZE, IPC_CREAT|0777 );
	if ( seg_id == -1 )
		oops("shmget", 1);

	/* attach to it and get a pointer to where it attaches */

	mem_ptr = shmat( seg_id, NULL, 0 );
	if ( mem_ptr == ( void *) -1 )
		oops("shmat", 2);

	/* run for a minute */
	for(n=0; n<60; n++ ){
		time( &now );			/* get the time	*/
		strcpy(mem_ptr, ctime(&now));	/* write to mem */
		sleep(1);			/* wait a sec   */
	}
		
	/* now remove it */
	shmctl( seg_id, IPC_RMID, NULL );
}
