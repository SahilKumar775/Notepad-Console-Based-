#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <conio.h>
#include <windows.h>
#include <iomanip>
#include <algorithm>

using namespace std;

// Terminal handling class for better UI
class Terminal {
public:
    static void clearScreen() {
        system("cls");
    }

    static void setCursorPosition(int x, int y) {
        COORD coord = { (SHORT)x, (SHORT)y };
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
    }

    static void setTextColor(int color) {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
    }

    static int getTerminalWidth() {
        CONSOLE_SCREEN_BUFFER_INFO csbi;
        GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
        return csbi.srWindow.Right - csbi.srWindow.Left + 1;
    }

    static int getTerminalHeight() {
        CONSOLE_SCREEN_BUFFER_INFO csbi;
        GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
        return csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
    }

    static void drawBox(int x, int y, int width, int height, const string& title = "") {
        setCursorPosition(x, y);
        cout << "+";
        for (int i = 0; i < width - 2; i++) {
            if (title.length() > 0 && i == 2) {
                cout << " " << title << " ";
                i += title.length() + 2;
            } else {
                cout << "-";
            }
        }
        cout << "+";

        for (int i = 1; i < height - 1; i++) {
            setCursorPosition(x, y + i);
            cout << "|";
            setCursorPosition(x + width - 1, y + i);
            cout << "|";
        }

        setCursorPosition(x, y + height - 1);
        cout << "+";
        for (int i = 0; i < width - 2; i++) {
            cout << "-";
        }
        cout << "+";
    }

    static void drawHorizontalLine(int x, int y, int width) {
        setCursorPosition(x, y);
        cout << "+";
        for (int i = 0; i < width - 2; i++) {
            cout << "-";
        }
        cout << "+";
    }
};

class Node {
public:
    Node* before;
    Node* after;
    char Data;
    Node* below;
    Node* above;
    
    Node(char Data) {
        this->Data = Data;
        before = nullptr;
        after = nullptr;
        below = nullptr;
        above = nullptr;
    }
    
    ~Node() {}
};

class Doublylinkedlist {
private:
    Node* head;
    Node* tail;
    Node* line;
    Node* cursor;
    
public:
    Doublylinkedlist() {
        Node* NewNode = new Node('|');
        head = NewNode;
        tail = NewNode;
        line = NewNode;
        cursor = NewNode;
    }
    
    Node* getHead() {
        return head;
    }
    
    void Insert(char data) {
        Node* temp = cursor;
        while(temp->after) { 
            temp = temp->after;
        }
        Node* NewNode = new Node(temp->Data);
        NewNode->before = temp;
        temp->after = NewNode;
        if (temp->above) {
            if (temp->above->after) {
                NewNode->above = temp->above->after;
                NewNode->above->below = NewNode;
            }
        }
        if (temp->below) {
            if (temp->below->after) {
                NewNode->below = temp->below->after;
                NewNode->below->above = NewNode;
            }
        }
        while (temp != cursor) {
            temp->Data = temp->before->Data;
            temp = temp->before;
        }
        temp->Data = data;
        cursor = cursor->after;
    }
    
    void Moveright() {
        if (cursor->after) {
            cursor->Data = cursor->after->Data;
            cursor->after->Data = '|';
            cursor = cursor->after;
        }
        else {
            Node* NewNode = new Node('|');
            cursor->Data = ' ';
            cursor->after = NewNode;
            NewNode->before = cursor;
            if (cursor->above) {
                if (cursor->above->after) {
                    cursor->above->after->below = NewNode;
                    NewNode->above = cursor->above->after;
                }
            }
            if (cursor->below) {
                if (cursor->below->after) {
                    cursor->below->after->after = NewNode;
                    NewNode->below = cursor->below->after;
                }
            }
            cursor = NewNode;
        }
    }
    
    void Moveabove() {
        if (line->above == nullptr)
            return;
        else if (cursor->above) {
            line = line->above;
            cursor = cursor->above;
            Insert('|');
            cursor = cursor->before->below;
            if (cursor->before == nullptr && cursor->after == nullptr) {
                cursor->Data = ' ';
                cursor = cursor->above;
                return;
            }
            else if (cursor->after == nullptr) {
                Node* temp = cursor;
                if (temp->below) {
                    temp->below->above = nullptr;
                }
                if (temp->above) {
                    temp->above->below = nullptr;
                }
                if (temp->before) {
                    temp->before->after = nullptr;
                }
                cursor = cursor->above;
                delete temp;    
            }
            else {
                cursor = cursor->after;
                Delete();
                cursor = cursor->above;
            }
        }
        else {
            line = line->above;
            Node* temp = line;
            while (temp->after) {
                temp = temp->after;
            }
            Node* NewNode = new Node('|');
            temp->after = NewNode;
            NewNode->before = temp;
            if (temp->below) {
                if (temp->below->after) {
                    temp->below->after->above = NewNode;
                    NewNode->below = temp->below->after;
                }
            }
            if (temp->above) {
                if (temp->above->after) {
                    temp->above->after->below = NewNode;
                    NewNode->above = temp->above->after;
                }
            }
            if (cursor->before == nullptr && cursor->after == nullptr) {
                cursor->Data = ' ';
                cursor == NewNode;
                return;
            }
            else if (cursor->after == nullptr) {
                Node* temp = cursor;
                if (temp->below) {
                    temp->below->above = nullptr;
                }
                if (temp->above) {
                    temp->above->below = nullptr;
                }
                if (temp->before) {
                    temp->before->after = nullptr;
                }
                cursor = NewNode;
                delete temp;
            }
            else {
                cursor = cursor->after;
                Delete();
                cursor = NewNode;
            }
        }
    }
    
