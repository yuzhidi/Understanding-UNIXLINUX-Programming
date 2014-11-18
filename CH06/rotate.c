/* rotate.c : map a->b, b->c, .. z->a
 *   purpose: useful for showing tty modes
 */

#include   <stdio.h>
#include   <ctype.h>

int main()
{
    int c;
    while ( ( c=getchar() ) != EOF ){
        if ( c == 'z' )  
            c = 'a';
        else if (islower(c))
            c++;
        putchar(c);
    }
}
