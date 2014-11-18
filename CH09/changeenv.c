/* changeenv.c  - shows how to change the environment
 *                note: calls "env" to display its new settings
 */
#include	<stdio.h>

extern char ** environ;

main()
{
	char *table[3];

	table[0] = "TERM=vt100";		/* fill the table */
	table[1] = "HOME=/on/the/range";
	table[2] = 0;

	environ = table;			/* point to that table */

	execlp("env", "env", NULL);		/* exec a program	*/
}
