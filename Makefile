EXEC = cbt

CC = gcc
CFLAGS = -Wall -Wextra -Werror
RM = rm -rf

BIN_DIR = bin
INC_DIR = include
SRC_DIR = src
OBJ_DIR = obj
# LIB_DIR = lib_directory

SRC = $(shell find $(SRC_DIR) -type f -name "*.c")
OBJ = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRC))

# LIB = $(LIB_DIR)/your_lib.a
LIBS = -lncurses

all: $(EXEC)

$(EXEC): $(OBJ) $(LIB)
	@$(CC) $(CFLAGS) $(OBJ) -I $(INC_DIR) $(LIBS) -o $@
	@mkdir -p $(BIN_DIR)
	@mv $(EXEC) $(BIN_DIR)/$(EXEC)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -I $(INC_DIR) -c $< -o $@

#$(LIB):
#	@$(MAKE) -C $(LIB_DIR)	(if a lib needs to be compiled)

clean:
	@$(RM) $(OBJ_DIR)

fclean: clean
	@$(RM) $(BIN_DIR)

re: fclean all
