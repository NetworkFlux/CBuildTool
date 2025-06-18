#ifndef CBT_H
# define CBT_H

# include <stdio.h>
# include <unistd.h>
# include "flux.h"

# define PATH_LEN 1024

typedef struct
{
	flx_str	*cwd;
	flx_str	*project_name;
	flx_str	*project_path;
}	cbt_t;

cbt_t	*create_cbt(void);
void	destroy_cbt(cbt_t *cbt);

#endif  // CBT_H
