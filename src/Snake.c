#include "../include/Snake.h"
#include "../include/common.h"

Snake *create_snake(Rect **rect, int len, Snake *prev)
{
        Snake *snake = (Snake *) malloc(sizeof (Snake));

        if (!snake)
        {
                perror("Could not create snake: ");
                return NULL;
        }

        snake->rect = rect;
	snake->len = len;
	snake->prev = prev;
	snake->i = prev ? prev->i + 1 : 0;

	return snake;
}

void free_snake(Snake *snake) 
{
	free(snake);
}

Snake *add_body(Snake *curr, Snake *new) 
{
	new->prev = curr;
	return new;
}
