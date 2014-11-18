/* forkdemo2.c - shows how child processes pick up at the return
 *               from fork() and can execute any code they like,
 *               even fork().  Predict number of lines of output.
 */

main()
{
	printf("my pid is %d\n", getpid() );
	fork();
	fork();
	fork();
	printf("my pid is %d\n", getpid() );
}
