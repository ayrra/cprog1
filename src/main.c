#include "header.h"

sem_t sema;					//declare a semaphore for use

int main(){
	pid_t pid;
	int childPID;
	sem_init(&sema, 0, 1);		//initialize the semaphore to 1

	toContinue();	//prompts user to continue or exit
	printf("Parent Process is running\n");	//quick printf to show that parent process is running

	pid = fork();			//if successful the child is now pid 0; parent gets the child pid
	childPID = getpid();	//fork() returns childpid to the parent, transfer it to childPID for later use
	if (pid == 0)
		childProcess(childPID);		//run the child
		else
		parentProcess();
		sem_destroy(&sema);		//destroy the semaphore
		return 0;
}

//child process does all the fun stuff; create threads
//and do work
void childProcess(int childPID) {
		printf("%s", "Child process is running\n");
	FILE *fp = fopen("PTAB.txt", "wb+");		//create and open PTAB.txt
		fprintf(fp,"%s","Child PID: ");
		fprintf(fp, "%d\n", childPID);				//write CHILD PID: [childPID] to the file
		fclose(fp);

	pthread_t thread1, thread2, thread3, thread4;	//declare the 4 threads

	pthread_create(&thread1, NULL, &workerthread1, NULL);		//create the 4 threads
	pthread_create(&thread2, NULL, &workerthread2, NULL);
	pthread_create(&thread3, NULL, &workerthread3, NULL);
	pthread_create(&thread4, NULL, &workerthread4, NULL);

	pthread_join(thread1, NULL);	//makes sure all threads execute? not sure but its required for it to work.
	pthread_join(thread2, NULL);
	pthread_join(thread3, NULL);
	pthread_join(thread4, NULL);
}

//thread 1 function
void *workerthread1(){
	int count = 0;
	while(count != 10) {		//print only once
		sleep(1);			//the one second sleep before we lock
		sem_wait(&sema);
		count++;			//increment our count to 1 so we meet while condition
		FILE *fps = fopen("PTAB.txt", "ab+");			//use ab+ so the pointer always starts at the end
		fprintf(fps,"%s","Thread 1 is running\n");		//write the Thread Number to the PTAB.txt file
		sem_post(&sema);								//unlock so the other threads can run
		}
			return 0;
}

//thread 2 function
void *workerthread2() {
	int count = 0;
	while(count != 10) {
		sleep(1);
		sem_wait(&sema);
		count++;
		FILE *fps = fopen("PTAB.txt", "ab+");
		fprintf(fps,"%s","Thread 2 is running\n");
		sem_post(&sema);
		}
			return 0;
}

//thread 3 function
void *workerthread3() {
	int count = 0;
	while(count != 10) {
		sleep(1);
		sem_wait(&sema);
		count++;
		FILE *fps = fopen("PTAB.txt", "ab+");
		fprintf(fps,"%s","Thread 3 is running\n");
		sem_post(&sema);
		}
			return 0;
}

//thread 4 function
void *workerthread4() {
	int count = 0;
	while(count != 10) {
		sleep(1);
		sem_wait(&sema);
		count++;
		FILE *fps = fopen("PTAB.txt", "ab+");
		fprintf(fps,"%s","Thread 4 is running\n");
		sem_post(&sema);
		}
			return 0;
}

//parent process will wait until the child process is done
void parentProcess() {
	wait();			//force wait on the parent process to wait for child
	printf("%s", "Parent Process: Child Process has finished running\n");
}

//prompts user for C or E
//C continues program, E gracefully exits
void toContinue() {
		char input[120];
		printf("Please Enter C to continue or E to exit: \n");
redo:	scanf("%s",input);
			if (strcmp(input,"c") != 0 && strcmp(input,"C") != 0 && strcmp(input,"E") != 0 && strcmp(input,"e") != 0){
				printf("Invalid Input: Enter C or E\n");
				goto redo;
				}
		else
			if(strcmp(input,"C") != 0 && strcmp(input,"c") != 0){
				printf("Gracefully exiting program\n");
				exit(0);
			}

}



