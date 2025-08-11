#include "Member.h"

Member::Member (std::string_view name,std::string Member_ID) : m_name (name), m_Member_ID(Member_ID){

}

std::string Member::getName () const {
    return m_name;
} 

std::string Member::getID () const {
    return m_Member_ID;
}

int Member::getBorrowedBooks() const {
    return m_borrowedBooks;
}

void Member::incrementBorrowedBooks() {
    ++m_borrowedBooks;
}

void Member::decrementBorrowedBooks() {
    --m_borrowedBooks;
}

std::ostream& operator<< (std::ostream& os,const Member& src){
    os << src.m_name << "," << src.m_Member_ID << "," << src.m_borrowedBooks;
    return os;
}

std::istream& operator>> (std::istream& is,Member& src){
    std::string line;
    if(std::getline(is,line)){
        std::istringstream iss (line);

        std::getline(iss,src.m_name,',');

        std::getline(iss,src.m_Member_ID,',');

        iss >> src.m_borrowedBooks;
    }

    return is;
}

void Member::displayOneLine () const {
    std::cout << "Name : " << m_name << ", ID : " << m_Member_ID << ", Borrowed Books : " << m_borrowedBooks << std::endl;
}

void Member::display() const {
    std::cout << "Name : " << m_name << ", ID : " << m_Member_ID << ", Borrowed status : ";
    if(m_borrowedBooks > 0) {
        std::cout << m_borrowedBooks << std::endl;
        std::cout << "Borrowed Books: \n";
        //MemberManager handles the display of borrowed books
    } else {
        std::cout << "No books borrowed." << std::endl;
    }
}
