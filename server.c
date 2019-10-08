#include"chat.h"


void* connection_handler(void* socket);
void transmitt(int socket, int index);
void recv_uname(int socket, char* uname, size_t len);

int n = 0;
int clients[MAX_CLIENTS];
struct sockaddr_in address;
int addrlen = sizeof(address);
pthread_mutex_t lock;

int main(int argc, char **argv)
{
	if(argc < 2){
		printf("Usage: server <port>\n");
		return 0;
	}
	int sock, client, valread;
	int port = atoi(argv[1]);
	int opt = 1;
	pthread_t thread;
	pthread_t pool[MAX_THREADS];

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
	//if((client = accept(sock, (struct sockaddr*)&address, (socklen_t*)&addrlen))<0 ){
	//	perror("ACCEPT FAILED");
	//	exit(EXIT_FAILURE);
	//}
	pthread_mutex_init(&lock, NULL);
	for(int i=0;i<MAX_THREADS;i++){
	 	pthread_create(&pool[i], NULL, connection_handler, &sock);
	}
	for(int i =0;i<MAX_CLIENTS;i++){
		pthread_join(pool[i], NULL);	
	}

	return 0;

}

void* connection_handler(void* socket){
	int sock = *((int *)socket);
	int client;
	size_t index;
	while(1){	
		printf("THREAD: %x WAITING FOR CONNECTIONS\n", pthread_self);
		client = accept(sock, (struct sockaddr*)&address, (socklen_t*)&addrlen);
		pthread_mutex_lock(&lock);
		index = find_free(clients, MAX_CLIENTS);
		if(index < 0){
			char* buff = "NO CONNECTIONS AVAILABLE";
			send(client, buff, sizeof(buff), 0);
			printf("MAX CLIENTS REACHED\n");
			pthread_mutex_unlock(&lock);
		}
		else{
			clients[index] = client;
			pthread_mutex_unlock(&lock);
			transmitt(client, index);
		}
	}
}


void transmitt(int socket, int index){
	printf("CONNECTION TO THREAD %x\n", pthread_self());
	char tmp[MAX];
	char bye[MAX];
	char uname[MAX_UNAME];
	char buffer[MAX+MAX_UNAME];
	sprintf(bye, "%d", BYE_MESSAGE);
	recv_uname(socket, uname, MAX_UNAME);
	while(1){
		bzero(tmp, sizeof(tmp));
		bzero(buffer, sizeof(buffer));
		recv(socket, tmp, sizeof(tmp), 0);
		if(strncmp(bye, tmp, MAX) == 0){
			printf("THREAD: %x DISCONNECTED\n", pthread_self());
			snprintf(buffer, sizeof(buffer), "SERVER MESSAGE: %s HAS DISCONNECTED", uname);
			for(int i =0;i<MAX_CLIENTS;i++){
				if(clients[i] != NULL){
					send(clients[i], buffer, sizeof(buffer), 0);
				}
			}
			clients[index] = NULL;
			return;
		}
		snprintf(buffer, sizeof(buffer), "%s: %s", uname, tmp);
		for(int i =0;i<MAX_CLIENTS;i++){
			if(clients[i] != NULL){
				send(clients[i], buffer, sizeof(buffer), 0);
			}
		}
	}
}

void recv_uname(int socket, char* uname, size_t len){
	char prompt[MAX_UNAME];
	snprintf(prompt, sizeof(prompt), "USERNAME: ");
	send(socket, prompt, sizeof(prompt), 0);
	recv(socket, uname, len, 0);
	printf("USERNAME RECEIVED: %s\n", uname);
}
