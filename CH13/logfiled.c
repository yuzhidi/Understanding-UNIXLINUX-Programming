/*************************************************************************
 * logfiled.c  - a simple logfile server using Unix Domain Datagram Sockets
 * 	         usage: logfiled >>logfilename
 */

#include	<stdio.h>
#include	<sys/types.h>
#include	<sys/socket.h>
#include	<sys/un.h>
#include	<time.h>

#define	MSGLEN	512
#define oops(m,x) { perror(m); exit(x); }
#define	SOCKNAME "/tmp/logfilesock"

int main(int ac, char *av[])
{
	int	sock;			/* read messages here	*/
	struct sockaddr_un addr;	/* this is its address	*/
	socklen_t addrlen;
	char	msg[MSGLEN];
	int	l;
	char	sockname[] = SOCKNAME ;
	time_t	now;
	int	msgnum = 0;
	char	*timestr;

	/* build an address */
	addr.sun_family = AF_UNIX;		/* note AF_UNIX */
	strcpy(addr.sun_path, sockname);	/* filename is address */
	addrlen = strlen(sockname) + sizeof(addr.sun_family);

	sock = socket(PF_UNIX, SOCK_DGRAM, 0);	/* note PF_UNIX  */
	if ( sock == -1 )
		oops("socket",2);

	/* bind the address */
	if ( bind(sock, (struct sockaddr *) &addr, addrlen) == -1 )
		oops("bind", 3);

	/* read and write */
	while(1)
	{
		l = read(sock, msg, MSGLEN);	/* read works for DGRAM	*/
		msg[l] = '\0';			/* make it a string 	*/
		time(&now);
		timestr = ctime(&now);
		timestr[strlen(timestr)-1] = '\0';	/* chop newline */

		printf("[%5d] %s %s\n", msgnum++, timestr, msg);
		fflush(stdout);
	}
}

