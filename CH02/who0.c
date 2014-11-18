#include	<stdio.h>
#include	<fcntl.h>
#include	<utmp.h>

/*
 *	who version 0
 *		main outline but no substance
 */

int
main()
{
        int         fd;                 /* for file des of utmp */
        struct utmp current_record;     /* hold info from file */
        int         reclen = sizeof(struct utmp);

        fd = open(UTMP_FILE, O_RDONLY);
        if ( fd == -1 ){
                perror( "who0" );       /* report a system error */
                exit(1);                /* and get out now       */
        }

        while ( read(fd, &current_record, reclen) == reclen )
                show_info( &current_record );

        close (fd);
        return 0;
}
