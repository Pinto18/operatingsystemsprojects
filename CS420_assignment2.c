/*
*Nicholas DiPinto
*CS 420 Assignment #2
*
*Write a program that creates a second thread of execution within a process. 
*The program shall print out a line identifying itself as the main function
*print out its own PID and TID. Then, the main function shall create a second
*thread. The thread shall be executed by a seond function that identifies 
*itself as the second thread and prints its PID and TID. The main function 
*will check for success in creating the second thread. If succesful, then 
*the main function will print the TID of the second thread.
*/

/*********************************Variables***********************************
*thread2 = the second thread which is executed within the program 
*result = the result of the main thread calling the pthread_create() function
******************************************************************************/

#include<stdio.h>
#include<pthread.h>
#include<strings.h>
void *printThreadInfo(void *);

main()
{
	pthread_t thread2;
	int result;

	printf("\nmain thread here; pid is %lu, tid is %lu\n", getpid(), pthread_self());
	result = pthread_create(&thread2, NULL, printThreadInfo, NULL);	    
	if(result)  //the pthread_create() function failed
		printf("Error occurred at %d, %s", __LINE__, strerror(result));
	else  //the pthread_create() successfully created a second thread
	{
		printf("\nmain succesfully created a new thread TID of %lu\n", thread2);
		pthread_join(thread2, NULL);
		printf("\nmain: second thread has terminated, main will now exit.\n");
	}
}

void *printThreadInfo(void *noValue)
{
	printf("\n	second thread here, my tid is %lu but I'm still in process %lu\n", pthread_self(), getpid());
	return NULL;
}
