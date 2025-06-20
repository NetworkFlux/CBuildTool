#!/bin/bash

# Color and formatting definitions
RED='\033[0;31m'
GREEN='\033[0;32m'
BLUE='\033[0;34m'
NC='\033[0m' # No Color
BOLD=$(tput bold)
NORMAL=$(tput sgr0)

# Check for make command
if ! command -v make &> /dev/null; then
	echo -e "${RED}${BOLD}Error:${NORMAL} ${RED}make command not found. Please install 'make'.${NC}"
	exit 1
fi

# Check if Makefile exists
if [ ! -f "./Makefile" ]; then
	echo -e "${RED}${BOLD}Error:${NORMAL} ${RED}No Makefile found in the current directory. Cannot proceed.${NC}"
	exit 1
fi

# Copy the templates directory to /usr/local/share/CBuildTool
echo -e "${BLUE}Copying the templates directory to /usr/local/share/CBuildTool...${NC}"
sudo mkdir -p /usr/local/share/CBuildTool
sudo cp -r templates /usr/local/share/CBuildTool

# Use the make command to build the executable
echo -e "${BLUE}Building cbt...${NC}"
make

# Check if bin directory exists
if [ ! -d "./bin" ]; then
	echo -e "${RED}${BOLD}Error:${NORMAL} ${RED}No bin directory found. Cannot proceed.${NC}"
	exit 1
fi

# Move to the bin directory
cd bin

# Define the executable name
exec_name=cbt

# Define the source path in the current directory (bin)
source_path=./"$exec_name"

# Define the target path in /usr/local/bin
target_path=/usr/local/bin/"$exec_name"

# Check if the source executable exists
if [ -f "$source_path" ]; then
	# Move the executable
	echo -e "${BLUE}Moving ${BOLD}$exec_name${NORMAL} ${BLUE}to /usr/local/bin...${NC}"
	sudo mv "$source_path" "$target_path"

	# Make the executable... executable
	echo -e "${BLUE}Making ${BOLD}$exec_name${NORMAL} ${BLUE}executable...${NC}"
	sudo chmod +x "$target_path"

	echo -e "${GREEN}$exec_name is now available as a command.${NC}"
else
	echo -e "${RED}${BOLD}Error:${NORMAL} ${RED}Executable $exec_name not found in the bin directory.${NC}"
fi
