#include "c_builder.h"

const char	*languages[] = {
	"C",
	"C++"
};

int	select_option(const char *options[], const char *question)
{
	char	choice[MAX_CHOICE];

	printf("%s\n", question);
	for (int i = 0; options[i]; i++)
		printf("%d. %s\n", i + 1, options[i]);
	printf("Enter your choice: ");
	scanf("%s", choice);
	while (1)
	{
		for (int i = 0; options[i]; i++)
		{
			if (!strcmp(choice, options[i]))
				return (i);
		}
		printf("Invalid choice, try again: ");
		scanf("%s", choice);
	}
	return (-1);
}

int	main(int argc, char **argv)
{
	char	pro_path[MAX_PATH];
	char	pro_name[MAX_NAME];
	int		language;
	char	*cwd;

	if (argc != 1)
		err_n_die("Usage: %s", argv[0]);

	if (!(cwd = getcwd(pro_path, MAX_PATH)))
		err_n_die("getcwd() failed");
	
	printf(COLOR_CYAN "Enter project name: " COLOR_RESET);
	scanf("%s", pro_name);
	if (pro_name[0] == '\0')
		err_n_die("Project name cannot be empty");

	language = select_option(languages, "Select language:");

	sprintf(pro_path, "%s/%s", cwd, pro_name);

	printf(COLOR_GREEN "Creating project ...\n" COLOR_RESET);

	if (mkdir(pro_name, 0777) < 0)
		err_n_die("mkdir() failed");

	printf(COLOR_GREEN "Project created successfully at %s\n" COLOR_RESET, pro_path);

	fill_project(pro_path, pro_name, language);

	return (0);
}
