## This project is in a draft, non-final state. Will be updated once done

# MiniShell

## Overview
MiniShell is a simple, yet powerful shell that mimics the functionality of bash. This shell is designed to handle a variety of common shell tasks and commands, making it a useful tool for both beginners and experienced users. This project is developed as part of the School 42 curriculum, offering a challenging and educational experience in system programming and shell development.

## Features

### Command Prompt
- **Prompt Display**: MiniShell displays a prompt when waiting for a new command, allowing users to easily see when the shell is ready for input.

### Command Execution
- **Executable Search and Launch**: MiniShell searches for and launches the correct executable based on the `PATH` environment variable or by using a relative or absolute path.

### Signal Handling
- **Minimal Global Variables**: Only one global variable is used to indicate a received signal, ensuring that signal handlers do not access main data structures.

### Quote Handling
- **Single Quotes (`'`)**: Prevents the shell from interpreting metacharacters within the quoted sequence.
- **Double Quotes (`"`)**: Prevents the shell from interpreting metacharacters within the quoted sequence, except for the dollar sign (`$`).

### Redirections
- **Input Redirection (`<`)**: Redirects input.
- **Output Redirection (`>`)**: Redirects output.
- **Here Document (`<<`)**: Reads input until a line containing the specified delimiter is seen, without updating history.
- **Append Output Redirection (`>>`)**: Redirects output in append mode.

### Pipes
- **Pipes (`|`)**: Connects the output of each command in the pipeline to the input of the next command via a pipe.

### Environment Variables
- **Variable Expansion (`$VAR`)**: Expands to the value of the environment variable.
- **Exit Status (`$?`)**: Expands to the exit status of the most recently executed foreground pipeline.

### Signal Handling
- **Ctrl-C**: Displays a new prompt on a new line.
- **Ctrl-D**: Exits the shell.
- **Ctrl-\**: Does nothing in interactive mode.

### Built-in Commands
- **echo**: Prints text to the terminal, with support for the `-n` option.
- **cd**: Changes the current directory, accepting only relative or absolute paths.
- **pwd**: Prints the current working directory.
- **export**: Sets environment variables.
- **unset**: Unsets environment variables.
- **env**: Prints the current environment.
- **exit**: Exits the shell.

## Memory Management
- **No Memory Leaks**: The `readline()` function may cause memory leaks, but MiniShell ensures that there are no memory leaks in the user-written code.

## Getting Started
1. Clone the repository:
   ```bash
   git clone https://github.com/yourusername/minishell.git
2. Navigate to the project directory:
   ```bash
   cd minishell
3. Build the project:
   ```bash
   make
4. Run the shell:
   ```bash
   ./minishell

Enjoy!
