#ifndef MemberManager_H
#define MemberManager_H

#include <iostream>
#include <fstream>
#include <vector>
#include <filesystem>
#include <chrono>
#include <thread>

#include "Member.h"
#include "InputHelper.h"

class MemberManager {
    std::vector<Member> Members;

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
};

#endif // MemberManager_H