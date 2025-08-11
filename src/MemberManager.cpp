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
        cleanscreen();
        std::cout << std::string(4,'-') << "Member Menu" << std::string(4,'-') << std::endl;
        std::cout << "Available options : " << std::endl;
        std::cout << "1. Add Member\n";
        std::cout << "2. Search Member\n";
        std::cout << "3. View all Members\n";
        std::cout << "4. Delete Member\n";
        std::cout << "0. Return to Library Manager" << std::endl;
        int choice = getValidInput("Please select an option (0-4): ", 0, 4);

        switch (choice)
        {
        case 0:
            std::cout << "Returning back to LibraryManager" << std::endl;
            std::this_thread::sleep_for(std::chrono::seconds(1));
            return;
        case 1:
            addMember();
            break;
        case 2:
            searchMember();
            break;
        case 3:
            viewAllMembers();
            break;
        case 4:
            deleteMember();
            break;
        }
    }
}

Member* MemberManager::findMemberById(const std::string& id) {
    auto it = std::find_if(Members.begin(), Members.end(), [&](const Member& src) {
        return src.getID() == id;
    });
    return (it != Members.end()) ? &(*it) : nullptr;
}

Member* MemberManager::findMemberByName(const std::string& name) {
    auto it = std::find_if(Members.begin(), Members.end(), [&](const Member& src) {
        return getUppercase(src.getName()) == getUppercase(name);
    });
    return (it != Members.end()) ? &(*it) : nullptr;
}

void MemberManager::addMember() {
    cleanscreen();
    std::string Name = getValidName("Enter Name : ");

    std::string IDprefic{extractInitial(Name)};

    std::string IDsuffix = getValidID("Enter Member ID : ");
    std::string MemberID = IDprefic + IDsuffix;

    auto itID = findMemberById(MemberID);
    if(itID != nullptr){
        std::cout << "Member with ID : " << MemberID << " already exists." << std::endl;
        std::cout << "Returning to Member menu." << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(2));
        return;
    }

    auto itName = findMemberByName(Name);
    if(itName != nullptr){
        std::cout << "Member with Name : " << Name << " already exists." << std::endl;
        std::cout << "Returning to Member menu." << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(2));
        return;
    }

    Members.emplace_back(Name, MemberID);
    std::cout << "Member \"" << Name << "\" with ID : " << MemberID << " added successfully." << std::endl;
    std::cout << "press <Enter> to continue...";
    std::cin.get();
    std::cout << "Returning to Member menu." << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(1));
}

void MemberManager::searchMember(bool indirectCall) {
    if(!indirectCall){
        cleanscreen();
        std::cout << "A Member ID is formed by taking the first letter of the Member's name, followed by a unique four-digit number (e.g., N2012)." << std::endl;
    }
    
    std::string searchID = getIdFromUser("Enter Member ID : ", true);
    
    auto Memberptr = findMemberById(searchID);

    if(Memberptr != nullptr){
        std::cout << "Member found: ";
        Memberptr->display();
        
        std::cout << "would you like to view more Members[y,n] ? (default: y) : ";
    } else {
        std::cout << "No member found with ID: " << searchID << std::endl;
        std::cout << "would you like to try again with diffrent Member ID[y,n] ? (default: y) : ";
    }

    askforTryAgain([&]() {searchMember(true);});
}

void MemberManager::viewAllMembers(){
    cleanscreen();
    std::cout << "Here are all the Members:" << std::endl;
    for(const Member& src : Members){
        src.displayOneLine();
    }

    std::cout << "would you like to search Member By ID [y,n]? (default y) : ";
    askforTryAgain([&](){searchMember(true);});
}

void MemberManager::deleteMember() {
    cleanscreen();
    std::string searchID = getIdFromUser("Enter Member ID to delete: ", true);

    auto Memberptr = findMemberById(searchID);

    if(Memberptr != nullptr){
        std::cout << "Member found: ";
        Memberptr->display();

        std::cout << "Are you sure to want to delete this member [y,n] ? (default: y) : ";
        char choice = getValidYnN();

        if(choice == 'y' || choice == 'Y'){
            auto it = std::find_if(Members.begin(), Members.end(), [&](const Member& src) {
                return &src == Memberptr;
            });
            Members.erase(it);
            std::cout << "Member with ID: " << searchID << " deleted successfully." << std::endl;
        } else {
            std::cout << "Deletion cancelled." << std::endl;
        }
        std::cout << "press <Enter> to continue...";
        std::cin.get();
        std::cout << "Returning to Member menu." << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(1));
    } else {
        std::cout << "No member found with ID: " << searchID << std::endl;

        std::cout << "Would you like to try again with a different Member ID [y,n] ? (default: y) : ";
        askforTryAgain([&](){deleteMember();});
    }

}