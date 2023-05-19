#pragma once

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <stdarg.h>
#include <string.h>
#include <sys/stat.h>
#include <fcntl.h>

#define MAX_PATH 1024
#define MAX_NAME 256
#define MAX_CONTENT 4096

// Error handling
void	err_n_die(const char *msg, ...);