#include<stdio.h>
#include<stdlib.h>
#include <netdb.h> 
#include<sys/socket.h>
#include<netinet/in.h>
#include<unistd.h>
#include<string.h>
#include<ncurses.h>
#include"chat.h"

void send_mode(int socket){
	char buff[MAX];
	char tmp;
	int n, y=0, x=0;
	for(;;){
		bzero(buff, sizeof(buff));
		printw("YOU: ");
		n=0;
		while(1){
			tmp = getch();
			getyx(stdscr, y, x);
			if(tmp == '`')
				return;
			else if(tmp == '\n')
				break;
			else if(tmp == ALT_BACKSPACE){
				if(x >=6){
					mvdelch(y, x-1);
					buff[--n] = NULL;
				}
			}
			else{
				printw("%c", tmp);
				buff[n++] = tmp;
			}
			refresh();
		}
		x = 0;
		move(++y, x);
		send(socket, buff, sizeof(buff), 0);
	}
	return;
}

void recv_mode(int socket){	
	char buff[MAX];
	char tmp;
	int n, y, x;
	printw("\nLISTENING...");	
	getyx(stdscr, y, x);
	move(++y, 0);
	while(1){
		refresh();
		timeout(1);
		if((tmp = getch())== 'q')
			return;
		bzero(buff, sizeof(buff));
		recv(socket, buff, sizeof(buff), MSG_WAITALL);
		printw("RECEIVED: %s", buff);
		move(++y, 0);
	}
	return;
}
