#include <CUnit/Basic.h>
#include "../include/Screen.h"
#include "../include/Logger.h"
#include "../include/Rect.h"
#include "../include/common.h"

void try_command_screen(void);
void try_init_logs(void);
void try_write_log(void);
void try_create_rect(void);
void try_draw_rect(void);
void try_draw_multiple_rect(void);
void try_move_rect_by(void);
void try_move_multiple_rect_by(void);

int main(int argc, char *argv[]) 
{
	CU_initialize_registry();

	CU_pSuite suite_screen = CU_add_suite("suite_screen", NULL, NULL);
        CU_pTest test_command_screen = CU_add_test(suite_screen, "test_command_screen", try_command_screen);

	CU_pSuite suite_logger = CU_add_suite("suite_logger", NULL, NULL);
	CU_pTest test_init_logs = CU_add_test(suite_logger, "test_init_logs", try_init_logs);
	CU_pTest test_write_log = CU_add_test(suite_logger, "test_write_log", try_write_log);
	
	CU_pSuite suite_rect = CU_add_suite("suite_rect", NULL, NULL);
	CU_pTest test_create_rect = CU_add_test(suite_rect, "test_create_rect", try_create_rect);
	CU_pTest test_draw_rect = CU_add_test(suite_rect, "test_draw_rect", try_draw_rect);
	CU_pTest test_draw_multiple_rect = CU_add_test(suite_rect, "test_draw_multiple_rect", try_draw_multiple_rect);
	CU_pTest test_move_rect_by = CU_add_test(suite_rect, "test_move_rect_by", try_move_rect_by);
	CU_pTest test_move_multiple_rect_by = CU_add_test(suite_rect, "test_move_multiple_rect_by", try_move_multiple_rect_by);

	CU_basic_run_tests();
	CU_cleanup_registry();
}

void try_command_screen(void) 
{
	int res = command_screen(CLEAR_SCREEN);
	CU_ASSERT_EQUAL(res, 0);
}

void try_init_logs(void) 
{
	char fname[] = "./build/test_logs.txt";

	FILE *logs = init_logs(fname);

	CU_ASSERT_PTR_NOT_NULL(logs);

	fclose(logs);
}

void try_write_log(void) 
{
	char fname[] = "./build/test_logs.txt";
	FILE *logs = init_logs(fname);
	char log[] = "Hello, World!\n\0";

	int res = write_log(logs, log);

	CU_ASSERT_EQUAL(res, strlen(log));

	fclose(logs);
}

void try_create_rect(void) 
{
	char str[] = "hello";
	Rect *rect = create_rect(0, 1, 2, 3, 4, &str);

	CU_ASSERT_PTR_NOT_NULL(rect);
	CU_ASSERT_EQUAL(strcmp(rect->str, str), 0);

	free_rect(rect);
}

void try_draw_rect(void) 
{
	char str[] = "hello\n";
        Rect *rect = create_rect(0, 101, 0, 255, 0, &str);

        int res = draw_rect(rect);

	CU_ASSERT_TRUE(res > strlen(str));

        free_rect(rect);
}

void try_draw_multiple_rect(void) 
{
	char str[] = "hello\n";
        Rect *rect1 = create_rect(0, 102, 0, 255, 255, &str);
	Rect *rect2 = create_rect(0, 103, 0, 0, 255, &str);
	int len = 2;
	Rect *image[2] = {
		rect1, rect2
	}; 

        int res = draw_multiple_rect(len, image);

        CU_ASSERT_TRUE(res > strlen(str) * len);

        free_multiple_rect(len, image);
}

void try_move_rect_by(void) 
{
	char str[] = "hello";
        Rect *rect = create_rect(1, 1, 2, 3, 4, &str);

        move_rect_by(1, 1, rect);

        CU_ASSERT_EQUAL(rect->x, 2);
	CU_ASSERT_EQUAL(rect->y, 2);

        free_rect(rect);
}

void try_move_multiple_rect_by(void) 
{
	char str[] = "hello";
	Rect *rect1 = create_rect(1, 102, 0, 255, 255, &str);
        Rect *rect2 = create_rect(1, 103, 0, 0, 255, &str);
        int len = 2;
        Rect *image[2] = {
                rect1, rect2
        };

        move_multiple_rect_by(1, 1, len, image);

        CU_ASSERT_EQUAL(image[0]->x, 2);
	CU_ASSERT_EQUAL(image[1]->x, 2);

	free_multiple_rect(len, image);
}
