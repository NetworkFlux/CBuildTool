#include "cbt.h"

cbt_t	*create_cbt(void)
{
	cbt_t	*new_cbt;
	char	buffer[PATH_LEN];

	if (!(new_cbt = calloc(1, sizeof(cbt_t))))
	{
		fprintf(stderr, "Failed to calloc() cbt_t.\n");
		return (NULL);
	}

	new_cbt->cwd = flx_newstr(getcwd(buffer, PATH_LEN));
	new_cbt->project_name = NULL;
	new_cbt->project_path = NULL;

	return (new_cbt);
}

void	destroy_cbt(cbt_t *cbt)
{
	if (cbt)
	{
		flx_destroy_str(cbt->cwd);
		flx_destroy_str(cbt->project_name);
		flx_destroy_str(cbt->project_path);

		free(cbt);
	}
}
