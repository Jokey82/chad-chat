#include"chat.h"


void chat_loop(int socket){
	char buff[MAX], sbuff[MAX+MAX_UNAME];
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
			printw("%s", sbuff);
			move(y, x);
		}
		refresh();
	}
}

void send_uname(int socket){
	char buff[MAX], unbuff[MAX_UNAME];
	char tmp;
	int n=0, y=0, x=0, init_x;
	size_t count =0;
	bzero(buff, sizeof(buff));
	recv(socket, buff, sizeof(buff), 0);
	printw("%s", buff);
	getyx(stdscr, y, init_x);
	while((tmp = getch())!='\n'){
		getyx(stdscr, y, x);
		if(tmp == ALT_BACKSPACE){
			if(x > init_x){
				mvdelch(y, x-1);
				unbuff[--n] = NULL;
			}
		}
		else if(tmp != ERR){
			if(n < MAX_UNAME){
				printw("%c", tmp);
				unbuff[n++] = tmp;
			}
		}
		refresh();
	}
	printw("\n");
	send(socket, unbuff, sizeof(unbuff), 0);
}	

int check_buff(char* buffer, size_t n){
	for(int i=0;i<n;i++){
		if(buffer[i]!=NULL)
			return 0;
	}
	return -1;
}

int find_free(int array[], size_t size){
	for(int i =0; i<size;i++){
		if(array[i] == NULL){return i;};
	}
	return -1;
}
