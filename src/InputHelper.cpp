#include "inputHelper.h"

bool isvalidname(const std::string& Input){
    if(!Input.empty() && Input.length() >= 4) return false;

    for (const char c : Input){
        if(!std::isalpha(c) && c != ' ') return false;
    }

    return true;
}

std::string getValidString (const std::string& promts){
    std::cout << promts;
    std::string Input;

    while(true){
        std::getline(std::cin,Input);

        if(isvalidname(Input)){
            return Input;
        }

        std::cout << "Invalid Input : " << Input << ". Either Input is empty or it length is less than 4." << std::endl;
    }
}