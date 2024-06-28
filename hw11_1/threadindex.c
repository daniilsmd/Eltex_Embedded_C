#include <stdio.h>
#include <pthread.h>
#include "threadindex.h"

void* output_thread_index(void *arg){
	int *i = (int*) arg;
	printf("Номер потока: %d\n", *i);
}