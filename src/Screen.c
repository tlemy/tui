#include "../include/Screen.h"
#include "../include/common.h"

int command_screen(Command cmd) 
{	
	size_t res = 0;
					 
	switch(cmd) 
	{
		case CLEAR_SCREEN:
			res = printf("%s", CLEAR_SCREEN_CODE);
			break;	
		case ERASE_SCROLLBACK_BUFFER:
			res = printf("%s", ERASE_SCROLLBACK_BUFFER_CODE);
			break;
		case MOVE_CURSOR_TOP_LEFT:
			res = printf("%s", MOVE_CURSOR_TOP_LEFT_CODE);
			break;
		case HIDE_CURSOR:
			res = printf("%s", HIDE_CURSOR_CODE);
			break;
		case RESET:
			res = printf("%s", RESET_CODE);
			break;
		default:
			break;
	}
	
	if (res <= 0) 
	{
		return res;
	}

	return 0;
}

int save_screen() 
{
	int res = fflush(stdout);
	return res;
}
