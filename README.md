# C/C++ Build Tool

## Introduction

This tool is designed to streamline the process of setting up new C/C++ projects by automatically generating the basic necessary files for you. The architecture of the generated project includes three root folders: `src`, `include`, and `obj` (which is created at compilation). It also includes a ready-to-go `Makefile`. The `src` folder contains a basic `main.c/cpp` file, while the `include` folder holds a basic `.h/hpp` file.

With just one command, you can set up an entire C/C++ project. The included Bash script generates an executable that is moved to the `/usr/local/bin` folder, enabling you to initiate new projects from anywhere on your machine.

## Installation

To use the tool, follow the steps below:

1. Clone this repository to your local machine.

```bash
git clone https://github.com/NetworkFlux/CBuildTool.git
```

2. Navigate into the cloned repository.

```bash
cd CBuildTool
```

3. Execute the installation script.

```bash
bash install_cbt.sh
```

Note: The installation script requires `sudo` privileges as it needs to move files to `/usr/local/bin`. If you don't have sudo privileges, you can simply run the make command to generate the executable and launch it from its current location.

Another Note: The generated files will match the files in the `templates` folder inside the repo. You can modify these templates as you want, and the CBuildTool will create projects based on your templates. Note that the `install_cbt.sh` script will create a new folder in `/usr/local/share` that will contain the `templates` folder. If you want to update them you must update them there. And if you don't have sudo privileges, update those in this repo.

## Usage

Once installed, you can create a new C/C++ project using the following command:

```bash
cbt
```

You will be prompted to enter a project name and select your desired language, and a project with the aforementioned architecture will be generated, ready to go.

Feel free to report any bugs or possible imporvements.

## Notes

For my fellow 42 students, I would highly recommend taking a closer look at the actual code, as the generated project does not comply with the Norminette. I can't just hand it to you 🤙
