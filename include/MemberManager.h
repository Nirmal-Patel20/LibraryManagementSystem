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

    // Member operations
};

#endif // MemberManager_H