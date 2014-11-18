/* file_ts.c - read the current date/time from a file 
 *     usage: file_ts filename
 *    action: writes the current time/date to filename
 *     note: uses fcntl()-based locking
 */

#include <stdio.h>
#include <sys/file.h>
#include <fcntl.h>
#include <time.h>

#define  oops(m,x)  { perror(m); exit(x); }

main(int ac, char *av[])
{
	int	fd;
	time_t  now;
	char    *message;

	if ( ac != 2 ){
		fprintf(stderr,"usage: file_ts filename\n");
		exit(1);
	}
	if ( (fd = open(av[1],O_CREAT|O_TRUNC|O_WRONLY,0644)) == -1 )
		oops(av[1],2);

	while(1)
	{
		time(&now);
		message = ctime(&now);		/* compute time	     */

		lock_operation(fd, F_WRLCK);	/* lock for writing  */

		if ( lseek(fd, 0L, SEEK_SET) == -1 )
			oops("lseek",3);
		if ( write(fd, message, strlen(message)) == -1 )
			oops("write", 4);

		lock_operation(fd, F_UNLCK);	/* unlock file	     */
		sleep(1);			/* wait for new time */
	}
}

lock_operation(int fd, int op)
{
	struct flock lock;

	lock.l_whence = SEEK_SET;
	lock.l_start = lock.l_len = 0;
	lock.l_pid = getpid();
	lock.l_type = op;

	if ( fcntl(fd, F_SETLKW, &lock) == -1 )
		oops("lock operation", 6);
}
