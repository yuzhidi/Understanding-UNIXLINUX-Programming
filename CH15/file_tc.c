/* file_tc.c - read the current date/time from a file 
 *     usage: file_tc filename 
 *      uses: fcntl()-based locking 
 */

#include <stdio.h>
#include <sys/file.h>
#include <fcntl.h>

#define  oops(m,x)  { perror(m); exit(x); }
#define  BUFLEN 10

main(int ac, char *av[])
{
	int	fd, nread;
	char	buf[BUFLEN];

	if ( ac != 2 ){
		fprintf(stderr,"usage: file_tc filename\n");
		exit(1);
	}

	if ( (fd= open(av[1],O_RDONLY)) == -1 )
		oops(av[1],3);

	lock_operation(fd, F_RDLCK);

	  while( (nread = read(fd, buf, BUFLEN)) > 0 )
		write(1, buf, nread );

	lock_operation(fd, F_UNLCK);

	close(fd);
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