    void Movebelow() {
        if (line->below == nullptr) {
            Node* NewNode = new Node('|');
            line->below = NewNode;
            NewNode->above = line;
            line = NewNode;
            tail = NewNode;
            if (cursor->after) {
                cursor = cursor->after;
                Delete();
            }
            else {
                Node* temp = cursor;
                if (temp->below) {
                    temp->below->above = nullptr;
                }
                if (temp->above) {
                    temp->above->below = nullptr;
                }
                if (temp->before) {
                    temp->before->after = nullptr;
                }
                cursor = NewNode;
                delete temp;
            }
            cursor = NewNode;
        }
        else if (cursor->below) {
            line = line->below;
            cursor = cursor->below;
            Insert('|');
            cursor = cursor->before->above;
            if (cursor->before == nullptr && cursor->after == nullptr) {
                cursor->Data = ' ';
                cursor = cursor->below;
                return;
            }
            else if (cursor->after == nullptr) {
                Node* temp = cursor;
                if (temp->below) {
                    temp->below->above = nullptr;
                }
                if (temp->above) {
                    temp->above->below = nullptr;
                }
                if (temp->before) {
                    temp->before->after = nullptr;
                }
                cursor = cursor->below;
                delete temp;
            }
            else {
                cursor = cursor->after;
                Delete();
                cursor = cursor->below;
            }
        }
        else {
            line = line->below;
            Node* temp = line;
            while (temp->after) {
                temp = temp->after;
            }
            Node* NewNode = new Node('|');
            temp->after = NewNode;
            NewNode->before = temp;
            if (temp->below) {
                if (temp->below->after) {
                    temp->below->after->above = NewNode;
                    NewNode->below = temp->below->after;
                }
            }
            if (temp->above) {
                if (temp->above->after) {
                    temp->above->after->below = NewNode;
                    NewNode->above = temp->above->after;
                }
            }
            if (cursor->before == nullptr && cursor->after == nullptr) {
                cursor->Data = ' ';
                cursor == NewNode;
                return;
            }
            else if (cursor->after == nullptr) {
                Node* temp = cursor;
                if (temp->below) {
                    temp->below->above = nullptr;
                }
                if (temp->above) {
                    temp->above->below = nullptr;
                }
                if (temp->before) {
                    temp->before->after = nullptr;
                }
                cursor = NewNode;
                delete temp;
            }
            else {
                cursor = cursor->after;
                Delete();
                cursor = NewNode;
            }
        }
    }
    
    void Moveleft() {
        if (cursor->before) {
            cursor->Data = cursor->before->Data;
            cursor->before->Data = '|';
            cursor = cursor->before;
        }
    }
    
    void Print(int startX, int startY, int width) {
        Node* temp = head;
        int lineCount = 0;
        
        while (temp && lineCount < Terminal::getTerminalHeight() - 4) {
            Terminal::setCursorPosition(startX, startY + lineCount);
            Node* temp2 = temp;
            int charCount = 0;
            
            while (temp2 && charCount < width - 2) {
                cout << temp2->Data;
                temp2 = temp2->after;
                charCount++;
            }
            
            temp = temp->below;
            lineCount++;
        }
    }
    
    string Saving() {
        string Save = "";
        Node* temp = head;
        while (temp) {
            Node* temp2 = temp;
            while (temp2) {
                if (temp2 != cursor) {
                    Save += temp2->Data;
                }
                temp2 = temp2->after;
            }
            Save += "\n";
            temp = temp->below;
        }
        return Save;
    }
    
