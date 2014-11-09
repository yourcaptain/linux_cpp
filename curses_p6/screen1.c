#include <unistd.h>
#include <stdlib.h>
#include <curses.h>

int main(){
	
	initscr();

	move(5, 5);
	printw("%s", "Hello World.");
	refresh();

	beep();

	sleep(2);

	endwin();
	exit(EXIT_SUCCESS);

}
