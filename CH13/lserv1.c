/****************************************************************************
 * lsrv1.c  
 * License server server program version 1
 */

#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <signal.h>
#include <sys/errno.h>
#define MSGLEN		128		/* Size of our datagrams */

int main(int ac, char *av[])
{
	struct sockaddr_in client_addr;
	socklen_t addrlen;
	char      buf[MSGLEN];
	int	  ret;
	int       sock;

	sock = setup();

	while(1) {
		addrlen = sizeof(client_addr);
		ret = recvfrom(sock,buf,MSGLEN,0,
				(struct sockaddr*)&client_addr,&addrlen);
		if ( ret != -1 ){
			buf[ret] = '\0';
			narrate("GOT:", buf, &client_addr);
			handle_request(buf,&client_addr,addrlen);
		}
		else if ( errno != EINTR )
			perror("recvfrom");
	}
}

