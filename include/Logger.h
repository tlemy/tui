#ifndef LOGGER_H
#define LOGGER_H

#include <stdio.h>

FILE *init_logs(char *name); 

int write_log(FILE *logs, char *log); 

#endif /* Logger.h */
