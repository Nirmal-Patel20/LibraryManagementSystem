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
        std::cout << "Please try again : ";
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
        std::cout << "Please try again : ";
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
    std::cout << prompt;
    while (true) {
        std::getline(std::cin, id);

        if (id.length() == 6 && std::all_of(id.begin(), id.end(), ::isalnum)){
            if(std::isalpha(*id.begin()) && std::isalpha(*(++id.begin()))){
                *id.begin() = std::toupper(*id.begin());
                *(++id.begin()) = std::toupper(*(++id.begin()));
                return id;
            }
            
        }

        std::cout << "Invalid Book ID. Please enter a valid alphanumeric ID (e.g., LH1234).\n";
        std::cout << "Please try again : ";
    }
}

char extractInitial(const std::string& str, char fallback) {
    for (char c : str) {
        if (std::isalpha(c)) {
            return std::toupper(c); // Normalize to uppercase
        }
    }
    return fallback;
}

std::string getUppercase(const std::string& src) {
    std::string Uppercase;

    for (const char& c : src) {
        if (std::isalpha(static_cast<unsigned char>(c))) {
            Uppercase += std::toupper(static_cast<unsigned char>(c));
        } else {
            Uppercase += c;
        }
    }

    return Uppercase;
}

char getValidYnN(){
    std::string Input;

    while(true){
        std::getline(std::cin,Input);

        if(!Input.empty() && Input.length() == 1){
            char choice = std::toupper(Input[0]);
            if(choice == 'Y' || choice == 'N'){
                return choice;
            }
            std::cout << "only 'Y' and 'N'" << std::endl;
        }
        std::cout << "invalid Input. " << "please try again : ";
    }
}