    void Delete() {
        if (cursor->before == nullptr) {
            return;
        }
        Node* temp = cursor->before;
        cursor = cursor->before;
        while (temp->after) {
            temp->Data = temp->after->Data;
            temp = temp->after;
        }
        if (temp->above) {
            temp->above->below = nullptr;
        }
        if (temp->below) {
            temp->below->above = nullptr;
        }
        if (temp->before) {
            temp->before->after = nullptr;
        }
        temp->above = nullptr;
        temp->below = nullptr;
        temp->after = nullptr;
        temp->before = nullptr;
        
        delete temp;
    }
    
    ~Doublylinkedlist() {}
};

// Function to get spell check suggestions
vector<vector<string>> SpellChecker(const vector<string>& Dictionary, const string& text) {
    vector<vector<string>> suggestions(4); // For substitution, omission, insertion, reversal
    
    if (text.empty() || text.size() < 2) return suggestions;
    
    // Substitution suggestions
    for (size_t i = 0; i < text.size(); i++) {
        for (char c = 'a'; c <= 'z'; c++) {
            string temp = text;
            temp[i] = c;
            for (const auto& word : Dictionary) {
                if (word == temp) {
                    if (find(suggestions[0].begin(), suggestions[0].end(), temp) == suggestions[0].end()) {
                        suggestions[0].push_back(temp);
                        if (suggestions[0].size() >= 5) break; // Limit to 5 suggestions
                    }
                }
            }
            if (suggestions[0].size() >= 5) break;
        }
    }
    
    // Omission suggestions
    for (size_t i = 0; i < text.size(); i++) {
        string temp = text;
        temp.erase(i, 1);
        for (const auto& word : Dictionary) {
            if (word == temp) {
                if (find(suggestions[1].begin(), suggestions[1].end(), temp) == suggestions[1].end()) {
                    suggestions[1].push_back(temp);
                    if (suggestions[1].size() >= 5) break;
                }
            }
        }
        if (suggestions[1].size() >= 5) break;
    }
    
    // Insertion suggestions
    for (size_t i = 0; i <= text.size(); i++) {
        for (char c = 'a'; c <= 'z'; c++) {
            string temp = text;
            temp.insert(i, 1, c);
            for (const auto& word : Dictionary) {
                if (word == temp) {
                    if (find(suggestions[2].begin(), suggestions[2].end(), temp) == suggestions[2].end()) {
                        suggestions[2].push_back(temp);
                        if (suggestions[2].size() >= 5) break;
                    }
                }
            }
            if (suggestions[2].size() >= 5) break;
        }
        if (suggestions[2].size() >= 5) break;
    }
    
    // Reversal suggestions
    for (size_t i = 0; i < text.size() - 1; i++) {
        string temp = text;
        swap(temp[i], temp[i + 1]);
        for (const auto& word : Dictionary) {
            if (word == temp) {
                if (find(suggestions[3].begin(), suggestions[3].end(), temp) == suggestions[3].end()) {
                    suggestions[3].push_back(temp);
                    if (suggestions[3].size() >= 5) break;
                }
            }
        }
        if (suggestions[3].size() >= 5) break;
    }
    
    return suggestions;
}

// Function to draw the sidebar with spell check suggestions
void drawSidebar(int startX, int startY, int width, int height, const string& currentWord, const vector<vector<string>>& suggestions) {
    // Draw sidebar box
    Terminal::drawBox(startX, startY, width, height, " Spell Check ");
    
    // Current word
    Terminal::setCursorPosition(startX + 2, startY + 2);
    Terminal::setTextColor(14); // Yellow
    cout << "Current Word:";
    Terminal::setTextColor(7); // Reset
    Terminal::setCursorPosition(startX + 2, startY + 3);
    cout << (currentWord.empty() ? "(none)" : currentWord);
    
    // Suggestions
    const char* titles[] = {"Substitution", "Omission", "Insertion", "Reversal"};
    int yPos = startY + 5;
    
    for (int i = 0; i < 4; i++) {
        Terminal::setCursorPosition(startX + 2, yPos);
        Terminal::setTextColor(11); // Light cyan
        cout << titles[i] << ":";
        Terminal::setTextColor(7); // Reset
        
        yPos += 1;
        
        if (suggestions[i].empty()) {
            Terminal::setCursorPosition(startX + 4, yPos);
            cout << "(none)";
            yPos += 1;
        } else {
            for (const auto& suggestion : suggestions[i]) {
                Terminal::setCursorPosition(startX + 4, yPos);
                cout << "- " << suggestion;
                yPos += 1;
                if (yPos >= startY + height - 3) break; // Prevent overflow
            }
        }
        
        yPos += 1; // Add space between categories
        if (yPos >= startY + height - 3) break; // Prevent overflow
    }
    
    // Help text at bottom
    Terminal::setCursorPosition(startX + 2, startY + height - 3);
    Terminal::setTextColor(8); // Gray
    cout << "Ctrl+S: Save | Ctrl+L: Load";
    Terminal::setCursorPosition(startX + 2, startY + height - 2);
    cout << "ESC: Exit";
    Terminal::setTextColor(7); // Reset
}

