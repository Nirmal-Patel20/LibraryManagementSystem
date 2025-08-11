#ifndef MemberManager_H
#define MemberManager_H

#include <iostream>
#include <fstream>
#include <vector>
#include <filesystem>
#include <chrono>
#include <thread>

// Forward declaration of BorrowRecordManager to avoid circular dependency.
// We only store a pointer here, so full definition not required in this header.

#include "Member.h"
#include "InputHelper.h"

class Book; // Forward declaration
class BorrowRecordManager; // Forward declaration

class MemberManager {
    std::vector<Member> Members;
    BorrowRecordManager* borrowRecords = nullptr;

    // File operations
    std::string m_file;

public : 

    MemberManager(std::string_view = "DataBase/Member.txt");
    ~MemberManager() = default;

    std::string filesExist ();
    void LoadFile ();
    void SaveFile ();

    // Member UI operations
    void MemberMenu();
        void addMember();
        void searchMember(bool indirectCall = false);
        void viewAllMembers();
        void deleteMember();

    // Member operations Logic
    Member* findMemberById(const std::string& id);
    Member* findMemberByName(const std::string& name);

    // Setter to provide a pointer to BorrowRecordManager after construction.
    void setBorrowRecordManager(BorrowRecordManager* borrowRecordManager);
};

#endif // MemberManager_H