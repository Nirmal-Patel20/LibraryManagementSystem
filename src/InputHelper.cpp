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
        if(std::getline(std::cin,Input)){
            return Input;
        }

        std::cout << "Invalid Input : " << Input << "Input maybe empty" <<  std::endl;
    }
}

std::string getValidID(const std::string& prompt){
    std::cout << prompt;
    std::string ID;
    char AuthorInitial;
    char BookInitial;
    int code;

    while(true){
        std::getline(std::cin,ID);
        std::istringstream iss(ID);

        if(iss >> BookInitial >> AuthorInitial >> code && iss.eof()){
            return ID;
        }

        std::cout << "Invalid Input: \"" << ID  << "\". ID must be a letter followed by 4 numbers (e.g., A 1234)." << std::endl;
        std::cout << "Please try again : ";
    }
}