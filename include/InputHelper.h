#ifndef InputHandler_H
#define InputHandler_H

#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>
#include <chrono>
#include <thread>
#include <functional>

template <typename T>
T getValidInput (const std::string& promts, T min, T max){
    std::cout << promts;

    std::string line;
    T value;

    while(true){
        std::getline(std::cin,line);
        std::istringstream iss(line);

        if(iss >> value && iss.eof() && value >= min && value <= max){
            return value;
        }

        std::cout << "Invalid input. please enter a value between " << min << " and " << max << ".\n";
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

bool isvalidname(const std::string& Input);

std::string getValidName (const std::string& prompt);

std::string getValidString (const std::string& prompt);

std::string getValidID(const std::string& promts);

std::string getIdFromUser(const std::string& prompt, bool callByMemberManager = false);

char extractInitial(const std::string& str, char fallback = 'X');

std::string getUppercase(const std::string& src);

char getValidYnN();

void cleanscreen();

void askforTryAgain(std::function<void()> callfunction);


#endif // InputHandler_H