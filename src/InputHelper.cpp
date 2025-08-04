#include "inputHelper.h"

bool isvalidname(const std::string& Input){
    if(Input.empty()) return false;

    for (const char c : Input){
        if(!std::isalpha(c) && c != ' ') return false;
    }

    return true;
}

std::string getValidName (const std::string& prompt){
    std::cout << prompt;
    std::string Input;

    while(true){
        std::getline(std::cin,Input);

        if(isvalidname(Input)){
            return Input;
        }

        std::cout << "Invalid Input : " << Input << ". Either Input is empty or contains Numbers." << std::endl;
    }
}

std::string getValidString (const std::string& prompt){
    std::cout << prompt;
    std::string Input;

    while(true){
        if(std::getline(std::cin,Input) && !Input.empty()){
            return Input;
        }

        std::cout << "Invalid Input : " << Input << "Input maybe empty" <<  std::endl;
    }
}

std::string getValidID(const std::string& prompt){
    std::cout << prompt;
    std::string ID;
    int code;

    while(true){
        std::getline(std::cin,ID);
        std::istringstream iss(ID);

        if(iss >> code && iss.eof() && ID.length() == 4){
            return ID;
        }

        std::cout << "Invalid Input: \"" << ID  << "\". ID must be 4 numbers (e.g., 1234)." << std::endl;
        std::cout << "Please try again : ";
    }
}

std::string getIdFromUser(const std::string& prompt) {
    std::string id;
    while (true) {
        std::cout << prompt;
        std::getline(std::cin, id);

        if (id.length() == 6 && std::all_of(id.begin(), id.end(), ::isalnum)) {
            return id;
        }

        std::cout << "Invalid Book ID. Please enter a valid alphanumeric ID.\n";
    }
}