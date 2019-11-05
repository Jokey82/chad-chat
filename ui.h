#include<stdio.h>
#include<stdlib.h>
#include<ncurses.h>


WINDOW *create_newwin(int height, int width, int starty, int startx);	
int init_ui();
void print_msg(char* msg);
void print_char(WINDOW *win, char ch);
void clear_prompt();
void erase_char(WINDOW* win);
void exit_ui();
WINDOW* init_popup();
void print_popup_prompt(WINDOW* win, char* msg);
void close_window(WINDOW* win);




