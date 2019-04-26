# DataStructFinal
## CSCI 2270 at CU Boulder final project

## Files
- Inventory.hpp - Inventory system (applies Database + Priority Queue + Trie in a manner related to skis/snowboards)
- Inventory.cpp - Inventory.hpp implementation
- Database.hpp - Defines and implements database system for linking tables and whatnot (primary datastructure)
- Trie.hpp - Defines and implements generic Trie type
- priorityQueue.hpp - Defines and implements generic priority queue type
- main.cpp - main function for GUI version
- returnscreen.h - Defines functionality for returning skis in the GUI
- returnscreen.cpp - returnscreen.h implementation
- shopwindow.h - Defines functionality for making ski reservations in GUI
- shopwindow.cpp - shopwindow.h implementation
- checkoutdialog.h - Defines dialog window for checking out skis in GUI
- checkoutdialog.cpp - checkoutdialog.h implementation

## Usage
1. Run with qmake then run the executable (requires Qt library)
2. Load serial inventory file called save.csv
3. All else is self explanatory
