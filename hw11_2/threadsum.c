#include <stdio.h>
#include <pthread.h>
#include "threadsum.h"

void *threadsum(void *arg) {
	int *sum = (int*)arg;
	while(*sum < 1000){
		*sum += 1;	
	}
}