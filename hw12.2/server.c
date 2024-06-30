#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <fcntl.h>

int main() {
	
	char msg[] = "Hi!";
	mkfifo ("pipe", 0666);
	int f = open("pipe", O_WRONLY);
	write(f, msg, sizeof(msg));
	close (f);
}