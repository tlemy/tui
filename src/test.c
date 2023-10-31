#include <CUnit/Basic.h>
#include "../include/Screen.h"
#include "../include/Logger.h"
#include "../include/common.h"

void try_command_screen(void);
void try_init_logs(void);
void try_write_log(void);

int main(int argc, char *argv[]) 
{
	CU_initialize_registry();

	CU_pSuite suite_screen = CU_add_suite("suite_screen", NULL, NULL);
	CU_pTest test_command_screen = CU_add_test(suite_screen, "test_command_screen", try_command_screen);
	
	CU_pSuite suite_logger = CU_add_suite("suite_logger", NULL, NULL);
	CU_pTest test_init_logs = CU_add_test(suite_logger, "test_init_logs", try_init_logs);
	CU_pTest test_write_log = CU_add_test(suite_logger, "test_write_log", try_write_log);

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
