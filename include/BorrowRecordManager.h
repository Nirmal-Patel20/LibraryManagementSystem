#ifndef BorrowRecordManager_H
#define BorrowRecordManager_H

#include <iostream>
#include <fstream>
#include <filesystem>
#include <chrono>
#include <thread>
#include <unordered_map>
#include "InputHelper.h"
#include "BookManager.h"
#include "MemberManager.h"

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
        void borrowBook(std::string_view MemberId = "",bool calledbyMemberManager = false);
        //void returnBook(std::string_view MemberId = "Not given");
        //void borrowRecord(std::string_view MemberId = "Not given");

};

#endif // BorrowRecordManager_H