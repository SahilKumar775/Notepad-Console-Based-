## Overview

This project implements a console-based text editor with an integrated spell checker. The editor allows users to write and edit text with real-time spell checking functionality. It uses a two-dimensional doubly linked list data structure to store and manipulate text, providing a notepad-like experience in a console environment.



## Features

- **Text Editing**: Add, delete, and edit text with cursor navigation
- **File Operations**: Save and load text files
- **Spell Checking**: Real-time spell checking with suggestions for misspelled words
- **Split Screen Interface**: 80% of the screen for text editing, 20% for spell check suggestions
- **Custom Cursor Implementation**: Navigate through text using arrow keys


## Implementation Details

### Data Structures

- **Two-Dimensional Doubly Linked List**: The core data structure used to store and manipulate text

- Each node has four links (before, after, below, above) and stores a single character
- Allows for efficient text insertion, deletion, and navigation in two dimensions
- Supports multi-line text editing



- **Vector**: Used to store dictionary words for spell checking


### Spell Checker Algorithm

The spell checker implements four methods to suggest corrections for misspelled words:

1. **Letter Substitution**: Replaces each character in the word with every possible letter
2. **Letter Omission**: Removes each character in the word one by one
3. **Letter Insertion**: Inserts every possible letter at each position in the word
4. **Letter Reversal**: Swaps adjacent characters in the word


## Requirements

- Windows operating system (for console manipulation functions)
- C++ compiler with C++11 or later support (e.g., MinGW, Visual C++)
- Terminal/console that supports ANSI color codes (for better visual experience)
- Minimum console size of 80x24 characters for optimal display


## Installation and Setup

1. **Clone or download** the repository to your local machine
2. **Compile the code** using a C++ compiler:

```plaintext
g++ -o text_editor enhanced-text-editor.cpp -std=c++17
```


3. **Create a dictionary file** named `dictionary.txt` in the same directory as the executable

1. Each word should be on a separate line
2. A sample dictionary file is provided with the project


4. **Run the executable**:

```plaintext
text_editor
```



## Usage

### Keyboard Controls

| Key Combination | Function
|-----|-----
| Arrow Keys | Move cursor through text
| Backspace | Delete character before cursor
| Ctrl + S | Save text to file (save.txt)
| Ctrl + L | Load text from file (save.txt)
| ESC | Exit the program
| Any printable character | Insert character at cursor position


### Interface

The screen is divided into two main sections:

1. **Text Editor Area (80% of screen width)**:

1. The main area where you can write and edit text
2. Shows the cursor position and text content



2. **Spell Check Area (20% of screen width)**:

1. Displays the current word being typed
2. Shows spelling suggestions categorized by correction method
3. Provides helpful information and keyboard shortcuts



3. **Status Bar (bottom of screen)**:

1. Shows program status and messages
2. Displays available commands



## How It Works

1. **Text Editing**:

1. Characters are stored in a two-dimensional doubly linked list
2. Each node represents a character and has links to adjacent characters
3. The cursor is implemented as a special character ('|') that moves through the text



2. **Spell Checking**:

1. As you type, the program tracks the current word
2. When a word is completed (by typing space or punctuation), it's checked against the dictionary
3. If the word is not found, the program suggests possible corrections
4. Suggestions are displayed in the right sidebar, categorized by correction method



3. **File Operations**:

1. Text is saved to and loaded from a file named "save.txt"
2. The file is created in the same directory as the executable



## Assignment Requirements Fulfilled

This implementation meets all the requirements specified in the assignment:

1. **Console-Based Notepad Functionality**:

1. ✅ Text input in console environment
2. ✅ Add, delete, and edit text content
3. ✅ Backspace for text deletion
4. ✅ Ctrl+L to load text from file
5. ✅ Ctrl+S to save text to file
6. ✅ ESC to quit
7. ✅ Memory release on exit
8. ✅ Screen division (80% for text, 20% for suggestions)



2. **Cursor Control and Tracking**:

1. ✅ Custom cursor implementation
2. ✅ Arrow key navigation
3. ✅ Real-time display updates
4. ✅ Immediate input processing without Enter key



3. **Data Structure**:

1. ✅ Two-dimensional doubly linked list implementation
2. ✅ Four links per node (before, after, below, above)
3. ✅ Character storage in each node
4. ✅ Multi-line text support



4. **Dictionary**:

1. ✅ Dictionary loading from text file
2. ✅ Vector storage for dictionary words



5. **Spell Checker**:

1. ✅ Letter Substitution
2. ✅ Letter Omission
3. ✅ Letter Insertion
4. ✅ Letter Reversal
5. ✅ Unique suggestion display



## Known Limitations

- The program is designed for Windows and uses Windows-specific console functions
- Large files may cause performance issues due to the linked list implementation
- The spell checker only works with English words and is case-sensitive
- The interface may not display correctly on very small console windows


## Future Improvements

- Cross-platform support for Linux and macOS
- Improved performance for large files
- Case-insensitive spell checking
- Undo/redo functionality
- Syntax highlighting for programming languages
- Find and replace functionality


## Troubleshooting

### Common Issues

1. **Compilation errors**:

1. Make sure you have a C++ compiler installed
2. Ensure you're using the correct compilation command with C++17 support



2. **Dictionary not found**:

1. Create a file named "dictionary.txt" in the same directory as the executable
2. Ensure the file has read permissions



3. **Display issues**:

1. Resize your console window to at least 80x24 characters
2. Use a console that supports ANSI color codes



### Getting Help

If you encounter any issues or have questions, please:

1. Check the troubleshooting section above
2. Review the code comments for additional information
3. Contact the developer at [[sahil.kumar.r516@example.com](mailto:sahil.kumar.r516@example.com)]


## License

This project is provided for educational purposes only. All rights reserved.

---
