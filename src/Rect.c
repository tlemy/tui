#include "../include/Rect.h"
#include "../include/common.h"

Rect *create_rect(int x, int y, int r, int g, int b, char *str)
{
        Rect *rect = (Rect *) malloc(sizeof (Rect));

        if (!rect)
        {
                perror("Could not create_rect (rect): ");
                return NULL;
        }

        rect->x = x;
        rect->y = y;
	rect->r = r;
	rect->g = g;
	rect->b = b;
        rect->str = (char *) malloc (sizeof (char) * (strlen(str) + 1));

        if (!rect->str)
        {
                perror("Could not create_rect (rect->str): ");
                return NULL;
        }

	char *res = strcpy(rect->str, str);

        if (strlen(res) != strlen(str))
        {
                perror("Could not create_rect (strcpy): " );
                return NULL;
        }

        return rect;
}

void free_rect(Rect *rect)
{
        free(rect->str);
        free(rect);
}

void free_multiple_rect(int len, Rect **rect) 
{
	for (int i = 0; i < len; i++) 
	{
		free_rect(rect[i]);
	}
}

int draw_rect(Rect *rect) 
{
	int res = printf("\033[%d;%dH\033[38;2;%d;%d;%dm%s\033[0m", rect->y, rect->x, rect->r, rect->g, rect->b, rect->str);
	return res;
}

int draw_multiple_rect(int len, Rect **rect) 
{
	int len_printed = 0;
	for (int i = 0; i < len; i++) 
	{
		len_printed += draw_rect(rect[i]);
	}
	return len_printed;
}

void move_rect_by(int x, int y, Rect *rect) 
{
	rect->x += x;
	rect->y += y;
}

void move_multiple_rect_by(int x, int y, int len, Rect **rect) 
{
	for (int i = 0; i < len; i++) 
	{
		rect[i]->x += x;
		rect[i]->y += y;
	}
}
