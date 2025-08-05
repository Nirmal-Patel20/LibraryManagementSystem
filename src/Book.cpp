#include "Book.h"

Book::Book (std::string_view title, std::string_view author, std::string ID) : m_title(title), m_author(author), m_ID(ID) {

}

std::string Book::getTitle () const {
    return m_title;
}

std::string Book::getAuthor () const {
    return m_author;
}

std::string Book::getID () const {
    return m_ID;
}

bool Book::getBorrowedStatus () const {
    return isBorrowed;
}

void Book::setBorrowedStatus (bool status){
    isBorrowed = status;
}

std::ostream& operator<< (std::ostream& os, const Book& src){
    os << src.m_title << "," << src.m_author << "," << src.m_ID << "," << src.isBorrowed;
    return os;
}

std::istream& operator>> (std::istream& is, Book& src){
    std::string line;
    if(std::getline(is,line)){
        std::stringstream iss(line);
        std::string Stringto;

        std::getline(iss,src.m_title,',');
        std::getline(iss,src.m_author,',');
        std::getline(iss,src.m_ID,',');
        std::getline(iss,Stringto);

        src.isBorrowed = (Stringto == "1");
    }
    return is;
}

void Book::display() const{
    std::cout << "Title : " << m_title << std::endl;
    std::cout << "Author : " << m_author << ", ID : " << m_ID << std::endl;
    std::cout << "Status : " << (isBorrowed ? "Borrowed" : "Available") << std::endl;

}

void Book::displayOneline() const{
    std::cout << "title : \"" << m_title << "\" Book ID : " << m_ID << " Status : " << (isBorrowed ? "Borrowed" : "Available") << std::endl;

}