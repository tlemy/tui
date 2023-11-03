#include "../include/Control.h"
#include "../include/common.h"

void init_control() 
{
	initscr();              // Initialize the curses library
    	cbreak();               // Disable line buffering
    	noecho();               // Disable echoing of characters
    	nodelay(stdscr, 1);
}
