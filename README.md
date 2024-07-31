# Simple Text Editor 📝

Welcome to the **Simple Text Editor**! This is a lightweight, command-line based text editor written in C++. It offers basic text manipulation features and supports color-coded outputs for better readability. Below is a detailed guide on how to use this editor.

## Features ✨

- **Add** new lines to your text.
- **Edit** existing lines by specifying the line number.
- **Delete** specific lines.
- **Display** the entire text with clear visual separation.
- **Save** your work to a text file.
- **Open** and read text files.
- **Clear** the screen and display the current text.
- **Menu** command to show available commands.
- **Exit** the editor.

## How to Use 🚀

### Adding a Line
To add a new line to your text, use the `add` command followed by the text you want to add.
```sh
add This is a new line.
```

### Editing a Line
To edit an existing line, use the `edit` command followed by the line number and the new text.
```sh
edit 2 This is the updated text.
```

### Deleting a Line
To delete a specific line, use the `delete` command followed by the line number.
```sh
delete 3
```

### Displaying the Text
To display all lines of your text, use the `display` command.
```sh
display
```

### Saving the File
To save your current text to a file, use the `save` command. If the file name is not already set, you will be prompted to enter one.
```sh
save
```

### Opening a File
To open and read a text file, use the `open` command followed by the file name.
```sh
open example.txt
```

### Clearing the Screen
To clear the screen and re-display the current text, use the `clear` command.
```sh
clear
```

### Showing the Menu
To display the list of available commands, use the `menu` command.
```sh
menu
```

### Exiting the Editor
To exit the text editor, use the `exit` command.
```sh
exit
```

## Sample Menu 📋
Here’s what the menu looks like:
```
+-----------------------------Simple-Text-Editor-Menu------------------------------+
| add [line] - Add a new line                                                      |
| edit [lineNum] [newLine] - Edit an existing line                                 |
| delete [lineNum] - Delete a line                                                 |
| display - Display all lines                                                      |
| save - Save file                                                                 |
| open [filename] - Load data from file                                            |
| menu - Show menu                                                                 |
| clear - Clear the screen and display the text                                    |
| exit - Exit the editor                                                           |
+----------------------------------------------------------------------------------+
```

## Code Structure 🏗️

The code is structured around a doubly linked list to store and manipulate lines of text efficiently. Below is an overview of the key components:

- **Node Structure**: Represents each line of text with pointers to the next and previous nodes.
- **TextEditor Class**: Encapsulates all the functionalities like adding, editing, deleting lines, displaying the text, saving to a file, reading from a file, and handling user commands.

### Installation and Compilation
To compile and run the text editor, you need a C++ compiler like `g++`. Use the following commands to compile and run the program:
```sh
g++ -o TextEditor TextEditor.cpp
./TextEditor
```

### Dependencies
This project uses the C++ standard library and the `<unistd.h>` library for sleep functionality.
