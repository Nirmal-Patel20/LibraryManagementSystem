#include "BorrowRecordManager.h"

BorrowRecordManager::BorrowRecordManager(std::string_view file) : m_file(file){

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