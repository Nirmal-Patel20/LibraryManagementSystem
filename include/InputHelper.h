#ifndef InputHandler_H
#define InputHandler_H

#include <iostream>
#include <string>
#include <sstream>

template <typename T>
T getValidInput (const std::string& promts, T max, T min){
    std::cout << promts;

    std::string line;
    T value;

    while(true){
        std::getline(std::cin,line);
        std::istringstream iss(line);

        if(iss >> value && iss.eof() && value >= max && value <= min){
            return value;
        }

        std::cout << "Invalid input. please enter a value between " << max << " and " << min << ".\n";
        std::cout << "please try again : "; 
    }
}

template <typename T>
T getValidInput (const std::string& promts){
    std::cout << promts;

    std::string line;
    T value;

    while(true){
        std::getline(std::cin,line);
        std::istringstream iss(line);

        if(iss >> value && iss.eof()){
            return value;
        }

        std::cout << "Invalid input. please try again : ";
    }
}

bool isvalidname(const std::string Input);

std::string getValidString (const std::string& promts);


#endif // InputHandler_H