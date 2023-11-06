#include "../include/Random.h"
#include "../include/common.h"

int get_rand_int_in_range(int min, int max) 
{
	return rand() % (max + 1 - min) + min;
}
