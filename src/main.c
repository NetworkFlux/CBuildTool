#include "cbt.h"

int main(int argc, char **argv)
{
	cbt_t	*cbt;

	cbt = create_cbt();
	if (argc == 2)
	{
		if (flx_strcmp(argv[1], "init"))
		{
			cbt->project_path = flx_newstr(cbt->cwd->str);
			cbt->project_name = flx_str_path_tail(cbt->project_path, 1);
			printf("Initializing C project in the current directory.\n");
			printf("Current working directory: %s\n", cbt->cwd->str);
			printf("Project path: %s\n", cbt->project_path->str);
			printf("Project name: %s\n", cbt->project_name->str);
		}
	}

	destroy_cbt(cbt);
    return (0);
}
