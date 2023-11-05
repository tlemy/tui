#include "../include/Screen.h"
#include "../include/Logger.h"
#include "../include/Snake.h"
#include "../include/Control.h"
#include "../include/common.h"

int main(int argc, char *argv[]) 
{
	FILE *logs = init_logs("./logs/snake.log");

	if (!logs) 
	{
		perror("Cannot init_logs: ");
		return -1;
	}

	if (argc < 3) 
	{
		char error[] = "Missing parameters\n";
		write_log(logs, error);
		return -1;
	}
	
	char str_half_square[] = "\u2588\u2588\u2588\u2588";
	char *half_square = (char *) malloc(sizeof (char) * strlen(str_half_square));
	strcpy(half_square, str_half_square);

	int width_square = 4; // number of visible characters
	int heigth_square = 2;

	int w = atoi(argv[1]);
	int h = atoi(argv[2]);

	int init_x = w - (w % width_square); 
	int init_y = h / heigth_square;
	int inc_x = width_square;
	int dec_x = inc_x * -1;
	int inc_y = heigth_square;
	int dec_y = inc_y * -1;

	int r = 240;
	int g = 240;
	int b = 240;

	int millisecs = 100;

	Rect *top_head = create_rect(init_x, init_y, 0, g, 0, half_square);
	Rect *bottom_head = create_rect(init_x, init_y + 1, 0, g, 0, half_square);
	Rect *top_body = create_rect(init_x + width_square, init_y, 0, g - 5, 0, half_square);
	Rect *bottom_body = create_rect(init_x + width_square, init_y + 1, 0, g - 5, 0, half_square);
	Rect *top_tail = create_rect(init_x + width_square * 2, init_y, 0, g - 10, 0, half_square);
	Rect *bottom_tail = create_rect(init_x + width_square * 2, init_y + 1, 0, g - 10, 0, half_square);
	Rect *top_apple = create_rect(w / 2, init_y, r, 0, 0, half_square);
        Rect *bottom_apple = create_rect(w / 2, init_y + 1, r, 0, 0, half_square);

	Rect *head[2] = { top_head, bottom_head };
	Rect *body[2] = { top_body, bottom_body };
	Rect *tail[2] = { top_tail, bottom_tail };
	Rect *apple[2] = { top_apple, bottom_apple };

	Snake *snake_head = create_snake(head, 2, NULL, LEFT, dec_x, 0);
	Snake *snake_body = create_snake(body, 2, snake_head, LEFT, 0, 0);
	Snake *snake_tail = create_snake(tail, 2, snake_body, LEFT, 0, 0);
	Snake *snake_apple = create_snake(apple, 2, NULL, BORDER, 0, 0);

	command_screen(CLEAR_SCREEN);
        command_screen(HIDE_CURSOR);
	init_control(); // IMPORTANT: getch in control_snake won't work without this
	
	for (;;) 
	{
		command_screen(CLEAR_SCREEN);
                command_screen(ERASE_SCROLLBACK_BUFFER);

		if (control_snake(snake_head, inc_x, dec_x, inc_y, dec_y)) 
		{
			break;
		}
		if (check_collision_with_snake(snake_head, snake_apple, width_square, heigth_square)) 
		{
			for (int i = 0; i < snake_apple->len; i++) 
			{
				//snake_apple->rects[i]->x = init_x;
				snake_apple->rects[i]->y += heigth_square;
			}	
		}
		if (!check_border_collision_snake(snake_head, w, h, width_square, heigth_square)) 
		{
			move_multiple_rect_by(snake_head->mov_x, snake_head->mov_y, snake_head->len, snake_head->rects);
		}
		else 
		{
			snake_head->dir = BORDER;
		}
		
		draw_multiple_rect(snake_apple->len, snake_apple->rects);	
		draw_and_move_snake(snake_head, snake_tail, w, h, width_square, heigth_square);
		save_screen();
                usleep(millisecs * 1000);
	}
	
	free_snake(snake_tail);
	free(half_square);
}
