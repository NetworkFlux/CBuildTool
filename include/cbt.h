#ifndef CBT_H
# define CBT_H

#include <stdio.h>
#include <stdlib.h>

#include "cbt_portability.h"

#define PATH_SIZE 512

typedef struct {
    char    *user_path;
    int     custom;
} Path;

Path    *init_path(void);

#endif  // CBT_H