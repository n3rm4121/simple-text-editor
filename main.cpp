#include <iostream>
#include <unistd.h>
#include <string>
#include <cctype>
using namespace std;

struct Node
{
    string line;
    Node *next;
    Node *prev;

    Node(const string line) : line(line), next(nullptr), prev(nullptr) {}
};

class TextEditor
{

    Node *head;
    Node *tail;
    int lineCount;

public:
    TextEditor() : head(nullptr), tail(nullptr), lineCount(0) {}

    void addLine(string &line)
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

        display();
    }

    void editLine(int lineNumber, string newLine)
    {
        Node *NodeToEdit = getNodeAt(lineNumber);
        if (NodeToEdit != nullptr)
        {
            NodeToEdit->line = newLine;
        }
        else
        {
            cout << "line number out of range\n";
        }
        display();
    }

    void deleteLine(int lineNumberToDelete)
    {
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
            display();
            return;
        }

        cout << "line number out of range\n";
    }

    void display()
    {
        //sleep(1);
        // cout << system("clear");
        std::cout << "\033[2J\033[H";  // 003[2J => clears the terminal & 003[H => move the cursor top-left

        cout << endl;
        cout << "Enter 'menu' to display the commands\n";
        Node *temp = head;
        int count = 1;
        while (temp != nullptr)
        {
            if(count < 10){
                cout << count << "   |  " << temp->line << "\n";
            }else{
                cout << count << "  |  " << temp->line << "\n";

            }
            
            temp = temp->next;
            count++;
        }
        cout << endl;
    }

    void run()
    {
        std::string command;
        cout << "SIMPLE TEXT EDITOR" << endl;
        showMenu();
        cout << endl;
        while (true)
        {

            cout << "> ";
            getline(cin, command);
            if (command.substr(0, 4) == "add ")
            {
                string line = command.substr(4);
                addLine(line);
            }
            else if (command == "display")
            {
                display();
            }
            else if (command.substr(0, 5) == "edit ")
            {
                string nextString = command.substr(5);
                int spacePos = nextString.find(" ");
                if (spacePos != string::npos)
                {
                    int lineNum = stoi(nextString.substr(0, spacePos));
                    string newLine = nextString.substr(spacePos + 1);
                    editLine(lineNum, newLine);
                }
                else
                {
                    cout << "Invalid command\n";
                }
            }
            else if (command.substr(0, 7) == "delete ")
            {

                std::string lineNumberStr = command.substr(7);
                if (isNumber(lineNumberStr))
                {
                    int lineNumber = std::stoi(lineNumberStr);
                    deleteLine(lineNumber);
                }
                else
                {
                    std::cout << "Invalid input: Please provide a numeric line number.\n";
                }
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
                cout << "Unknown Command!\n";
            }
        }
    }

private:
    Node *getNodeAt(int lineNumber)
    {
        Node *temp = head;
        int count = 1;
        while (temp != nullptr && count < lineNumber)
        {
            temp = temp->next;
            count++;
        }
        return temp;
    }

    void showMenu()
    {
        string menu[] = {
            "add [line] - Add a new line",
            "edit [lineNum] [newLine] - Edit an existing line",
            "delete [lineNum] - Delete a line",
            "display - Display all lines",
            "menu - Show menu",
            "exit - Exit the editor"};
        const char corner = '+';
        const char horizontal = '-';
        const char vertical = '|';

        const int width = 60;
        string border(width, horizontal);
        cout << corner << border << corner << endl;

        for (string &line : menu)
        {
            int padding = width - line.size();
            std::cout << vertical << line << std::string(padding, ' ') << vertical << std::endl;
        }
        cout << corner << border << corner << endl;
    }

    bool isNumber(const std::string &str)
    {
        for (char const &c : str)
        {
            if (!std::isdigit(c))
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
