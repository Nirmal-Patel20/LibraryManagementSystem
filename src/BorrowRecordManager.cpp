#include "BorrowRecordManager.h"

BorrowRecordManager::BorrowRecordManager(BookManager& bookManager, MemberManager& memberManager, std::string_view file)
                                             : books(bookManager), members(memberManager), m_file(file){

}

std::string BorrowRecordManager::filesExist(){
    if(!std::filesystem::exists(m_file)){
        return m_file;
    }
    return "";
}

void BorrowRecordManager::LoadFile(){
    std::ifstream InfileBorrowRecords (m_file);

    //load BorrowRecords vector
    if(InfileBorrowRecords){
        std::string BookID;
        std::string MemberID;

        while(InfileBorrowRecords >> BookID >> MemberID){
            BorrowRecords[BookID] = MemberID;
        }
    }else{
        std::cerr << "[Fatal ERROR] The required files \""<< m_file <<"\" is not Opening:" << std::endl;
        std::cerr << "Working directory: " << std::filesystem::current_path() << std::endl;
        std::cerr << "Program terminated due to error opening files." << std::endl;
        std::exit(EXIT_FAILURE);
    }
}

void BorrowRecordManager::SaveFile() {
    std::ofstream OutfileBorrowRecord (m_file);

    //save BorrowRecord vector
    if(OutfileBorrowRecord){
        for (const auto& [key,value] : BorrowRecords){
            OutfileBorrowRecord << key << " " << value << std::endl;
        }
    }else{
        std::cerr << "[Fatal ERROR] The required files \""<< m_file <<"\" is not Opening:" << std::endl;
        std::cerr << "Working directory: " << std::filesystem::current_path() << std::endl;
        std::cerr << "Program terminated due to error opening files." << std::endl;
        std::exit(EXIT_FAILURE);
    }
}

void BorrowRecordManager::BorrowMenu() {
    while(true){
        std::cout << std::string(4, '-') << " Borrow Book Menu " << std::string(4, '-') << std::endl;

        std::cout << "1. Borrow Book" << std::endl;
        std::cout << "2. Return Book" << std::endl;

        int choice = getValidInput("Please select an option (0-2): ", 0, 2);

        switch (choice)
        {
        case 1:
            // Borrow Book code
            break;
        case 2:
            // Return Book code
            break;
        case 0:
            std::cout << "Returning to Library Manager." << std::endl;
            std::this_thread::sleep_for(std::chrono::seconds(1));
            return;
        }
    }
}

void BorrowRecordManager::borrowBook(std::string_view MemberId) {
    
}