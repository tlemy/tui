#ifndef SNAKE_H
#define SNAKE_H

#include "Rect.h"
#include "Control.h"

typedef enum
{
        UP,
        DOWN,
        LEFT,
	RIGHT,
	BORDER,
} Direction;

typedef struct Snake
{
	int i;
	int len;
	int mov_x;
	int mov_y;
	Rect **rects;
	struct Snake *prev;
	Direction dir;
} Snake;

Snake *create_snake(Rect **rects, int len, Snake *prev, Direction dir, int mov_x, int mov_y);

void free_snake(Snake *snake_tail);

int update_body(Snake *snake);

Snake *add_body(Snake *curr, Snake *new);

int control_snake(Snake *snake, int inc_x, int dec_x, int inc_y, int dec_y);

int check_border_collision_snake(Snake *snake_head, int w, int h, int width_square, int heigth_square);

void draw_and_move_snake(Snake *snake_head, Snake *snake, int w, int h, int width_square, int heigth_square);

int check_collision_with_apple(Snake *snake, Snake *apple, int width_square, int heigth_square);

Snake *add_to_tail_snake(Snake *snake_tail, int width_square, int height_square);

#endif /* Snake.h */
