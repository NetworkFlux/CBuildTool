# Root Makefile
MAKEFLAGS += --no-print-directory

EXEC = cbt

CC = gcc
CFLAGS = -Wall -Wextra -Werror
RM = rm -rf

BIN_DIR = bin
OBJ_DIR = obj
INC_DIR = include

FLUX_DIR = fluxlib
FLUX_INC = $(FLUX_DIR)/include
FLUX_LIB = $(FLUX_DIR)/libflux.a

SRC_DIR = src
SRC = $(shell find $(SRC_DIR) -type f -name "*.c")
OBJ = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRC))

INCLUDES = -I$(INC_DIR) -I$(FLUX_INC)

all: $(FLUX_LIB) $(EXEC)

$(EXEC): $(OBJ)
	@echo "🔧 Linking final executable..."
	@$(CC) $(CFLAGS) $(OBJ) -L$(FLUX_DIR) -lflux $(INCLUDES) -o $(EXEC)
	@mkdir -p $(BIN_DIR)
	@mv $(EXEC) $(BIN_DIR)/$(EXEC)
	@echo "✅ Built executable moved to $(BIN_DIR)/$(EXEC)"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@echo "🧩 Compiling $< -> $@"
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(FLUX_LIB):
	@echo "📦 Building fluxlib static library..."
	@$(MAKE) -C $(FLUX_DIR)

clean:
	@echo " �Cleaning object files..."
	@$(RM) $(OBJ_DIR)
	@$(MAKE) -C $(FLUX_DIR) clean

fclean: clean
	@echo " �Cleaning binary and libraries..."
	@$(RM) $(BIN_DIR)
	@$(MAKE) -C $(FLUX_DIR) fclean

re: fclean all

.PHONY: all clean fclean re