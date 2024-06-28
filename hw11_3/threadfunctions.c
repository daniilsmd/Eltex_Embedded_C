#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <pthread.h>
#include "threadfunctions.h"

pthread_mutex_t mutex[4] = PTHREAD_MUTEX_INITIALIZER;
pthread_once_t mutex_once = PTHREAD_ONCE_INIT;

int stores[5];
int shoppers[3];
int var = 3;

void fill_store() {

	for (int i = 0; i < 3; i++){
		shoppers[i] = rand() % 20000 + 80000;
		pthread_mutex_init(&mutex[i], NULL);
	}
	for (int j = 0; j < 4; j++) {
    	stores[j] = rand() % 2000 + 8000;
    }
}

void *refill_store() {

	while (var != 0){
		for (int i = 0; i <= 3; i++){
			if (stores[i] <= 200) {
				stores[i] += rand() % 2000 + 4000;
				 printf("%d%s\n", i, "- ый магазин пополнен" );
			}
		}
		sleep(2);
	}
}

void *buy_store(void *arg) {

	pthread_once(&mutex_once, fill_store);
	int *inc = (int*)arg;
	int choice;
	while (var != 0) {
		choice = rand() % 4;
		while (pthread_mutex_trylock(&mutex[choice]) != 0);
		printf("%d%s%d\n", *inc, "- ый покупатель зашел в магазин ", choice);
		if (shoppers[*inc] == 0){
			var -= 1;
			pthread_exit(NULL);
		}
		if (shoppers[*inc] > stores[*inc]) {
			shoppers[*inc] -= stores[*inc];
			stores[*inc] = 0;
			printf("%d%s%d\n", *inc, "- ый покупатель запросил ", shoppers[*inc]);
		}
		else if (shoppers[*inc] <= stores[*inc]) {
			shoppers[*inc] = 0;
			stores[*inc] -= shoppers[*inc];	
		}
		sleep(2);
		pthread_mutex_unlock(&mutex[choice]);
	}
}

void *del_mutex() {

	pthread_mutex_destroy(mutex);	
}
