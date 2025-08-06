#include "MemberManager.h"

MemberManager::MemberManager(std::string_view file) : m_file(file) {

}


std::string MemberManager::filesExist(){
    if(!std::filesystem::exists(m_file)){
        return m_file;
    }
    return "";
}

void MemberManager::LoadFile(){
    std::ifstream InfileMember (m_file);

    //load Members vector
    if(InfileMember){
        Member temp;
        while(InfileMember >> temp){
            Members.emplace_back(temp);
        }
    }else{
        std::cerr << "[Fatal ERROR] The required files \""<< m_file <<"\" is not Opening:" << std::endl;
        std::cerr << "Working directory: " << std::filesystem::current_path() << std::endl;
        std::cerr << "Program terminated due to error opening files." << std::endl;
        std::exit(EXIT_FAILURE);
    }
}

void MemberManager::SaveFile() {
    std::ofstream OutfileMember (m_file);

    //save Member vector
    if(OutfileMember){
        for(const Member& src : Members){
            OutfileMember << src << std::endl;
        }
    }else{
        std::cerr << "[Fatal ERROR] The required files \""<< m_file <<"\" is not Opening:" << std::endl;
        std::cerr << "Working directory: " << std::filesystem::current_path() << std::endl;
        std::cerr << "Program terminated due to error opening files." << std::endl;
        std::exit(EXIT_FAILURE);
    }
}

void MemberManager::MemberMenu() {
    while(true){
        std::cout << std::string(4,'-') << "Member Menu" << std::string(4,'-') << std::endl;
        std::cout << "Available options : " << std::endl;
        std::cout << "1. Add Member\n";
        std::cout << "2. Search Member\n";
        std::cout << "3. View Member\n";
        std::cout << "4. Delete Member\n";
        std::cout << "5. BorrowRecords\n";
        std::cout << "0. Return Book\n";
        int choice = getValidInput("Please select an option (0-5): ", 0, 5);

        switch (choice)
        {
        case 0:
            std::cout << "Returning back to LibraryManager" << std::endl;
            std::this_thread::sleep_for(std::chrono::seconds(1));
            return;
        case 1:
            //addMember();
            break;
        case 2:
            //searchMember();
            break;
        case 3:
            //viewMember();
            break;
        case 4:
            //deleteMember();
            break;
        case 5:
            //borrowRecords
            break;
        }
    }
}