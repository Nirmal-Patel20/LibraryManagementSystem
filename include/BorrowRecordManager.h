#ifndef BorrowRecordManager_H
#define BorrowRecordManager_H

#include <iostream>
#include <fstream>
#include <filesystem>
#include <chrono>
#include <thread>
#include <unordered_map>

class BorrowRecordManager {
    std::unordered_map<std::string, std::string> BorrowRecords; //BookID to MemberID

    // File operations
    std::string m_file;

public : 

    BorrowRecordManager(std::string_view file = "DataBase/BorrowRecords.txt");
    ~BorrowRecordManager() = default;

    std::string filesExist ();
    void LoadFile ();
    void SaveFile ();
};

#endif // BorrowRecordManager_H