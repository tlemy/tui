#include "../include/Screen.h"
#include "../include/Logger.h"
#include "../include/Snake.h"
#include "../include/Control.h"
#include "../include/Random.h"
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

	int r = 255;
	int g = 255;
	int b = 255;

	int millisecs = 100;

	Rect *top_head = create_rect(init_x, init_y, 0, g, 0, half_square);
	Rect *bottom_head = create_rect(init_x, init_y + 1, 0, g, 0, half_square);
	Rect *top_apple = create_rect(w / 2, init_y, r, 0, 0, half_square);
        Rect *bottom_apple = create_rect(w / 2, init_y + 1, r, 0, 0, half_square);

	Rect **head = (Rect **) malloc(sizeof (Rect *) * 2);
	head[0] = top_head;
	head[1] = bottom_head;

	Rect **apple = (Rect **) malloc(sizeof (Rect *) * 2);
	apple[0] = top_apple;
	apple[1] = bottom_apple;

	Snake *snake_head = create_snake(head, 2, NULL, LEFT, dec_x, 0);
	Snake *snake_apple = create_snake(apple, 2, NULL, BORDER, 0, 0);

	Snake *snake_tail = snake_head;

	for (int i = 1; i < 3; i++) 
	{
		snake_tail = add_to_tail_snake(snake_tail, width_square, heigth_square);
	}

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
		if (check_collision_with_apple(snake_head, snake_apple, width_square, heigth_square)) 
		{
			int rand_x = get_rand_int_in_range(1, w - width_square);
			int rand_y = get_rand_int_in_range(4, h - heigth_square);
			
			char log[20];
			sprintf(log, "new position: x=%d, y=%d\n", rand_x, rand_y);
			write_log(logs, &log);

			sprintf(log, "color: %d\n", snake_tail->rects[0]->g);
                        write_log(logs, &log);

			for (int i = 0; i < snake_apple->len; i++) 
			{
				snake_apple->rects[i]->x = rand_x;
				snake_apple->rects[i]->y = rand_y + i;
			}
			snake_tail = add_to_tail_snake(snake_tail, width_square, heigth_square);	
		}
		if (!check_border_collision_snake(snake_head, w, h, width_square, heigth_square)) 
		{
			move_multiple_rect_by(snake_head->mov_x, snake_head->mov_y, snake_head->len, snake_head->rects);
		}
		else 
		{
			snake_head->dir = BORDER;
		}
		
		char log[20];
                sprintf(log, "snake: x=%d, y=%d\n", snake_head->rects[0]->x, snake_head->rects[0]->y);
                write_log(logs, &log);
			
		draw_multiple_rect(snake_apple->len, snake_apple->rects);	
		draw_and_move_snake(snake_head, snake_tail, w, h, width_square, heigth_square);
		save_screen();
                usleep(millisecs * 1000);
	}
	
	free_snake(snake_tail);
	free_snake(snake_apple);
	free(half_square);
}
