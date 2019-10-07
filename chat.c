#include<stdio.h>
#include<stdlib.h>
#include <netdb.h> 
#include<sys/socket.h>
#include<netinet/in.h>
#include<unistd.h>
#include<string.h>
#include<ncurses.h>
#include"chat.h"


void chat_loop(int socket){
	char buff[MAX], sbuff[MAX];
	char tmp;
	int n, y=0, x=0, maxcol, maxrow, recy, recx;
	getmaxyx(stdscr, maxrow, maxcol);
	recy = 0;
	recx = maxcol/2;
	timeout(1);
	bzero(buff, sizeof(buff));
	printw("YOU: ");
	n=0;
	while(1){
		tmp = getch();
		getyx(stdscr, y, x);
		if(tmp == '`'){
			sprintf(buff, "%d", BYE_MESSAGE);
			send(socket, buff, sizeof(buff), 0);
			return;
		}
		else if(tmp == '\n'){
			send(socket, buff, sizeof(buff), 0);
			bzero(buff, sizeof(buff));
	//		printw("YOU: ");
			move(++y, 0);
			n=0;
		}
		else if(tmp == ALT_BACKSPACE){
			if(x > 0){
				mvdelch(y, x-1);
				buff[--n] = NULL;
			}
		}
		else if(tmp != ERR){
			printw("%c", tmp);
			buff[n++] = tmp;
		}

		bzero(sbuff, sizeof(sbuff));
		recv(socket, sbuff, sizeof(sbuff), MSG_DONTWAIT);
		if(check_buff(sbuff, sizeof(sbuff)) == 0){
			getyx(stdscr, y, x);
			move(recy++, recx); 
			printw("RECEIVED: %s", sbuff);
			move(y, x);
		}
		refresh();
	}
}

int check_buff(char* buffer, size_t n){
	for(int i=0;i<n;i++){
		if(buffer[i]!=NULL)
			return 0;
	}
	return -1;
}
