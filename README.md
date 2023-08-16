 A Minimalistic Unix Shell

### ⚠️ Introduction
Minishell is a simple, lightweight implementation of a Unix shell in C, designed to provide a basic command-line interface for users to interact with the operating system. It serves as a learning exercise for understanding fundamental concepts of operating systems, process management, and command execution.

### ⚠️ Features
Basic command execution: Run simple commands, including built-in shell commands and external executable files.
Built-in commands: Implement a subset of common shell built-in commands such as cd, echo, and exit.
Command line parsing: Parse user input to extract command and arguments, handling whitespace and special characters.
Process management: Create and manage processes using fork and exec, handle background processes, and support foreground execution.
Signal handling: Handle signals like Ctrl+C (SIGINT) gracefully.
Simple error handling: Display informative error messages for user input and command execution errors.
Redirection (optional): Support basic input/output redirection for commands using < and >.
Getting Started
Clone the Minishell repository from GitHub.
Compile the code using a C compiler (e.g., GCC) by running the appropriate make command.
Run the compiled executable to launch the Minishell.
Enter commands and explore the basic shell functionality.

### ⚠️ Usage

make the files:
```make```
Start Minishell by running the executable.
```./minishell```
Enter commands as you would in a regular shell (e.g., ls, echo, cd, etc.).
Use built-in commands by typing their names (e.g., cd to change the current directory).
Use Ctrl+C to interrupt running commands or terminate the shell.
Use input/output redirection (if implemented) with < and >.

### ⚠️ Example
Here's a simple example of using Minishell:

### ⚠️ Launch Minishell.
Enter the command ls to list files in the current directory.
Enter the command echo "Hello, Minishell!" to display the given message.
Use cd to change the current directory.
Enter exit to exit Minishell.
##Limitations
Minishell is a minimalistic implementation, and it may lack advanced features found in full-fledged shells (e.g., scripting, advanced input/output redirection, environment variable management, etc.).

### ⚠️ Contribution.
Contributions to Minishell are welcome. Feel free to fork the repository, make improvements, and submit pull requests.


### ⚠️ Credits
Minishell was developed as part of a learning project by  BRAHIM_BENIDAR.
