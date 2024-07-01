#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <termios.h>
#include <signal.h>
#include <curses.h>
#include <dirent.h>
#include <time.h>
#include <malloc.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <sys/wait.h>
#include <sys/ioctl.h>

#ifndef __INCLUDES_H__
#define __INCLUDES_H__

struct req_send {
    long type_m;
    char msg[50];
    char users[10][20];
    int amount_users;
    int num_user;  
    int type_msg; 
    int prt;
};

#endif
