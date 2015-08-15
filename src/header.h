#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>
#include <string.h>

void childProcess();
void parentProcess();

void *workerthread1();
void *workerthread2();
void *workerthread3();
void *workerthread4();

void toContinue();


