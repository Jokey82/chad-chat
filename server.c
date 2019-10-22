#include<stdio.h>
#include<stdlib.h>
#include <netdb.h> 
#include<sys/socket.h>
#include<netinet/in.h>
#include<unistd.h>
#include<string.h>
#include<pthread.h>
#include"chat.h"

#define MAX_THREADS 4
#define MAX_CLIENTS 10

void* connection_handler(void* socket);
void transmitt(int socket, int index);
int find_free(int array[], size_t size);

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
			pthread_mutex_unlock(&lock);
		}
		else{
			clients[index] = client;
			pthread_mutex_unlock(&lock);
			transmitt(client, index);
		}
	}
	//else{return;}
}

void transmitt(int socket, int index){
	char buff[MAX];
	char bye[MAX];
	sprintf(bye, "%d", BYE_MESSAGE);
	while(1){
		bzero(buff, sizeof(buff));
		recv(socket, buff, sizeof(buff), 0);
		if(strncmp(bye, buff, MAX) == 0){
			printf("THREAD: %x DISCONNECTED\n", pthread_self());
			clients[index] = NULL;
			return;
		}
		for(int i =0;i<MAX_CLIENTS;i++){
			if(clients[i] != NULL){
				send(clients[i], buff, sizeof(buff), 0);
			}
		}
	}
}

int find_free(int array[], size_t size){
	for(int i =0; i<size;i++){
		if(array[i] == NULL){return i;};
	}
	return -1;
}
