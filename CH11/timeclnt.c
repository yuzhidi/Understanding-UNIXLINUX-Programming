/* timeclnt.c - a client for timeserv.c
 *              usage: timeclnt hostname portnumber
 */
#include       <stdio.h>
#include       <sys/types.h>
#include       <sys/socket.h>
#include       <netinet/in.h>
#include       <netdb.h>

#define        oops(msg)       { perror(msg); exit(1); }

main(int ac, char *av[])
{
	struct sockaddr_in  servadd;        /* the number to call */
	struct hostent      *hp;            /* used to get number */
	int    sock_id, sock_fd;            /* the socket and fd  */
	char   message[BUFSIZ];             /* to receive message */
	int    messlen;                     /* for message length */

     /*
      * Step 1: Get a socket
      */

	sock_id = socket( AF_INET, SOCK_STREAM, 0 );    /* get a line   */
	if ( sock_id == -1 ) 
		oops( "socket" );          		/* or fail      */

     /*
      * Step 2: connect to server
      *         need to build address (host,port) of server  first
      */

	bzero( &servadd, sizeof( servadd ) );   /* zero the address     */

	hp = gethostbyname( av[1] );            /* lookup host's ip #   */
	if (hp == NULL) 
		oops(av[1]);            	/* or die               */
	bcopy(hp->h_addr, (struct sockaddr *)&servadd.sin_addr, hp->h_length);

	servadd.sin_port = htons(atoi(av[2]));  /* fill in port number  */

	servadd.sin_family = AF_INET ;          /* fill in socket type  */

						       /* now dial     */
	if ( connect(sock_id,(struct sockaddr *)&servadd, sizeof(servadd)) !=0)
	       oops( "connect" );

     /*
      * Step 3: transfer data from server, then hangup
      */

	messlen = read(sock_id, message, BUFSIZ);     /* read stuff   */
	if ( messlen == - 1 )
	       oops("read") ;
	if ( write( 1, message, messlen ) != messlen )  /* and write to */
	       oops( "write" );                        /* stdout       */
	close( sock_id );    
}
