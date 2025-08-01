#include "LibraryManager.h"

LibraryManager::LibraryManager () {
    filesExist(); //check files
    LoadData(); //load files
}

LibraryManager::~LibraryManager () {
    SaveData();
}

void LibraryManager::filesExist() {
    const std::vector<std::string> requiredFiles = {
        "Database/Book.txt",
        "Database/Member.txt",
        "Database/BorrowRecords.txt"
    };

    std::vector<std::string> missingFiles;

    for (const auto& path : requiredFiles) {
        if (!std::filesystem::exists(path)) {
            missingFiles.push_back(path);
        }
    }

    if (!missingFiles.empty()) {
        std::cerr << "[Fatal ERROR] The following required files are missing:" << std::endl;
        for (const auto& file : missingFiles) {
            std::cerr << "  - " << file << std::endl;
        }
        std::cerr << "Working directory: " << std::filesystem::current_path() << std::endl;
        std::cerr << "Program terminated due to missing files." << std::endl;
        std::exit(EXIT_FAILURE);
    }
}

void LibraryManager::LoadData() {
    std::ifstream InFileBook ("DataBase/Book.txt");
    std::ifstream InFileMember ("DataBase/Member.txt");
    std::ifstream InFileBorrowRecords ("DataBase/BorrowRecords");

    std::vector<std::string> ErrorOpeningFiles;

    //load Books vector
    if(InFileBook){
        Book temp;
        while(InFileBook >> temp){
            Books.emplace_back(temp);
        }
    }else{
        ErrorOpeningFiles.emplace_back("DataBase/Book.txt");
    }

    //load Members vector
    if(InFileMember){
        Member temp;
        while(InFileMember >> temp){
            Members.emplace_back(temp);
        }
    }else{
        ErrorOpeningFiles.emplace_back("DataBase/Member.txt");
    }

    //load BorrowRecord
    if(InFileBorrowRecords){
        std::string BookID;
        std::string MemberID;

        while(InFileBorrowRecords >> BookID >> MemberID){
            borrowRecords[BookID] = MemberID;
        }
    }else{
        ErrorOpeningFiles.emplace_back("DataBase/BorrowRecords.txt");
    }


    if (!ErrorOpeningFiles.empty()) {
        std::cerr << "[Fatal ERROR] The following required files are not Opening:" << std::endl;
        for (const auto& file : ErrorOpeningFiles) {
            std::cerr << "  - " << file << std::endl;
        }
        std::cerr << "Working directory: " << std::filesystem::current_path() << std::endl;
        std::cerr << "Program terminated due to missing files." << std::endl;
        std::exit(EXIT_FAILURE);
    }
}

void LibraryManager::SaveData() {
    std::ofstream OutFileBook ("DataBase/Book.txt");
    std::ofstream OutFileMember ("DataBase/Member.txt");
    std::ofstream OutFileBorrowRecords ("DataBase/BorrowRecords");

    std::vector<std::string> ErrorOpeningFiles;

    //save BorrowRecords
    if(OutFileBorrowRecords){
        for(const auto& [key,value] : borrowRecords){
            OutFileBorrowRecords << key << " " << value << std::endl;
        }
    }else{
        ErrorOpeningFiles.emplace_back("DataBase/BorrowRecords");
    }

    //save Members
    if(OutFileBook){
        for(const Member& src : Members){
            OutFileBook << src << std::endl;
        }
    }else{
        ErrorOpeningFiles.emplace_back("DataBase/Member.txt");
    }

    //save Books
    if(OutFileBook){
        for(const Book& src : Books){
            OutFileBook << src << std::endl;
        }
    }else{
        ErrorOpeningFiles.emplace_back("DataBase/Book.txt");
    }

    if (!ErrorOpeningFiles.empty()) {
        std::cerr << "[Fatal ERROR] The following required files are not Opening:" << std::endl;
        for (const auto& file : ErrorOpeningFiles) {
            std::cerr << "  - " << file << std::endl;
        }
        std::cerr << "Working directory: " << std::filesystem::current_path() << std::endl;
        std::cerr << "Program terminated due to missing files." << std::endl;
        std::exit(EXIT_FAILURE);
    }
}