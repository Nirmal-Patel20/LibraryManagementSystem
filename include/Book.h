#ifndef Book_H
#define Book_H

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

class Book {
    std::string m_title{"none"};
    std::string m_author{"none"};
    int m_ID{0};
    bool isBorrowed = true;

public : 
    Book () = default;
    Book (std::string_view title, std::string_view author, int ID);

    //getters and setters
    std::string getTitle() const;
    std::string getAuthor() const;
    int getID () const;
    bool getBorrowedStatus () const;
    void setBorrowedStatus (bool status);

    //I/O

    friend std::ostream& operator<< (std::ostream& os, const Book& src);
    friend std::istream& operator>> (std::istream& is, Book& src);
    void display() const;
}; 

#endif // Book_H