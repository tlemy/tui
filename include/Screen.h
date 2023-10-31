#define CODE_MAX_LEN 10

#define CLEAR_SCREEN_CODE "\033[2J"
#define ERASE_SCROLLBACK_BUFFER_CODE "\033[3J"
#define MOVE_CURSOR_TOP_LEFT_CODE "\033[0;0H"
#define HIDE_CURSOR_CODE "\033[?25l"
#define RESET_CODE "\033[0m"

typedef enum 
{
	CLEAR_SCREEN,
	ERASE_SCROLLBACK_BUFFER,
	MOVE_CURSOR_TOP_LEFT,
	HIDE_CURSOR,
	RESET
} Command;

int command_screen(Command cmd);

int save_screen();
