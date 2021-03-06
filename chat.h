#include<stdio.h>
#include<stdlib.h>
#include <netdb.h> 
#include<sys/socket.h>
#include<netinet/in.h>
#include <arpa/inet.h>
#include<unistd.h>
#include<string.h>
#include<pthread.h>
#include<ncurses.h>
#include"ui.h"

//common
#define ALT_BACKSPACE 127
#define MAX 128 //common buffer size
#define MAX_UNAME 36
#define BYE_MESSAGE 10101010

//server-specific
#define MAX_THREADS 4
#define MAX_CLIENTS 4

//client-specific
void chat_loop(int socket);
int send_uname(int socket);
int send_pass(int socket);
//server-specific

//common
int check_buff(char* buffer, size_t n);
int find_free(int array[], size_t size);
int find_string_in_array(char** array, char* entry,  size_t arr_len);
