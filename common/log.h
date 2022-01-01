#ifndef LOG_H_
#define LOG_H_

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

void note(const char *message);
void fatal(const char *message);
void warning(const char *message);

#endif
