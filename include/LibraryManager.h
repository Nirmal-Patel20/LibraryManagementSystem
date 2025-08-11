#ifndef LibraryManager_H
#define LibraryManager_H

#include <iostream>
#include <chrono>
#include <thread>

// Include full headers here because LibraryManager owns full objects of these classes
#include "BookManager.h"
#include "MemberManager.h"
#include "BorrowRecordManager.h"
#include "InputHelper.h"

class LibraryManager {
    BookManager books;
    MemberManager members;
    BorrowRecordManager borrowRecords;

public : 

    LibraryManager ();
    ~LibraryManager ();

    void checkFiles ();

    void MainMenu ();

    
    
};

#endif // LibraryManager_H