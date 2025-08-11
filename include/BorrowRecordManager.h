#ifndef BorrowRecordManager_H
#define BorrowRecordManager_H

#include <iostream>
#include <fstream>
#include <filesystem>
#include <chrono>
#include <thread>
#include <unordered_map>
#include "InputHelper.h"

class Book; // Forward declaration
class BookManager; // Forward declaration
class MemberManager; // Forward declaration

class BorrowRecordManager {
    std::unordered_map<std::string, std::string> BorrowRecords; //BookID to MemberID
    BookManager& books;
    MemberManager& members;

    // File operations
    std::string m_file;

public : 

    BorrowRecordManager(BookManager& bookManager, MemberManager& memberManager, std::string_view file = "DataBase/BorrowRecords.txt");
    ~BorrowRecordManager() = default;

    std::string filesExist ();
    void LoadFile ();
    void SaveFile ();

    //Borrowing operations
    void BorrowMenu ();
        void borrowBook();
        void returnBook();
        //void borrowRecord(std::string_view MemberId = "Not given");

    // Helper functions
    std::vector<Book*> getBorrowedBooksRecord(const std::string& MemberId);
};

#endif // BorrowRecordManager_H