// Function to draw the status bar
void drawStatusBar(int startX, int startY, int width, const string& message = "") {
    Terminal::setCursorPosition(startX, startY);
    cout << "+";
    for (int i = 0; i < width - 2; i++) {
        cout << "-";
    }
    cout << "+";
    
    Terminal::setCursorPosition(startX + 2, startY + 1);
    if (!message.empty()) {
        cout << message;
    } else {
        cout << "Enhanced Text Editor | Arrow keys to navigate | Type to insert text";
    }
}

int main() {
    // Set console title
    SetConsoleTitle("Enhanced Text Editor with Spell Check");
    
    char ch = '\0';
    string word = "";
    string statusMessage = "";
    int statusMessageTimer = 0;
    
    Doublylinkedlist text;
    vector<string> Dictionary;
    
    // Load dictionary
    ifstream file("dictionary.txt");
    if (file) {
        string line;
        while (getline(file, line)) {
            Dictionary.push_back(line);
        }
        file.close();
    } else {
        // Create a simple dictionary if file doesn't exist
        Dictionary = {"the", "and", "that", "have", "for", "not", "with", "you", "this", "but", 
                     "his", "from", "they", "say", "her", "she", "will", "one", "all", "would", 
                     "there", "their", "what", "out", "about", "who", "get", "which", "when", "make"};
    }
    
    while (true) {
        Terminal::clearScreen();
        
        // Calculate layout dimensions
        int termWidth = Terminal::getTerminalWidth();
        int termHeight = Terminal::getTerminalHeight();
        int mainWidth = termWidth * 0.8; // 80% of screen width
        int sidebarWidth = termWidth - mainWidth; // 20% of screen width
        
        // Draw main text area
        Terminal::drawBox(0, 0, mainWidth, termHeight - 2, " Text Editor ");
        
        // Draw sidebar
        vector<vector<string>> suggestions;
        if (!word.empty()) {
            suggestions = SpellChecker(Dictionary, word);
        } else {
            suggestions.resize(4); // Empty suggestions
        }
        drawSidebar(mainWidth, 0, sidebarWidth, termHeight - 2, word, suggestions);
        
        // Draw status bar
        drawStatusBar(0, termHeight - 2, termWidth, statusMessage);
        
        // Print text content
        text.Print(1, 1, mainWidth - 2);
        
        // Decrease status message timer
        if (statusMessageTimer > 0) {
            statusMessageTimer--;
            if (statusMessageTimer == 0) {
                statusMessage = "";
            }
        }
        
        // Get user input
        ch = _getch();
        
        if (ch == 12) { // Ctrl + L (Load)
            ifstream file("Save.txt");
            if (file) {
                string line;
                while (getline(file, line)) {
                    for (int i = 0; i < line.size(); i++) {
                        text.Insert(line[i]);
                    }
                    text.Movebelow(); // Add a new line after each line
                }
                file.close();
                statusMessage = "File loaded successfully!";
                statusMessageTimer = 5;
            } else {
                statusMessage = "Error: File not found or unable to open.";
                statusMessageTimer = 5;
            }
        } else if (ch == 19) { // Ctrl + S (Save)
            ofstream file("Save.txt");
            if (file) {
                file << text.Saving();
                file.close();
                statusMessage = "Text saved successfully!";
                statusMessageTimer = 5;
            } else {
                statusMessage = "Error: Unable to open or create the file for saving.";
                statusMessageTimer = 5;
            }
        } else if (ch == 32) { // Space key
            text.Insert(' ');
            word = ""; // Reset current word on space
        } else if (ch == 8) { // Backspace (Delete)
            text.Delete();
            if (!word.empty()) {
                word.pop_back();
            }
        } else if (ch == 27) { // ESC (Quit)
            Terminal::clearScreen();
            cout << "Exiting the program. Goodbye!" << endl;
            break;
        } else if (ch == 75) { // Left Arrow
            text.Moveleft();
            word = ""; // Reset current word on cursor movement
        } else if (ch == 77) { // Right Arrow
            text.Moveright();
            word = ""; // Reset current word on cursor movement
        } else if (ch == 72) { // Up Arrow
            text.Moveabove();
            word = ""; // Reset current word on cursor movement
        } else if (ch == 80) { // Down Arrow
            text.Movebelow();
            word = ""; // Reset current word on cursor movement
        } else if (ch >= 32 && ch <= 126) { // Printable ASCII characters
            text.Insert(ch);
            if (isalpha(ch)) { // Only add alphabetic characters to the current word
                word += ch;
            } else {
                word = ""; // Reset current word on non-alphabetic characters
            }
        }
    }
    
    return 0;
}