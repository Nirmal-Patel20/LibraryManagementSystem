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

        std::cout << "Invalid Input : " << Input << " Input maybe empty" <<  std::endl;
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

bool isValidBookID(const std::string ID){
    return ID.length() == 6 && std::all_of(ID.begin(), ID.end(), ::isalnum) && std::isalpha(ID[0]) && std::isalpha(ID[1]);
}

bool isValidMemberID(const std::string ID){
    return ID.length() == 5 && std::all_of(ID.begin(), ID.end(), ::isalnum) && std::isalpha(ID[0]);
}

std::string getIdFromUser(const std::string& prompt,bool callByMemberManager) {
    std::string id;
    std::cout << prompt;
    while (true) {
        std::getline(std::cin, id);

        if(!callByMemberManager){
            if(isValidBookID(id)){
                id[0] = std::toupper(id[0]);
                id[1] = std::toupper(id[1]);
                return id;
            }

            std::cout << "Invalid Book ID. Please enter a valid alphanumeric ID (e.g., LH1234).\n";

        }else{
            if(isValidMemberID (id)){
                id[0] = std::toupper(id[0]);
                return id;
            }
            
            std::cout << "Invalid Book ID. Please enter a valid alphanumeric ID (e.g., L1234).\n";
        }

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

        if(Input.length() == 1){
            char choice = std::toupper(Input[0]);
            if(choice == 'Y' || choice == 'N'){
                return choice;
            }
            std::cout << "only 'Y' and 'N'" << std::endl;
        }else if(Input.empty()){
            return 'Y'; // Default to 'Y' if input is empty
        }
        std::cout << "invalid Input. " << "please try again : ";
    }
}

void cleanscreen() {
    // Clear the console screen
    std::cout << "\033[2J\033[1;1H"; // ANSI escape code to clear the screen and move cursor to top-left
}

void askforTryAgain(std::function<void()> callfunction){
    char choice = getValidYnN();
    if(choice == 'Y'){
        callfunction();
    } else {
        std::cout << "press <Enter> to continue...";
        std::cin.get();
        std::cout << "Returning back to menu." << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}