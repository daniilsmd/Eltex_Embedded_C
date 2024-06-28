#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "threadsum.h"

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER; 

int main() {

	pthread_t theard[5];
	int sum = 0;

	for (int i = 0; i < 5; i++) {
		pthread_create(&theard[i], NULL, threadsum, &sum);
		printf("Создание %d - ого потока\n", i);
	}
	for (int j = 0; j < 5; j++){
		pthread_join(theard[j], NULL);
	}
	printf("Сумма: %d\n", sum);
}
