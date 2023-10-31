#include "../include/Screen.h"
#include "../include/Logger.h"
#include "../include/Rect.h" 
#include "../include/common.h"

int main(int argc, char *argv[])
{
        if (argc < 3)
        {
                return -1;
        }
	
	char square[] = "\u2588\u2588";
        int w = atoi(argv[1]) - 2;
        int h = atoi(argv[2]);
	int x = w / 2 - 1;
	int y = h / 2;
	int len = strlen(square);
	
	Rect *top_left_square = create_rect(x - 2, y, 255, 0, 0, &square);
	Rect *top_right_square = create_rect(x, y, 255, 255, 0, &square);
	Rect *bottom_left_square = create_rect(x - 2, y + 1, 0, 255, 0, &square);
	Rect *bottom_right_square = create_rect(x, y + 1, 0, 0, 255, &square);
	
	Rect *image[4] = 
	{
		top_left_square,
		top_right_square,
		bottom_left_square,
		bottom_right_square
	};

	command_screen(CLEAR_SCREEN);
	command_screen(HIDE_CURSOR);

	int x_mov = 2;
	int y_mov = 1;
	char coordinates[20];
	FILE *logs = init_logs("bouncing_ball.log");

	for (;;) 
	{
		command_screen(CLEAR_SCREEN);
		command_screen(ERASE_SCROLLBACK_BUFFER);
                command_screen(MOVE_CURSOR_TOP_LEFT);
		
		draw_multiple_rect(4, image);
		sprintf(coordinates, "bounce: %d, %d\n", bottom_right_square->x, bottom_right_square->y);

		if (top_left_square->x + x_mov <= 0 || top_right_square->x + x_mov > w) 
		{
			x_mov *= -1;
			write_log(logs, coordinates);

		}

		if (top_left_square->y + y_mov <= 0 || bottom_left_square->y + y_mov > h)
                {
                        y_mov *= -1;
			write_log(logs, coordinates);
                }

		move_multiple_rect_by(x_mov, y_mov, 4, image);		

		save_screen();
		usleep(20 * 1000);
	}

	free_rect(top_left_square);
	free_rect(top_right_square);
	free_rect(bottom_left_square);
	free_rect(bottom_right_square);
}
