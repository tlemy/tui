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
	
	char str_square[] = "\u2588\u2588\u2588\u2588";
	char *square = (char *) malloc(sizeof (char) * strlen(str_square));
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
	int mov_x = dec_x;
        int mov_y = 0;
	int color = 240;
	char c = '\0';
	Direction dir = LEFT;
	Snake *snake;
	
	strcpy(square, str_square);

	Rect *top_head = create_rect(init_x, init_y, 0, color, 0, square);
	Rect *bottom_head = create_rect(init_x, init_y + 1, 0, color, 1, square);
	Rect *top_body = create_rect(init_x + width_square, init_y, 0, color, color, square);
	Rect *bottom_body = create_rect(init_x + width_square, init_y + 1, 0, color, color, square);
	Rect *top_tail = create_rect(init_x + width_square * 2, init_y, 0, 0, color, square);
	Rect *bottom_tail = create_rect(init_x + width_square * 2, init_y + 1, 0, 0, color, square);

	Rect *head[2] = { top_head, bottom_head };
	Rect *body[2] = { top_body, bottom_body };
	Rect *tail[2] = { top_tail, bottom_tail };

	Snake *snake_head = create_snake(head, 2, NULL);
	Snake *snake_body = create_snake(body, 2, snake_head);
	Snake *snake_tail = create_snake(tail, 2, snake_body);

	command_screen(CLEAR_SCREEN);
        command_screen(HIDE_CURSOR);
	init_control(); // IMPORTANT: getch won't work without this
	
	for (;;) 
	{
		command_screen(CLEAR_SCREEN);
                command_screen(ERASE_SCROLLBACK_BUFFER);

		// controls
		c = getch();

		if (c == 'q')
                {
                        break;
                }
		else if (c == 'w' && dir != DOWN) 
		{
			dir = UP;
			mov_x = 0;
			mov_y = dec_y; 
		}
		else if (c == 's' && dir != UP)  
		{
			dir = DOWN;
			mov_x = 0;
			mov_y = inc_y;
		}
		else if (c == 'a' && dir != RIGHT) 
		{
			dir = LEFT;
			mov_x = dec_x;
			mov_y = 0;
		}
		else if (c == 'd' && dir != LEFT) 
		{
			dir = RIGHT;
			mov_x = inc_x;
			mov_y = 0;
		}
		
		// draw and move snake from tail to head
		snake = snake_tail;
		bool is_left_border_ok = snake_head->rect[0]->x + mov_x >= 1;
                bool is_right_border_ok = snake_head->rect[0]->x + mov_x <= w - width_square;
                bool is_top_border_ok = snake_head->rect[0]->y + mov_y >= 1;
                bool is_bottom_border_ok = snake_head->rect[0]->y + mov_y <= h - heigth_square;
		
		if (is_left_border_ok && is_right_border_ok && is_top_border_ok && is_bottom_border_ok) 
		{
			move_multiple_rect_by(mov_x, mov_y, snake_head->len, snake_head->rect);
		}

		while (snake)
		{
                	if (snake->rect[0]->x + width_square <= w && snake->rect[0]->y + heigth_square <= h) 
			{
				draw_multiple_rect(snake->len, snake->rect);
			}

                        if (snake->prev && is_left_border_ok && is_right_border_ok && is_top_border_ok && is_bottom_border_ok)
                        {
                        	for (int i = 0; i < snake->len; i++)
                                {
                                	snake->rect[i]->x = snake->prev->rect[i]->x;
                                       	snake->rect[i]->y = snake->prev->rect[i]->y;
                                }
                        }
                        snake = snake->prev;
                }
	
		save_screen();
                usleep(500 * 1000);
	}
	free(square);
	// free rects
}
