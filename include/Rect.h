#ifndef RECT_H
#define RECT_H


typedef struct Rect
{
	int y;
	int x;
	int r;
	int g;
	int b;
	char *str;
} Rect;

Rect *create_rect(int x, int y, int r, int g, int b, char *str); 

void free_rect(Rect *rect);

void free_multiple_rect(int len, Rect **rect);

int draw_rect(Rect *rect);

int draw_multiple_rect(int len, Rect **rect);

void move_rect_by(int x, int y, Rect *rect);

void move_multiple_rect_by(int x, int y, int len, Rect **rect);

#endif /* Rect.h */
