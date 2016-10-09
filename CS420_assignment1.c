/*
*Nicholas DiPinto
*CS 420 Assignment #1
*
*Write a program that creates three children programs. The program shall
*iterate three times, and with each iteration it will print a line that 
*identifies itself as the parent process, provides the process identifier
*of the parent process, states which child it is spawning, and the process
*identifier of that child. Each child process must identify itsel as a 
*child process with its process identification number and child number,and
*print out the process identification number of its parent. Additionally, 
*a small C program must be written for child #2 that prints out another line
* which includes its PID and its parents PID.
*/

/*********************************Variables***********************************
*pid = the process identification number of the process in execution
*childNum = the number indicating the order in which the child was spawned by the parent process
******************************************************************************/

#include <stdio.h>
#include <sys/types.h>

#define MAX_CHILDREN 3

main()
{
   pid_t pid;
   int childNum;

   for(childNum = 1; childNum <= MAX_CHILDREN; childNum++)
   {
      pid = fork();
      if(pid)
         printf("Parent, my pid is %d: Spawned child #%d whose pid is %d\n", getpid(), childNum, pid);
      else
      {
         printf("\t I am child #%d, my pid is %d; my parent's pid is %d\n", childNum, getpid(), getppid());
         if(childNum == 2)
            execv("child2Replacement.exe",  NULL);
         break;
      }
   }   
}
