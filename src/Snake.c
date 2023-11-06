#include "../include/Snake.h"
#include "../include/common.h"

Snake *create_snake(Rect **rects, int len, Snake *prev, Direction dir, int mov_x, int mov_y)
{
        Snake *snake = (Snake *) malloc(sizeof (Snake));

        if (!snake)
        {
                perror("Could not create snake: ");
                return NULL;
        }

        snake->rects = rects;
	snake->len = len;
	snake->prev = prev;
	snake->i = prev ? prev->i + 1 : 0;
	snake->dir = dir;
	snake->mov_x = mov_x;
	snake->mov_y = mov_y;

	return snake;
}

void free_snake(Snake *snake_tail) 
{
	Snake *curr;

        while (snake_tail)
        {
                curr = snake_tail;
                snake_tail = snake_tail->prev;

                for (int i = 0; i < curr->len; i++)
                {
                        free(curr->rects[i]);
                }
		free(curr->rects);
                free(curr);
        }
}

Snake *add_body(Snake *curr, Snake *new) 
{
	new->prev = curr;
	return new;
}

int control_snake(Snake *snake_head, int inc_x, int dec_x, int inc_y, int dec_y) 
{
	char *c = getch();

        if (c == 'q')
        {
        	return 1;;
        }
        else if (c == 'w' && snake_head->dir != DOWN)
        {
        	snake_head->dir = UP;
                snake_head->mov_x = 0;
                snake_head->mov_y = dec_y;
        }
        else if (c == 's' && snake_head->dir != UP)
        {
        	snake_head->dir = DOWN;
                snake_head->mov_x = 0;
                snake_head->mov_y = inc_y;
        }
        else if (c == 'a' && snake_head->dir != RIGHT)
        {
        	snake_head->dir = LEFT;
                snake_head->mov_x = dec_x;
                snake_head->mov_y = 0;
        }
        else if (c == 'd' && snake_head->dir != LEFT)
        {
                snake_head->dir = RIGHT;
                snake_head->mov_x = inc_x;
        	snake_head->mov_y = 0;
	}
	return 0;
}

int check_border_collision_snake(Snake *snake_head, int w, int h, int width_square, int heigth_square) 
{
	int is_left_border_ok = snake_head->rects[0]->x + snake_head->mov_x >= 1;
        int is_right_border_ok = snake_head->rects[0]->x + snake_head->mov_x <= w - width_square;
        int is_top_border_ok = snake_head->rects[0]->y + snake_head->mov_y >= 1;
        int is_bottom_border_ok = snake_head->rects[0]->y + snake_head->mov_y <= h - heigth_square;
	
	return !(is_left_border_ok && is_right_border_ok && is_top_border_ok && is_bottom_border_ok);
}

void draw_and_move_snake(Snake *snake_head, Snake *snake, int w, int h, int width_square, int heigth_square) 
{
	while (snake)
        {
        	if (snake->rects[0]->x + width_square <= w && snake->rects[0]->y + heigth_square <= h)
                {
                	draw_multiple_rect(snake->len, snake->rects);
                }
                if (snake->prev && snake_head->dir != BORDER)
                {
                	for (int i = 0; i < snake->len; i++)
                        {
                        	snake->rects[i]->x = snake->prev->rects[i]->x;
                               	snake->rects[i]->y = snake->prev->rects[i]->y;
                        }
                }
                snake = snake->prev;
        }
}

int check_collision_with_apple(Snake *snake, Snake *apple, int width_square, int heigth_square) 
{
	int left_border = apple->rects[0]->x;
	int right_border = apple->rects[0]->x + width_square;
	int top_border = apple->rects[0]->y;
        int bottom_border = apple->rects[0]->y + heigth_square;

       	int is_in_x = (left_border <= snake->rects[0]->x && snake->rects[0]->x <= right_border) 
	|| (left_border <= snake->rects[0]->x + width_square && snake->rects[0]->x + width_square <= right_border);
	
	int is_in_y = (top_border <= snake->rects[0]->y && snake->rects[0]->y <= bottom_border)
	|| (top_border <= snake->rects[0]->y + heigth_square && snake->rects[0]->y + heigth_square <= bottom_border);

	return is_in_x && is_in_y;	
}

Snake *add_to_tail_snake(Snake *snake_tail, int width_square, int height_square) 
{
	int x = snake_tail->rects[0]->x;
	int y = snake_tail->rects[0]->y;

	if (snake_tail->dir == LEFT) 
	{
		x += width_square;
	}
	else if (snake_tail->dir == RIGHT) 
	{
		x -= width_square;
	}
	else if (snake_tail->dir == UP) 
	{
		y += height_square;
	}
	else if (snake_tail->dir == DOWN) 
	{
		y -= height_square;
	}

	Rect *top_tail = create_rect(x, y, 0, snake_tail->rects[0]->g - 1, 0, snake_tail->rects[0]->str);
        Rect *bottom_tail = create_rect(x, y + 1, 0, snake_tail->rects[0]->g - 1, 0, snake_tail->rects[0]->str);
	Rect **tail = (Rect **) malloc(sizeof (Rect *) * 2);
	tail[0] = top_tail;
	tail[1] = bottom_tail;
	Snake *new_snake_tail = create_snake(tail, snake_tail->len, snake_tail, snake_tail->dir, 0, 0);
	
	return new_snake_tail;
}
