# Simple Text Editor 📝

Welcome to the **Simple Text Editor**! This is a command-line based text editor written in C++ using doubly linked list data structure. It offers basic text manipulation features and supports color-coded outputs for better readability. Below is a detailed guide on how to use this editor.


## Features ✨

- **Add Lines**: Add new lines of text, either individually or multiple lines at once.
- **Edit Lines**: Edit existing lines with confirmation prompts.
- **Delete Lines**: Delete specific lines or all lines with confirmation.
- **File Operations**: Save the current text to a file or open an existing file to edit.
- **Display**: Clear and visually appealing display of the current text with ANSI color codes for better readability.

## Commands 🛠️

- `menu` - Displays the available commands.
- `add <text>` - Adds a new line with the given text.
- `add -m` - Adds multiple lines until 'end' is entered.
- `add -b <line_number>` - Adds a new line below the specified line number.
- `add -a <line_number>` - Adds a new line above the specified line number.
- `edit <line_number>` - Edits the specified line with the new text.
- `del <line_number>` - Deletes the specified line number.
- `display` - Displays the current text.
- `save` - Saves the current text to a file.
- `open <file_name>` - Opens the specified file and loads the content.
- `del -a` - Deletes all the lines.
- `exit` - Exits the text editor.

## Getting Started 🚀

### Prerequisites

Ensure you have the following installed:
- C++ compiler (e.g., `g++`)
- `make` (optional, for easier compilation)

### Compilation

Compile the program using `g++`:

```bash
g++ main.cpp -o ./main
```

### Running the Program

Run the compiled program:

```bash
./main
```

## Usage Example 📘

1. **Add a Line**:
    ```sh
    > add This is a new line
    ```

2. **Edit a Line**:
    ```sh
    > edit 1
    Current line: This is a new line
    Enter new line (or leave empty to keep current): This is the edited line
    ```

3. **Delete a Line**:
    ```sh
    > del 1
    ```

4. **Save to a File**:
    ```sh
    > save
    File name not set. Please enter a file name to save with its extension (e.g., FILENAME.txt): example.txt
    Saving file...
    File saved successfully as "example.txt".
    ```

5. **Open a File**:
    ```sh
    > open example.txt
    ```
