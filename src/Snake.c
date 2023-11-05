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

int check_collision_with_snake(Snake *main_snake, Snake *other_snake, int width_square, int heigth_square) 
{
	int left_border = other_snake->rects[0]->x;
	int right_border = other_snake->rects[0]->x + width_square;
	int top_border = other_snake->rects[0]->y;
        int bottom_border = other_snake->rects[0]->y + heigth_square;

       	int is_in_x = (left_border < main_snake->rects[0]->x && main_snake->rects[0]->x < right_border) 
	|| (left_border < main_snake->rects[0]->x + width_square && main_snake->rects[0]->x + width_square < right_border);
	
	int is_in_y = (top_border < main_snake->rects[0]->y && main_snake->rects[0]->y < bottom_border)
	|| (top_border == main_snake->rects[0]->y && main_snake->rects[0]->y + heigth_square == bottom_border);

	return is_in_x && is_in_y;	
}
