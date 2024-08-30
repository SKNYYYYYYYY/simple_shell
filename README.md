Simple Shell Project

Description

This project is a simple shell, mimicking the functionality of the standard Unix shell. It is designed to handle basic command execution, including the use of environment variables, path resolution, and built-in commands like cd and exit. The shell is implemented in C, adhering to strict coding standards and best practices, such as those outlined by the Betty style guide.

Features

    •	Command Execution: Supports execution of commands with and without arguments.
    •	Path Resolution: Resolves commands using both absolute and relative paths.
    •	Built-in Commands: Implements basic built-in commands, such as cd for changing directories and exit for terminating the shell.
    •	Environment Management: Handles environment variables, allowing the shell to execute commands in different environments.
    •	Error Handling: Provides meaningful error messages when commands cannot be found or executed.

Project Structure

    •	Modular Design: The code is organized into multiple files, each handling a specific aspect of the shell’s functionality, ensuring maintainability and scalability.
    •	Memory Management: Careful management of memory allocation and deallocation to avoid leaks.
    •	System Calls: Utilizes various system calls like fork, execve, wait, and chdir to execute commands and manage processes.

Usage

To compile the shell:
gcc -Wall -Werror -Wextra -pedantic \*.c -o hsh

To run the shell:
./hsh
