#ifndef LibraryManager_H
#define LibraryManager_H

#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>
#include <filesystem>
#include <chrono>
#include <thread>

#include "Book.h"
#include "Member.h"
#include "InputHelper.h"

class LibraryManager {
    std::vector<Book> Books;
    std::vector<Member> Members;
    std::unordered_map<std::string , std::string> borrowRecords; // bookID -> memberID

    // File operations
    void filesExist ();
    void LoadData ();
    void SaveData ();

public : 

    LibraryManager ();
    ~LibraryManager ();

    void run();

    // Book operations
    void bookMenu();
        void addBook();
        void viewBooks();
            void viewBooksById(bool calledbyViewallBooks = false);
            void viewBooksByAuthor();
            void viewBooksByTitle();
            void viewallBooks();
        void deleteBook();
    
};

#endif // LibraryManager_H