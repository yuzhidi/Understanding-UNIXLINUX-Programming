/***************************************************************************
 * lclnt_funcs1.c: functions for the client of the license server
 */

#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>

/*
 * Important variables used throughout
 */
static int pid = -1;			/* Our PID */
static int sd = -1;			/* Our communications socket */
static struct sockaddr serv_addr;	/* Server address */	
static socklen_t serv_alen;		/* length of address */
static char ticket_buf[128];		/* Buffer to hold our ticket */
static have_ticket = 0;			/* Set when we have a ticket */

#define MSGLEN		128		/* Size of our datagrams */
#define SERVER_PORTNUM	2020		/* Our server's port number */
#define	HOSTLEN		512
#define oops(p) { perror(p); exit(1) ; }

char *do_transaction();

/*
 * setup:  get pid, socket, and address of license server
 * IN      no args
 * RET     nothing, dies on error
 * notes:  assumes server is on same host as client
 */
setup()
{
	char	hostname[BUFSIZ];

	pid = getpid();				/* for ticks and msgs	*/
	sd  = make_dgram_client_socket();	/* to talk to server	*/
	if ( sd == -1 ) 
		oops("Cannot create socket");
	gethostname(hostname, HOSTLEN);         /* server on same host	*/
	make_internet_address(hostname, SERVER_PORTNUM, &serv_addr);
	serv_alen = sizeof(serv_addr);
}

shut_down()
{
	close(sd);
}
/****************************************************************************
 * get_ticket
 * get a ticket from the license server
 * Results: 0 for success, -1 for failure
 */
int get_ticket()
{
	char *response;
	char buf[MSGLEN];

	if(have_ticket)				/* don't be greedy 	*/
		return(0);

	sprintf(buf, "HELO %d", pid);		/* compose request	*/

	if ( (response = do_transaction(buf)) == NULL )
		return(-1);

	/* parse the response and see if we got a ticket.  
	 *   on success, the message is: TICK ticket-string
	 *   on failure, the message is: FAIL failure-msg
	 */
	if ( strncmp(response, "TICK", 4) == 0 ){
		strcpy(ticket_buf, response + 5);	/* grab ticket-id */
		have_ticket = 1;			/* set this flag  */
		narrate("got ticket", ticket_buf);
		return(0);
	}

	if ( strncmp(response,"FAIL",4) == 0)
		narrate("Could not get ticket",response);
	else
		narrate("Unknown message:", response);

	return(-1);
} /* get_ticket */
  
/****************************************************************************
 * release_ticket
 * Give a ticket back to the server
 * Results: 0 for success, -1 for failure
 */
int release_ticket()
{
	char buf[MSGLEN];
	char *response;

	if(!have_ticket)			/* don't have a ticket	*/
		return(0);			/* nothing to release	*/

	sprintf(buf, "GBYE %s", ticket_buf);	/* compose message	*/
	if ( (response = do_transaction(buf)) == NULL )
		return(-1);

	/* examine response
	 * success: THNX info-string
	 * failure: FAIL error-string
	 */
	if ( strncmp(response, "THNX", 4) == 0 ){
		narrate("released ticket OK","");
		return 0;
	}
	if ( strncmp(response, "FAIL", 4) == 0)
		narrate("release failed", response+5);
	else
		narrate("Unknown message:", response);
	return(-1);
} /* release_ticket */

/****************************************************************************
 * do_transaction
 * Send a request to the server and get a response back
 * IN  msg_p		message to send
 * Results: pointer to message string, or NULL for error
 *			NOTE: pointer returned is to static storage 
 *			overwritten by each successive call.
 * note: for extra security, compare retaddr to serv_addr (why?)
 */
char *do_transaction(char *msg)
{
	static char buf[MSGLEN];
	struct sockaddr retaddr;
	socklen_t       addrlen;
	int ret;
	
	ret = sendto(sd, msg, strlen(msg), 0, &serv_addr, serv_alen);
	if ( ret == -1 ){
		syserr("sendto");
		return(NULL);
	}

	/* Get the response back */
	ret = recvfrom(sd, buf, MSGLEN, 0, &retaddr, &addrlen);
	if ( ret == -1 ){
		syserr("recvfrom");
		return(NULL);
	}

	/* Now return the message itself */
	return(buf);
} /* do_transaction */

/****************************************************************************
 * narrate:  print messages to stderr for debugging and demo purposes
 * IN msg1, msg2 : strings to print along with pid and title
 * RET     nothing, dies on error
 */
narrate(char *msg1, char *msg2)
{
	fprintf(stderr,"CLIENT [%d]: %s %s\n", pid, msg1, msg2);
}
syserr(char *msg1)
{
	char	buf[MSGLEN];
	sprintf(buf,"CLIENT [%d]: %s", pid, msg1);
	perror(buf);
}

