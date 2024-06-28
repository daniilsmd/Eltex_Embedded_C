#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <pthread.h>
#include "threadfunctions.h"


int main(){

	pthread_t load_thread;
	pthread_t shopper_thread[3];
	int val[4];

	for (int i = 0; i < 3; i++){
		val[i] = i;
		pthread_create(&shopper_thread[i], NULL, &buy_store, &val[i]);
	}
	pthread_create(&load_thread, NULL, refill_store, NULL);

	for (int j = 0; j < 3; j++){
		pthread_join(shopper_thread[j], NULL);
	}
	pthread_join(load_thread, NULL);
  del_mutex();
return 0;
}
