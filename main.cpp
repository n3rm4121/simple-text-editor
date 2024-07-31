#include <iostream>
#include <unistd.h>
#include <string>
#include <cctype>
#include <fstream>
using namespace std;

  // ANSI escape codes for colors
    const std::string RESET = "\033[0m";     // to reset the color back to the default after each line
    const std::string RED = "\033[31m";
    const std::string GREEN = "\033[32m";
    const std::string YELLOW = "\033[33m";
    const std::string BLUE = "\033[34m";
    const std::string MAGENTA = "\033[35m";
    const std::string CYAN = "\033[36m";
    const std::string WHITE = "\033[37m";

struct Node {
    string line;
    Node* next;
    Node* prev;

    Node(const string& line) : line(line), next(nullptr), prev(nullptr) {}
};

class TextEditor {
    Node* head;
    Node* tail;
    int lineCount;
    string fileName;

public:
    TextEditor() : head(nullptr), tail(nullptr), lineCount(0) {}

    ~TextEditor() {

        Node* current = head;
        while (current != nullptr) {
            Node* nextNode = current->next;
            delete current;
            current = nextNode;
        }
    }

    void addLine(const string& line, bool skipDisplay = false) {
        Node* newNode = new Node(line);

        if (head == nullptr) {
            head = tail = newNode;
        } else {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
        lineCount++;

        if (!skipDisplay) {
            display();
        }
    }

    void editLine(int lineNumber, const string& newLine) {
        Node* nodeToEdit = getNodeAt(lineNumber);
        if (nodeToEdit != nullptr) {
            nodeToEdit->line = newLine;
            display();
        } else {
            cout << "Line number out of range\n";
        }
    }

    void deleteLine(int lineNumberToDelete) {
        Node* nodeToDelete = getNodeAt(lineNumberToDelete);
        if (nodeToDelete != nullptr) {
            if (nodeToDelete == head) {
                head = nodeToDelete->next;
                if (head != nullptr) {
                    head->prev = nullptr;
                }
            } else if (nodeToDelete == tail) {
                tail = nodeToDelete->prev;
                if (tail != nullptr) {
                    tail->next = nullptr;
                }
            } else {
                nodeToDelete->prev->next = nodeToDelete->next;
                nodeToDelete->next->prev = nodeToDelete->prev;
            }
            delete nodeToDelete;
            lineCount--;
            display();
        } else {
            cout << "Line number out of range\n";
        }
    }

   void display() const {
    system("clear");    // clears the terminal
    cout << endl;
   cout << YELLOW << "Enter 'menu' to display the commands\n" << RESET ;
    // borders for the display
    const char corner = '+';
    const char horizontal = '-';
    const char vertical = '|';

    // calculate the width based on the longest line
    int maxWidth = 60;
    Node* temp = head;
    while (temp != nullptr) {
        if (temp->line.size() > maxWidth) {
            maxWidth = temp->line.size();
        }
        temp = temp->next;
    }
    
    maxWidth += 10; // add padding to the width

    string border(maxWidth, horizontal);
     // determine the center text based on filename
    string centerText = fileName.empty() ? "NOT SAVED" : "File: " + fileName;
    
    // calculate the padding to center the text
    int paddingLeft = (maxWidth - centerText.size()) / 2;
    int paddingRight = maxWidth - centerText.size() - paddingLeft;

    // display the top border with the center text
    cout << BLUE << corner << border << corner << RESET << endl;
    cout << string(paddingLeft, ' ') << centerText << string(paddingRight, ' ') <<  endl;

    temp = head;
    int count = 1;
    while (temp != nullptr) {
        string lineNum = std::to_string(count);

        cout << lineNum << (lineNum.size() < 10 ? "| " : "| ") 
             << temp->line << endl;
        
        temp = temp->next;
        count++;
    }

    

        // add vertical space
    int numOfEmptyLines = 5; 
    for (int i = 0; i < numOfEmptyLines; ++i) {
        cout << '\n';
    }

   cout << BLUE << corner << border << corner << RESET << endl;


}


   void saveInTextFile() {
    if (fileName.empty()) {
        cout << RED << "File name not set. Please enter a file name to save the file with its extension" << RESET << YELLOW << " (e.g., FILENAME.txt): " << RESET;
        getline(cin, fileName);
        if (fileName.empty()) {
            cout << RED <<  "No file name provided. Aborted save.\n" << RESET;
            return;
        }
    }

    cout << YELLOW << "Saving file" << RESET ;
    for (int i = 0; i < 3; ++i) {
        cout << YELLOW <<  "." << RESET;
        cout.flush();
        usleep(400000); // sleep for 400 milliseconds
    }
    cout << endl;

    Node* temp = head;
    std::ofstream file(fileName, std::ios::out);

    if (file.is_open()) {
        while (temp != nullptr) {
            file << temp->line << '\n';
            temp = temp->next;
        }
        file.flush(); 
        file.close();  
        cout << GREEN << "File saved successfully as \"" << fileName << "\".\n" << RESET;
    } else {
        cout << RED << "Unable to open file for saving.\n" << RESET;
    }
}


    
    void readFile(const string& fileName) {
        if (isFileExists(fileName)) {
            this->fileName = fileName;
            std::ifstream fileIn(fileName);

            if (fileIn.peek() == std::ifstream::traits_type::eof()) {
                cout << "File is empty\n";
                return;
            }

            string line;
            while (getline(fileIn, line)) {
                addLine(line, true);
            }
            fileIn.close();
            display();
        } else {
            cout << "The file name you entered doesn't exist\n";
        }
    }

    void run() {
        std::string command;
        // cout << BLUE << "SIMPLE TEXT EDITOR MENU" << endl<< RESET;
        showMenu();
        cout << endl;
        while (true) {
            cout << GREEN << "> " << RESET ;
            getline(cin, command);
            if (command.substr(0, 4) == "add ") {
                string line = command.substr(4);
                addLine(line);
            } else if (command == "display") {
                display();
            } else if (command == "save") {
                saveInTextFile();
            } else if (command.substr(0, 5) == "open ") {
                readFile(command.substr(5));
            } else if (command.substr(0, 5) == "edit ") {
                string nextString = command.substr(5);
                int spacePos = nextString.find(" ");
                if (spacePos != string::npos) {
                    int lineNum = stoi(nextString.substr(0, spacePos));
                    string newLine = nextString.substr(spacePos + 1);
                    editLine(lineNum, newLine);
                } else {
                    cout << RED << "Invalid command." <<RESET << YELLOW << " Enter 'menu' to see commands.\n"<< RESET;
                }
            } else if (command.substr(0, 7) == "delete ") {
                std::string lineNumberStr = command.substr(7);
                if (isNumber(lineNumberStr)) {
                    int lineNumber = std::stoi(lineNumberStr);
                    deleteLine(lineNumber);
                } else {
                    cout << RED << "Invalid input:"<< RESET << YELLOW << " Please provide a numeric line number.\n" << RESET;
                }
            }
            else if(command == "clear"){
                display();
            }
            else if (command == "exit") {
                break;
            } else if (command == "menu") {
                showMenu();
            } else {
                cout << RED << "Unknown command." <<RESET << YELLOW << " Enter 'menu' to see commands.\n"<< RESET;
            }
        }
    }

private:
    Node* getNodeAt(int lineNumber) const {
        Node* temp = head;
        int count = 1;
        while (temp != nullptr && count < lineNumber) {
            temp = temp->next;
            count++;
        }
        return temp;
    }

    void showMenu() const {
   
        

        string menu[] = {
            "add [line] - Add a new line",
            "edit [lineNum] [newLine] - Edit an existing line",
            "delete [lineNum] - Delete a line",
            "display - Display all lines",
            "save - Save file",
            "open [filename] - Load data from file",
            "menu - Show menu",
            "clear - Clear the screen and display the text",
            "exit - Exit the editor"
        };
        const char corner = '+';
        const char horizontal = '-';
        const char vertical = '|';

        const int width = 60;
        string border(width, horizontal);
        
    string title ="Simple-Text-Editor-Menu"; // add color
    int titlePadding = (width - title.size()) / 2;
    string titleBorder = string(titlePadding, horizontal) + title + string(titlePadding, horizontal);
    if (titleBorder.size() < width) {
        titleBorder += horizontal; // adjust for odd width
    }

    cout << corner << titleBorder << corner << endl;

       for (const string& line : menu) {
        int padding = width - line.size();
        std::cout << vertical << " " << GREEN << line << std::string(padding, ' ') << RESET << vertical << std::endl;
        }
        cout << corner << border << corner << endl;
    }

     bool isNumber(const std::string& str) const {
        if (str.empty()) {
            return false;
        }
        for (char c : str) {
            if (!std::isdigit(c)) {
                return false;
            }
        }
        return true;
    }
    bool isFileExists(const string& fileName) const {
        std::ifstream fileIn(fileName);
        return fileIn.good();
    }
};

int main() {
    TextEditor editor;
    editor.run();
    return 0;
}
