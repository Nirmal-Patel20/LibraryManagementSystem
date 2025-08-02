#ifndef LibraryManager_H
#define LibraryManager_H

#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>
#include <filesystem>

#include "Book.h"
#include "Member.h"
#include "InputHelper.h"

class LibraryManager {
    std::vector<Book> Books;
    std::vector<Member> Members;
    std::unordered_map<std::string , std::string> borrowRecords; // bookID -> memberID

    //checkup,Load and Save
    void filesExist ();
    void LoadData ();
    void SaveData ();

public : 

    LibraryManager ();

    ~LibraryManager ();
};

#endif // LibraryManager_H