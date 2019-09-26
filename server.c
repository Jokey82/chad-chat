#include<stdio.h>
#include<stdlib.h>
#include <netdb.h> 
#include<sys/socket.h>
#include<netinet/in.h>
#include<unistd.h>
#include<string.h>
#include<ncurses.h>
#include"chat.h"

int main(int argc, char **argv)
{
	if(argc < 2){
		printf("Usage: server <port>\n");
		return 0;
	}
	int sock, client, valread;
	uint16_t port = atoi(argv[1]);
	struct sockaddr_in address;
	int opt = 1;
	int addrlen = sizeof(address);
	char buffer[1024];
	char *message = "CONNECTION SUCCESSFUL";	

	if((sock = socket(AF_INET, SOCK_STREAM, 0)) == 0){
		perror("SOCKET FAILED");
		exit(EXIT_FAILURE);
	}
	
	if (setsockopt(sock, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT,&opt, sizeof(opt))) { 
        	perror("setsockopt"); 
        	exit(EXIT_FAILURE); 
         } 
	
	address.sin_family = AF_INET;
	address.sin_addr.s_addr = INADDR_ANY;
	address.sin_port = htons(port);
	
	if(bind(sock, (struct sockaddr *)&address, sizeof(address))<0){
		perror("BIND FAILED");
		exit(EXIT_FAILURE);
	}
	
	if(listen(sock, 3) < 0){
		perror("LISTEN FAILED");
		exit(EXIT_FAILURE);
	}
	
	printf("LISTENING ON PORT %d\n", port);
	if((client = accept(sock, (struct sockaddr*)&address, (socklen_t*)&addrlen))<0 ){
		perror("ACCEPT FAILED");
		exit(EXIT_FAILURE);
	}
    	send(client,message, strlen(message) , 0 ); 
	initscr();
	noecho();
	raw();
	send_mode(client);
	endwin();
	return 0;

}

