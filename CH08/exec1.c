/* exec1.c - shows how easy it is for a program to run a program
 */

main()
{
	char	*arglist[3];

	arglist[0] = "ls";
	arglist[1] = "-l";
	arglist[2] = 0 ;
	printf("* * * About to exec ls -l\n");
	execvp( "ls" , arglist );
	printf("* * * ls is done. bye\n");
}
