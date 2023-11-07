#include "../include/Screen.h"
#include "../include/Logger.h"
#include "../include/Rect.h"
#include "../include/Control.h"
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
	char coordinates[20];
	
	Rect *top_left_square = create_rect(x - 2, y, 255, 0, 0, square);
	Rect *top_right_square = create_rect(x, y, 255, 255, 0, square);
	Rect *bottom_left_square = create_rect(x - 2, y + 1, 0, 255, 0, square);
	Rect *bottom_right_square = create_rect(x, y + 1, 0, 0, 255, square);
	
	Rect *image[4] = 
	{
		top_left_square,
		top_right_square,
		bottom_left_square,
		bottom_right_square
	};

	command_screen(CLEAR_SCREEN);
	command_screen(HIDE_CURSOR);
	init_control();

	int x_mov = 2;
	int y_mov = 1;
	char keys[20];
	FILE *logs = init_logs("./logs/move_ball.log");
	char c = '\0';

	for (;;) 
	{
		command_screen(CLEAR_SCREEN);
		command_screen(ERASE_SCROLLBACK_BUFFER);
		
		c = getch();
		
		if (c == 'w') 
		{
			move_multiple_rect_by(0, y_mov * -1, 4, image);
                	sprintf(keys, "up\n");
                        write_log(logs, keys);
		}

		else if (c == 's')
                {
                        move_multiple_rect_by(0, y_mov, 4, image);
                        sprintf(keys, "down\n");
                        write_log(logs, keys);
                }

		else if (c == 'a')
                {
                        move_multiple_rect_by(x_mov * -1, 0, 4, image);
                        sprintf(keys, "left\n");
                        write_log(logs, keys);
                }

		else if (c == 'd')
                {
                        move_multiple_rect_by(x_mov, 0, 4, image);
                        sprintf(keys, "right\n");
                        write_log(logs, keys);
                }
		else if (c == 'q') 
		{
			break;
		}

		draw_multiple_rect(4, image);
		sprintf(coordinates, "%d, %d\n", top_left_square->x, top_left_square->y);
		write_log(logs, coordinates);
		
		save_screen();
		usleep(20 * 1000);
	}

	free_rect(top_left_square);
	free_rect(top_right_square);
	free_rect(bottom_left_square);
	free_rect(bottom_right_square);
}
