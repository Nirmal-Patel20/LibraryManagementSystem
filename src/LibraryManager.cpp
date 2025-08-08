#include "LibraryManager.h"

LibraryManager::LibraryManager() : borrowRecords(books, members) {
    checkFiles();
    // Load data from files
    books.LoadFile();
    members.LoadFile();
    borrowRecords.LoadFile();
}

LibraryManager::~LibraryManager() {
    // Save data to files
    borrowRecords.SaveFile();
    members.SaveFile();
    books.SaveFile();
}

void LibraryManager::checkFiles() {
    std::vector<std::string> missingfiles;

    std::string bookFile = books.filesExist();
    std::string memberFile = members.filesExist();
    std::string borrowFile = borrowRecords.filesExist();

    if (!bookFile.empty()) missingfiles.push_back(bookFile);
    if (!memberFile.empty()) missingfiles.push_back(memberFile);
    if (!borrowFile.empty()) missingfiles.push_back(borrowFile);

    if (!missingfiles.empty()) {
        std::cout << "The following files are missing:" << std::endl;
        for (const auto& file : missingfiles) {
            std::cout << file << std::endl;
        }
        std::cerr << "Working directory: " << std::filesystem::current_path() << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(2));
        std::cout << std::string(40,'-') << std::endl;
        std::cerr << "please ensure you are in the correct working directory." << std::endl;
        std::cerr << "Program terminated due to missing files." << std::endl;
        std::exit(EXIT_FAILURE);
    }
}

void LibraryManager::MainMenu() {
    while (true) {
        cleanscreen();
        std::cout << std::string(4, '-') << " Library Manager " << std::string(4, '-') << std::endl;
        std::cout << "Available options:" << std::endl;
        std::cout << "1. Book Menu" << std::endl;
        std::cout << "2. Member Menu" << std::endl;
        std::cout << "0. Exit" << std::endl;

        int choice = getValidInput("Please select an option (0-2): ", 0, 2);
        switch (choice)
        {
        case 0:
            std::cout << "Exiting the Library Manager." << std::endl;
            return;
        case 1:
            books.bookMenu();
            break;
        case 2:
            members.MemberMenu();
            break;
        }
    }
}
