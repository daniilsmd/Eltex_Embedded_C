#include <stdio.h>
#include <pthread.h>
#include "threadindex.h"

int main() {
	pthread_t thread[5];
	int threads[5];
	for (int i = 0; i <= 4; i++) {
		threads[i] = i + 1;
		pthread_create(&thread[i], NULL, output_thread_index, (void*)&threads[i]);
	}

	for (int j = 0; j <= 4; j++) {
		pthread_join(thread[j], NULL); 
	}
}
