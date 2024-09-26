# minishell

*Minishell - As beautiful as a shell*

### Description

This project is about creating a fully functional shell from scratch, which should behave like bash, just with less features.
This was a group project consisting of [@frbeyer](https://github.com/frbeyer1) and [@me](https://github.com/mottjes/).

### Features

- **Executable Search**: Minishell can execute the appropriate executable with a relative and a absolute path

- **Signal Handling**: Only one global variable is used to indicate received signals. This maintains the integrity of our main data structures.

- **Ctrl-C, Ctrl-D, Ctrl-\ Handling**: The shell behaves like bash with respect to these keyboard shortcuts:
    - Ctrl-C: Displays a new prompt on a new line.
    - Ctrl-D: Exits the shell.
    - Ctrl-\\: No action taken.

- **Command History**

- **Quoting**: Minishell handles single quotes ('), preventing the interpretation of metacharacters within the quoted sequence. Double quotes (") do the same, except for the dollar sign ($).

- **Redirections**: The shell supports various redirections:
    - `<` redirects input.
    - `>` redirects output.
    - `<<` reads input until a specified delimiter, without updating history.
    - `>>` redirects output in append mode.

- **Pipes**: Our shell implements pipes (`|`), to get output from one command to the input of the next.

- **Environment Variables**: Minishell handles environment variables ($ followed by characters), expanding them to their corresponding values.

- **Exit Status**: `$?` expands to the exit status of the most recently executed foreground pipeline.

- **Built-in Commands**: Minishell supports the following built-in commands:
    - `echo` with the `-n` option
    - `cd` with relative or absolute paths
    - `pwd` with no options
    - `export` with no options
    - `unset` with no options
    - `env` with no options or arguments
    - `exit` with no options

For more detail read the [subject.pdf](https://github.com/mottjes/minishell/en.subject.pdf)

### Installation

Follow these steps to set up and run Minishell on your system:

#### Requirements:

    - GCC / CLANG Compiler
    - GNU Make
    - GNU Readline library

1. **Clone the Repository**:

    ```sh
    git https://github.com/mottjes/minishell.git
    ```

2. **Compile the Code**:

    ```sh
    make
    ```

3. **Launch the Executable**:

    ```sh
    ./minishell
    ```
