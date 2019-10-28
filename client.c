
#include"chat.h"

int main(int argc, char **argv)
{


	if(argc < 3){
		printf("Usage: client <address> <port>\n");
		return 0;
	}
	int sock, valread;
	uint16_t port = atoi(argv[2]);
        char* address = argv[1];	
	struct sockaddr_in serv_addr;
	char buffer[1024];
	char *message = "CLIENT CONNECTED\n";	

	if((sock = socket(AF_INET, SOCK_STREAM, 0)) == 0){
		perror("SOCKET FAILED");
		exit(EXIT_FAILURE);
	}
	
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(port);

	if(inet_pton(AF_INET, address, &serv_addr.sin_addr)<=0){
		perror("INVALID ADDRESS");
		exit(EXIT_FAILURE);
	}
	printf("CONNECTING TO %s PORT %d\n", address, port);
	if(connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr))<0){
		perror("CONNECTION FAILED");
		exit(EXIT_FAILURE);
	}
	initscr();
	raw();
	noecho();
	if(send_pass(sock)<0){
		printw("Failed to authorize\n");
		endwin();	
		return 0;
	}
	if(send_uname(sock)<0){
		printw("Failed to send username\n");
		endwin();
		return 0;
	}
	chat_loop(sock);
	endwin();
    	return 0;

}

