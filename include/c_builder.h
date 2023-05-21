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
#define MAX_CHOICE 32

// define some color codes
#define COLOR_RED		"\x1b[31m"
#define COLOR_GREEN		"\x1b[32m"
#define COLOR_YELLOW	"\x1b[33m"
#define COLOR_BLUE		"\x1b[34m"
#define COLOR_MAGENTA	"\x1b[35m"
#define COLOR_CYAN		"\x1b[36m"
#define COLOR_RESET		"\x1b[0m"

// File handling
int fill_project(char *pro_path, char *pro_name, int lang);
void copy_file_content(FILE *fd, const char *input_file, const char *project_name, int lang);

// Error handling
void	err_n_die(const char *msg, ...);