#ifndef Book_H
#define Book_H

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

class Book {
    std::string m_title{"none"};
    std::string m_author{"none"};
    std::string m_ID{"none"};
    bool isBorrowed = true;

public : 
    Book () = default;
    Book (std::string_view title, std::string_view author, std::string ID);

    //getters and setters
    std::string getTitle() const;
    std::string getAuthor() const;
    std::string getID () const;
    bool getBorrowedStatus () const;
    void setBorrowedStatus (bool status);

    //I/O

    friend std::ostream& operator<< (std::ostream& os, const Book& src);
    friend std::istream& operator>> (std::istream& is, Book& src);
    void display() const;
}; 

#endif // Book_H