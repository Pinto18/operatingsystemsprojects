/*
*Nicholas DiPinto
*CS 420 Assignment #3
*
*Write a program that creates a second thread of execution within a process. 
*The program shall print out a line identifying itself as the main function
*print out its own PID and TID, but the PID and TID will be displayed in 
*separtae lines. Then, the main function promt the user for a non-zero integer 
*input. After the value is set, a second thread shall be created and the main 
*thread will spin for as long as that numeber remains zero. Then, the second
*thread will print its TID and PID and continue to spin on 0. Once the thread
* stops spinning, it will print out the value that caused it to stop, and set
*that value back to 0 so the main thread can stop spinning.
*/

/*********************************Variables***********************************
*thread2 = the second thread which is executed within the program 
*result = the result of the main thread calling the pthread_create() function
*flag = vairable which controls the spinning states of each thread
******************************************************************************/

#include<stdio.h>
#include<pthread.h>
#include<strings.h>

/////////////Global Variables/////////////
int flag = 0;
//////////////////////////////////////////

///////////Function Prototypes///////////
void *printThreadInfo(void *);
/////////////////////////////////////////

main()
{
	pthread_t thread2;
	int result;

	printf("\n\tMain:  PID is %lu\n", getpid());
	result = pthread_create(&thread2, NULL, printThreadInfo, NULL);	    
	if(result)  //the pthread_create() function failed
		printf("\tError occurred at %d, %s", __LINE__, strerror(result));
	else  //the pthread_create() successfully created a second thread
	{
		printf("\tMain: Succesfully created a thread with TID of %lu\n", thread2);
		printf("\tEnter a non-zero integer so that the other thread can get out of its spin loop: ");
		scanf("%d", &flag);
		while(flag != 0);  //enter into a spin lock for main
		printf("\tMain: Second thread has re-zeroed the flag, so I'm done.\n");
	}
}

void *printThreadInfo(void *noValue)
{
	printf("\n\t\tSecond thread: My TID is %lu, still in process #%lu\n", pthread_self(), getpid());
	printf("\t\t\tI'm about to spin until main enters a non-zero value into flag\n");
	while(flag == 0); //enter busy waiting state for second thread
	printf("\t\tSecond thread: Main set the flag to %d; I'll set it back to zero and then I'm done.\n", flag);
	flag = 0;
	return NULL;
}
