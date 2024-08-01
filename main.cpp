#include <iostream>
#include <unistd.h>
#include <string>
#include <cctype>
#include <fstream>
using namespace std;

// ANSI escape codes for colors
const std::string RESET = "\033[0m"; // to reset the color back to the default after each line
const std::string RED = "\033[31m";
const std::string GREEN = "\033[32m";
const std::string YELLOW = "\033[33m";
const std::string BLUE = "\033[34m";
const std::string MAGENTA = "\033[35m";
const std::string CYAN = "\033[36m";
const std::string WHITE = "\033[37m";
const std::string WHITE_BG = "\033[48;5;15m"; // White background
const std::string YELLOW_BG = "\033[43m";    // Yellow background

struct Node
{
    string line;
    Node *next;
    Node *prev;

    Node(const string &line) : line(line), next(nullptr), prev(nullptr) {}
};

class TextEditor
{
    Node *head;
    Node *tail;
    int lineCount;
    string fileName;

public:
    TextEditor() : head(nullptr), tail(nullptr), lineCount(0) {}

    ~TextEditor()
    {
        Node *current = head;
        while (current != nullptr)
        {
            Node *nextNode = current->next;
            delete current;
            current = nextNode;
        }
    }

    void addLine(const string &line, bool skipDisplay = false)
    {
        Node *newNode = new Node(line);

        if (head == nullptr)
        {
            head = tail = newNode;
        }
        else
        {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
        lineCount++;

        if (!skipDisplay)
        {
            display();
        }
    }

    void editLine(int lineNumber)
    {
        // show confirmation before editing

        
        Node *nodeToEdit = getNodeAt(lineNumber);
        if (nodeToEdit != nullptr)
        {
            // display the current line and prompt the user to edit it
            cout << YELLOW << "Current line: " << RESET << nodeToEdit->line << endl;
            cout << YELLOW << "Enter new line (or leave empty to keep current): " << RESET;
            string newLine;
            getline(cin, newLine);
            

            
            if (!newLine.empty() && !showConfirmation("Are you sure you want to update line " + std::to_string(lineNumber) + "?"))
            {
                return;
            }
            {
                nodeToEdit->line = newLine;
            }

            display();
            cout << GREEN << "Line " << lineNumber << " updated.\n"
                 << RESET;
        }
        else
        {
            cout << RED << "Line number out of range\n"
                 << RESET;
        }
    }

    void deleteSingleLine(int lineNumberToDelete)
    {
        if(!showConfirmation("Are you sure you want to delete line " + std::to_string(lineNumberToDelete) + "?")){
            return;
        }
        Node *nodeToDelete = getNodeAt(lineNumberToDelete);
        if (nodeToDelete != nullptr)
        {
            if (nodeToDelete == head)
            {
                head = nodeToDelete->next;
                if (head != nullptr)
                {
                    head->prev = nullptr;
                }
            }
            else if (nodeToDelete == tail)
            {
                tail = nodeToDelete->prev;
                if (tail != nullptr)
                {
                    tail->next = nullptr;
                }
            }
            else
            {
                nodeToDelete->prev->next = nodeToDelete->next;
                nodeToDelete->next->prev = nodeToDelete->prev;
            }
            delete nodeToDelete;
            lineCount--;
            display();
            cout << GREEN << "Line " << lineNumberToDelete << " deleted.\n"
                 << RESET;
            
        }
        else
        {
            cout << "Line number out of range\n";
        }
    }

    void deleteAllLines()
    {
        if (head == nullptr)
        {
            cout << "No lines to delete\n";
            return;
        }

        if (showConfirmation("Are you sure you want to delete all lines?"))
        {
            Node *current = head;
            while (current != nullptr)
            {
                Node *nextNode = current->next;
                delete current;
                current = nextNode;
            }
            head = tail = nullptr;
            lineCount = 0;
            display();
            cout << GREEN << "All lines deleted.\n"
                 << RESET;
        }
    }

    void display() const {
    system("clear");    // clears the terminal
    cout << endl;
    cout << YELLOW << "Enter 'menu' to display the commands\n" << RESET;

    // Borders for the display
    const char corner = '+';
    const char horizontal = '-';
    const char vertical = '|';

    // Calculate the width based on the longest line
    int maxWidth = 60;
    Node* temp = head;
    while (temp != nullptr) {
        if (temp->line.size() > maxWidth) {
            maxWidth = temp->line.size();
        }
        temp = temp->next;
    }
    maxWidth += 10; // Add padding to the width

    string border(maxWidth, horizontal);
    // Determine the center text based on filename
    string centerText = fileName.empty() ? "NOT SAVED" : "File: " + fileName;

    // Calculate the padding to center the text
    int paddingLeft = (maxWidth - centerText.size()) / 2;
    int paddingRight = maxWidth - centerText.size() - paddingLeft;

    // Display the top border with the center text
    cout << BLUE << corner << border << corner << RESET << endl;
    cout << string(paddingLeft, ' ') << (fileName.empty() ? RED : GREEN) << centerText << RESET << string(paddingRight, ' ') << endl;

    // Calculate maximum width of the line numbers
    int maxLineNumberWidth = 1;
    Node* tempForWidth = head;
    while (tempForWidth != nullptr) {
        int lineNumWidth = std::to_string(lineCount).size();
        if (lineNumWidth > maxLineNumberWidth) {
            maxLineNumberWidth = lineNumWidth;
        }
        tempForWidth = tempForWidth->next;
    }

    temp = head;
    int count = 1;
    while (temp != nullptr) {
        // Format line number with padding
        string lineNum = std::to_string(count);
        string paddedLineNum = std::string(maxLineNumberWidth - lineNum.size(), ' ') + lineNum;

        cout << CYAN<< paddedLineNum << RESET << BLUE << " |  " << RESET << temp->line << endl;

        temp = temp->next;
        count++;
    }

    // Add vertical space
    int numOfEmptyLines = 5;
    for (int i = 0; i < numOfEmptyLines; ++i) {
        cout << '\n';
    }

    cout << BLUE << corner << border << corner << RESET << endl;
}

    void saveInTextFile()
    {
        if (fileName.empty())
        {
            cout << RED << "File name not set. Please enter a file name to save the file with its extension" << RESET << YELLOW << " (e.g., FILENAME.txt): " << RESET;
            getline(cin, fileName);
            if (fileName.empty())
            {
                cout << RED << "No file name provided. Aborted save.\n"
                     << RESET;
                return;
            }
        }

        cout << YELLOW << "Saving file" << RESET;
        for (int i = 0; i < 3; ++i)
        {
            cout << YELLOW << "." << RESET;
            cout.flush();
            usleep(400000); // sleep for 400 milliseconds
        }
        cout << endl;

        Node *temp = head;
        std::ofstream file(fileName, std::ios::out);

        if (file.is_open())
        {
            while (temp != nullptr)
            {
                file << temp->line << '\n';
                temp = temp->next;
            }
            file.flush();
            file.close();
            cout << GREEN << "File saved successfully as \"" << fileName << "\".\n"
                 << RESET;

            sleep(1); // sleep for 1 second
            display();
        }
        else
        {
            cout << RED << "Unable to open file for saving.\n"
                 << RESET;
        }
    }

    void readFile(const string &fileName)
    {
        if (isFileExists(fileName))
        {
            this->fileName = fileName;
            std::ifstream fileIn(fileName);

            if (fileIn.peek() == std::ifstream::traits_type::eof())
            {
                cout << "File is empty\n";
                return;
            }

            string line;
            while (getline(fileIn, line))
            {
                addLine(line, true);
            }
            fileIn.close();
            display();
        }
        else
        {
            cout << "The file name you entered doesn't exist\n";
        }
    }

    void run()
    {
        std::string command;
        showMenu();
        cout << endl;
        while (true)
        {
            cout << GREEN << "> " << RESET;
            getline(cin, command);
            
            if (command == "add -m")
            {
                addMultipleLines();
            }
            else if (command.substr(0, 7) == "add -b ")
            {
                std::string lineNumberStr = command.substr(7);
                if (isNumber(lineNumberStr))
                {
                    int lineNumber = std::stoi(lineNumberStr);
                    addLineBelowLineNumber(lineNumber);
                }
                else
                {
                    cout << RED << "Invalid input:" << RESET << YELLOW << " Please provide a numeric line number.\n"
                         << RESET;
                }
            }
            else if(command.substr(0, 7) == "add -a ")
            {
                std::string lineNumberStr = command.substr(7);
                if (isNumber(lineNumberStr))
                {
                    int lineNumber = std::stoi(lineNumberStr);
                    addLineAboveLineNumber(lineNumber);
                }
                else
                {
                    cout << RED << "Invalid input:" << RESET << YELLOW << " Please provide a numeric line number.\n"
                         << RESET;
                }
            }
            else if (command.substr(0, 4) == "add ")
            {
                string line = command.substr(4);
                addLine(line);
            }
            
            else if (command == "display")
            {
                display();
            }
            else if (command == "save")
            {
                saveInTextFile();
            }
            else if (command.substr(0, 5) == "open ")
            {
                readFile(command.substr(5));
            }
            else if (command.substr(0, 5) == "edit ")
            {
                int lineNumber = stoi(command.substr(5));
                editLine(lineNumber);
            }
             else if(command == "del -a")
            {
                deleteAllLines();
            }
            else if (command.substr(0, 4) == "del ")
            {
                std::string lineNumberStr = command.substr(4);
                if (isNumber(lineNumberStr))
                {
                    int lineNumber = std::stoi(lineNumberStr);
                    deleteSingleLine(lineNumber);
                }
                else
                {
                    cout << RED << "Invalid input:" << RESET << YELLOW << " Please provide a numeric line number.\n"
                         << RESET;
                }
            }
           
            else if (command == "clear")
            {
                display();
            }
            else if (command == "exit")
            {
                break;
            }
            else if (command == "menu")
            {
                showMenu();
            }
            else
            {
                cout << RED << "Unknown command." << RESET << YELLOW << " Enter 'menu' to see commands.\n"
                     << RESET;
            }
        }
    }

    void addMultipleLines()
    {
        cout << YELLOW << "Enter multiple lines. Type 'end' on a new line to finish." << RESET << endl;
        string line;
        while (true)
        {
            getline(cin, line);
            if (line == "end")
            {
                break;
            }
            addLine(line, true);
        }
        display();
    }

    void addLineBelowLineNumber(int lineNumber)
    {
        Node *node = getNodeAt(lineNumber);
        if (node != nullptr)
        {
            cout << YELLOW << "Enter the text to add below line " << lineNumber << ": " << RESET;
            string line;
            getline(cin, line);
            Node *newNode = new Node(line);

            if (node == tail)
            {
                tail->next = newNode;
                newNode->prev = tail;
                tail = newNode;
            }
            else
            {
                newNode->next = node->next;
                newNode->prev = node;
                node->next->prev = newNode;
                node->next = newNode;
            }
            lineCount++;
            display();
        }
        else
        {
            cout << RED << "Line number out of range\n"
                 << RESET;
        }
    }

    void addLineAboveLineNumber(int lineNumber)
    {
        Node *node = getNodeAt(lineNumber);
        if (node != nullptr)
        {
            cout << YELLOW << "Enter the text to add above line " << lineNumber << ": " << RESET;
            string line;
            getline(cin, line);
            Node *newNode = new Node(line);

            if (node == head)
            {
                head->prev = newNode;
                newNode->next = head;
                head = newNode;
            }
            else
            {
                newNode->prev = node->prev;
                newNode->next = node;
                node->prev->next = newNode;
                node->prev = newNode;
            }
            lineCount++;
            display();
        }
        else
        {
            cout << RED << "Line number out of range\n"
                 << RESET;
        }
    }

private:
    Node *getNodeAt(int lineNumber) const
    {
        Node *temp = head;
        int count = 1;
        while (temp != nullptr && count < lineNumber)
        {
            temp = temp->next;
            count++;
        }
        return (count == lineNumber) ? temp : nullptr;
    }

    bool isFileExists(const string &fileName)
    {
        std::ifstream file(fileName);
        return file.good();
    }

    bool isNumber(const string &str)
    {
        for (char const &c : str)
        {
            if (std::isdigit(c) == 0)
                return false;
        }
        return true;
    }

    void showMenu() const
    {
       
        cout << YELLOW_BG << WHITE << "Available commands:" << RESET << endl;
        cout << CYAN << "menu" << RESET << " - Displays the available commands." << endl;
        cout << CYAN << "add <text>" << RESET << " - Adds a new line with the given text." << endl;
        cout << CYAN << "add -m" << RESET << " - Adds multiple lines until 'end' is entered." << endl;
        cout << CYAN << "add -b <line_number>" << RESET << " - Adds a new line below the specified line number." << endl;
        cout << CYAN << "add -a <line_number>" << RESET << " - Adds a new line above the specified line number." << endl;
        cout << CYAN << "edit <line_number>" << RESET << " - Edits the specified line with the new text." << endl;
        cout << CYAN << "del <line_number>" << RESET << " - Deletes the specified line number." << endl;
        cout << CYAN << "display" << RESET << " - Displays the current text." << endl;
        cout << CYAN << "save" << RESET << " - Saves the current text to a file." << endl;
        cout << CYAN << "open <file_name>" << RESET << " - Opens the specified file and loads the content." << endl;
        cout << CYAN << "del -a" << RESET << " - Deletes all the lines." << endl;
        cout << CYAN << "exit" << RESET << " - Exits the text editor." << endl;
        
    }

    bool showConfirmation(const string &message) const
    {
        cout << GREEN << message << RESET << YELLOW << " (y/n): " << RESET;
        string response;
        getline(cin, response);
        if (response != "y")
        {
            cout << RED << "Operation aborted.\n"
                 << RESET;
            return false;
        }

        return true;
    }
};

int main()
{
    TextEditor editor;
    editor.run();
    return 0;
}
