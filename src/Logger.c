#include "../include/Logger.h"
#include "../include/common.h"

FILE *init_logs(char *name) 
{
	FILE *logs = fopen(name, "w");

	if (!logs) 
	{
		exit(-1);
	}
	return logs;
}

int write_log(FILE *logs, char *log) 
{
	int res = fwrite(log, sizeof (char), strlen(log), logs);

	if (res <= 0) 
	{
		perror("Could not write log: ");
		return -1;
	}
	fflush(logs);
	return res;
}
