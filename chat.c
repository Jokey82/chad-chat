#include"chat.h"


void chat_loop(int socket){
	char buff[MAX], sbuff[MAX+MAX_UNAME];
	char tmp;
	int n;
	timeout(1);
	bzero(buff, sizeof(buff));
	n=0;
	while(1){
		tmp = getch();
		if(tmp == '`'){
			sprintf(buff, "%d", BYE_MESSAGE);
			send(socket, buff, sizeof(buff), 0);
			return;
		}
		else if(tmp == '\n'){
			if(send(socket, buff, sizeof(buff), 0)<0){
				print_msg("Failed to send message to server\n");
			}
			bzero(buff, sizeof(buff));
			clear_prompt();
			n=0;
		}
		else if(tmp == ALT_BACKSPACE){
			if(n > 0){
				erase_char(stdscr);
				buff[--n] = NULL;
			}
		}
		else if(tmp != ERR){
			print_char(stdscr, tmp);
			buff[n++] = tmp;
		}

		bzero(sbuff, sizeof(sbuff));
		recv(socket, sbuff, sizeof(sbuff), MSG_DONTWAIT);
		if(check_buff(sbuff, sizeof(sbuff)) == 0){
			print_msg(sbuff);
		}
	}
}

int send_uname(int socket){
	char buff[MAX], unbuff[MAX_UNAME];
	char tmp;
	int n=0;
	WINDOW* uname_win;
	bzero(buff, sizeof(buff));
	bzero(unbuff, sizeof(unbuff));
	uname_win = init_popup();
	if(recv(socket, buff, sizeof(buff), 0)<0){
		print_popup_prompt(uname_win, "Failed to get responce from server");
		return -1;
	}
	print_popup_prompt(uname_win, buff);
	while((tmp = getch())!='\n' || n<1){
		if(tmp == ALT_BACKSPACE){
			if(n > n){
				erase_char(uname_win);
				unbuff[--n] = NULL;
			}
		}
		else if(tmp != ERR && tmp != '\n'){
			if(n < MAX_UNAME){
				print_char(uname_win, tmp);
				unbuff[n++] = tmp;
			}
		}
	}
	close_window(uname_win);
	return send(socket, unbuff, sizeof(unbuff), 0);
}	

int send_pass(int socket){
	char buff[MAX], passbuff[MAX_UNAME];
	char tmp;
	int n=0;
	WINDOW* pass_win;
	bzero(buff, sizeof(buff));
	pass_win = init_popup();
	if(recv(socket, buff, sizeof(buff), 0)<0){
		print_popup_prompt(pass_win, "Failed to get responce from server");
		return -1;
	}
	print_popup_prompt(pass_win, buff);
	while((tmp = getch())!='\n'){
		if(tmp == ALT_BACKSPACE){
			if(n > 0){
				erase_char(pass_win);
				passbuff[--n] = NULL;
			}
		}
		else if(tmp != ERR && tmp != '\n'){
			if(n < MAX_UNAME){
				print_char(pass_win, '*');
				passbuff[n++] = tmp;
			}
		}
	}
	close_window(pass_win);
	return send(socket, passbuff, sizeof(passbuff), 0);
	
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

int find_string_in_array(char** array, char* entry,  size_t arr_len){
	for(int i=0;i<arr_len;i++){
		if(array[i]!=NULL){
			if(strcmp(array[i], entry) == 0){
				return i;
			}
		}
	}
	return -1;
	
}
