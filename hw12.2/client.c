#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <fcntl.h>

int main() { 

	char msg[127];
	int f = open("pipe", O_RDONLY);
	read(f, msg, sizeof(msg));
	printf("%s\n", msg);
	close(f);
}