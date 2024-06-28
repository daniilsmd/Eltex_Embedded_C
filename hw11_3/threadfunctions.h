#ifndef THREADFUNCTIONS_H
#define THREADFUNCTIONS_H

#include <pthread.h>

void fill_store();
void *refill_store();
void *buy_store(void *arg);
void *del_mutex();

#endif