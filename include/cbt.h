#ifndef CBT_H
# define CBT_H

# include <stdio.h>
# include <unistd.h>
# include <sys/stat.h>
# include <errno.h>
# include <fcntl.h>
# include "flux.h"

# define SRC_DIR "src"
# define INCLUDE_DIR "include"
# define MAIN_TEMPLATE "/usr/local/share/CBuildTool/templates/default/main.c.cbt"
# define DOTH_TEMPLATE "/usr/local/share/CBuildTool/templates/default/project.h.cbt"
# define MAKEFILE_TEMPLATE "/usr/local/share/CBuildTool/templates/default/Makefile.cbt"

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
