#include<stdio.h>
#include<stdlib.h>
#include <netdb.h> 
#include<sys/socket.h>
#include<netinet/in.h>
#include <arpa/inet.h>
#include<unistd.h>
#include<string.h>
#include<ncurses.h>

#define ALT_BACKSPACE 127
#define MAX 128


void send_mode(int socket);
void recv_mode(int socket);	