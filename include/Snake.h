#include "Rect.h"

typedef enum
{
        UP,
        DOWN,
        LEFT,
	RIGHT
} Direction;

typedef struct Snake
{
	int i;
	int len;
	Rect **rect;
	struct Snake *prev;
} Snake;

Snake *create_snake(Rect **rect, int len, Snake *prev);

void free_snake(Snake *snake);

int update_body(Snake *snake);

Snake *add_body(Snake *curr, Snake *new);
