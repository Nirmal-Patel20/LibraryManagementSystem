#ifndef BookManager_H
#define BookManager_H

#include <iostream>
#include <fstream>
#include <vector>
#include <filesystem>
#include <chrono>
#include <thread>

#include "Book.h"
#include "InputHelper.h"

class BookManager{
    std::vector<Book> Books;

    // File operations
    std::string m_file;

public : 

    BookManager(std::string_view file = "DataBase/Book.txt");
    ~BookManager() = default;

    std::string filesExist ();
    void LoadFile ();
    void SaveFile ();

    // Book UI operations
    void bookMenu();
        void addBook();
        void viewBooks();
            void viewBooksById(bool indirectCall = false);
            void viewBooksByAuthor();
            void viewBooksByTitle();
            void viewallBooks();
        void deleteBook();
        void availableBooks(bool indirectCall = false);
        void borrowedBook();

    // Book Operations logic
    Book* findBookById(const std::string& id);
    Book* findBookByTitle(const std::string& title);
};

#endif // BookManager_H