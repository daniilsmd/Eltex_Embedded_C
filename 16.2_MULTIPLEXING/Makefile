.PHONY := clean

bin1 := tcp_client
bin2 := udp_client
bin3 := server
CC:= gcc

all: gcc

gcc:
		$(CC) tcp_client.c -o $(bin1) -g -lncurses
		$(CC) udp_client.c -o $(bin2) -g -lncurses
		$(CC) server.c -o $(bin3) -g -lncurses

clean: 
		rm -rf *.o *.a client serv 