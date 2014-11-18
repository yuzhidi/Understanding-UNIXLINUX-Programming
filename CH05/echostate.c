/* echostate.c
 *   reports current state of echo bit in tty driver for fd 0
 *   shows how to read attributes from driver and test a bit
 */

#include        <stdio.h>
#include        <termios.h>

main()
{
        struct termios info;
        int rv;

        rv = tcgetattr( 0, &info );     /* read values from driver      */

        if ( rv == -1 ){
                perror( "tcgetattr");
                exit(1);
        }
        if ( info.c_lflag & ECHO )
                printf(" echo is on , since its bit is 1\n");
        else
                printf(" echo if OFF, since its bit is 0\n");
}
