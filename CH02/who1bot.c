/*
 *  show info()
 *	displays contents of the utmp struct in human readable form
 *	*note* these sizes should not be hardwired
 */
show_info( struct utmp *utbufp )
{
	printf("%-8.8s", utbufp->ut_name);	/* the logname	*/
	printf(" ");				/* a space	*/
	printf("%-8.8s", utbufp->ut_line);	/* the tty	*/
	printf(" ");				/* a space	*/
	printf("%10ld", utbufp->ut_time);	/* login time	*/
	printf(" ");				/* a space	*/
#ifdef	SHOWHOST
	printf("(%s)", utbufp->ut_host);	/* the host	*/
#endif
	printf("\n");				/* newline	*/
}
