#include "c_builder.h"

int	fill_main(int main_fd, char *pro_name)
{
	char	main_content[MAX_CONTENT];

	sprintf(main_content, "#include \"%s.h\"\n\nint\tmain(int argc, char **argv)\n{\n\t(void)argc;\n\t(void)argv;\n\tprintf(\"Hello World!\\n\");\n\treturn (0);\n}\n", pro_name);
	if (write(main_fd, main_content, strlen(main_content)) < 0)
		err_n_die("write() failed");
	return (0);
}

int	fill_include(int include_fd)
{
	char	include_content[MAX_CONTENT];

	sprintf(include_content, "#pragma once\n\n#include <unistd.h>\n#include <stdlib.h>\n#include <stdio.h>\n\n");
	if (write(include_fd, include_content, strlen(include_content)) < 0)
		err_n_die("write() failed");

	return (0);
}

int	fill_makefile(int makefile_fd, char *pro_name)
{
	char	makefile_content[MAX_CONTENT];

	sprintf(makefile_content, "EXEC = %s\n\nCC = gcc\nCFLAGS = -Wall -Wextra -Werror\nRM = rm -rf\n\nBIN_DIR = bin\nINC_DIR = include\nSRC_DIR = src\nOBJ_DIR = obj\n# LIB_DIR = lib_directory\n\nSRC = $(shell find $(SRC_DIR) -type f -name \"*.c\")\nOBJ = $(patsubst $(SRC_DIR)/%%.c, $(OBJ_DIR)/%%.o, $(SRC))\n\n# LIB = $(LIB_DIR)/your_lib.a\n# LIBS = -L$(LIB_DIR) -lLib -lLib -lLib -lLib (if you have multiple libs)\n\nall: $(EXEC)\n\n$(EXEC): $(OBJ) $(LIB)\n\t@$(CC) $(CFLAGS) $(OBJ) -I $(INC_DIR) $(LIBS) -o $@\n\t@mkdir -p $(BIN_DIR)\n\t@mv $(EXEC) $(BIN_DIR)/$(EXEC)\n\n$(OBJ_DIR)/%%.o: $(SRC_DIR)/%%.c\n\t@mkdir -p $(dir $@)\n\t@$(CC) $(CFLAGS) -I $(INC_DIR) -c $< -o $@\n\n#$(LIB):\n#\t@$(MAKE) -C $(LIB_DIR)	(if a lib needs to be compiled)\n\nclean:\n\t@$(RM) $(OBJ_DIR)\n\nfclean: clean\n\t@$(RM) $(BIN_DIR)\n\nre: fclean all\n\n.PHONY: all clean fclean re\n", pro_name);
	if (write(makefile_fd, makefile_content, strlen(makefile_content)) < 0)
		err_n_die("write() failed");
	return (0);
}

int	fill_project(char *pro_path, char *pro_name)
{
	char	temp_path[MAX_PATH];
	int		main_fd, include_fd, makefile_fd;

	sprintf(temp_path, "%s/src", pro_path);
	if (mkdir(temp_path, 0777) < 0)
		err_n_die("mkdir() failed");
	sprintf(temp_path, "%s/src/main.c", pro_path);
	if ((main_fd = open(temp_path, O_CREAT | O_WRONLY, 0777)) < 0)
		err_n_die("open() failed");
	fill_main(main_fd, pro_name);
	sprintf(temp_path, "%s/include", pro_path);
	if (mkdir(temp_path, 0777) < 0)
		err_n_die("mkdir() failed");
	sprintf(temp_path, "%s/include/%s.h", pro_path, pro_name);
	if ((include_fd = open(temp_path, O_CREAT | O_WRONLY, 0777)) < 0)
		err_n_die("open() failed");
	fill_include(include_fd);
	sprintf(temp_path, "%s/Makefile", pro_path);
	if ((makefile_fd = open(temp_path, O_CREAT | O_WRONLY, 0777)) < 0)
		err_n_die("open() failed");
	fill_makefile(makefile_fd, pro_name);
	return (0);
}

int	main(int argc, char **argv)
{
	char	pro_path[MAX_PATH];
	char	pro_name[MAX_NAME];
	char	*cwd;

	if (argc != 1)
		err_n_die("Usage: %s", argv[0]);

	if (!(cwd = getcwd(pro_path, MAX_PATH)))
		err_n_die("getcwd() failed");
	
	printf("Enter project name: ");
	scanf("%s", pro_name);

	sprintf(pro_path, "%s/%s", cwd, pro_name);

	printf("Creating project ...\n");

	if (mkdir(pro_name, 0777) < 0)
		err_n_die("mkdir() failed");

	printf("Project created successfully at %s\n", pro_path);

	fill_project(pro_path, pro_name);

	return (0);
}
