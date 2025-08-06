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