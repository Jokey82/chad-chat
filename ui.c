#include "ui.h"



WINDOW *msgar;
WINDOW *popup;

int init_ui(){
	int startx, starty, width, height;	

	initscr();
	//cbreak();		
	raw();
	keypad(stdscr, FALSE);	
	noecho();

	height = LINES-10;
	width = COLS;
	starty = 0;
	startx = 0;
	refresh();
	msgar = create_newwin(height, width, starty, startx);

	wmove(stdscr, LINES-9, 0);
	whline(stdscr, '=', COLS);
	mvwprintw(stdscr, height+2, 0, "->: ");
	refresh();
	scrollok(msgar, TRUE);
	return 0;	
}

WINDOW* init_popup(){
	WINDOW *temp;
	int height=10, width=COLS-10, y=LINES/2, x=5;
	temp = create_newwin(height, width, y, x);
	box(temp, '|', '-');
	wrefresh(temp);
	return temp;
}

void print_popup_prompt(WINDOW* win, char* msg){
	mvwprintw(win, 2, 10, "%s", msg);
	mvwprintw(win, 4, 10, "->: ");
	wrefresh(win);
}

void print_msg(char* msg){
	static int y=2, x=2;
	int maxy, maxx;
	getmaxyx(msgar, maxy, maxx);
	mvwprintw(msgar, y++, x, "%s", msg);
	if(y==maxy){
		scroll(msgar);
		y--;
	}
	wrefresh(msgar);
}


void close_window(WINDOW* win){
	werase(win);
	wborder(win, ' ', ' ', ' ',' ',' ',' ',' ',' ');	
	wrefresh(win);
	delwin(win);
}


void print_char(WINDOW *win, char ch){
	wprintw(win, "%c", ch);
	wrefresh(win);	
}

void erase_char(WINDOW* win){
	int y, x;
	getyx(win, y, x);
	wmove(win, y, x-1);
	wdelch(win);
	wrefresh(win);
}

void clear_prompt(){
	wmove(stdscr, LINES-8, 4);
	wclrtobot(stdscr);
	refresh();
}

void exit_ui(){
	endwin();
}

WINDOW *create_newwin(int height, int width, int starty, int startx){	
	WINDOW *local_win;

	local_win = newwin(height, width, starty, startx);
				
			
	wrefresh(local_win);

	return local_win;
}

