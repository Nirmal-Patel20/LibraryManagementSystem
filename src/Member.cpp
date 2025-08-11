#include "Member.h"

Member::Member (std::string_view name,std::string Member_ID) : m_name (name), m_Member_ID(Member_ID){

}

std::string Member::getName () const {
    return m_name;
} 

std::string Member::getID () const {
    return m_Member_ID;
}

int Member::getBorrowedBooksCount() const {
    return m_borrowedBooksCount;
}

void Member::incrementBorrowedBooksCount() {
    ++m_borrowedBooksCount;
}

void Member::decrementBorrowedBooksCount() {
    --m_borrowedBooksCount;
}

std::ostream& operator<< (std::ostream& os,const Member& src){
    os << src.m_name << "," << src.m_Member_ID << "," << src.m_borrowedBooksCount;
    return os;
}

std::istream& operator>> (std::istream& is,Member& src){
    std::string line;
    if(std::getline(is,line)){
        std::istringstream iss (line);

        std::getline(iss,src.m_name,',');

        std::getline(iss,src.m_Member_ID,',');

        iss >> src.m_borrowedBooksCount;
    }

    return is;
}

void Member::displayOneLine () const {
    std::cout << "Name : " << m_name << ", ID : " << m_Member_ID << ", Borrowed Books : " << m_borrowedBooksCount << std::endl;
}

void Member::display() const {
    std::cout << "Name : " << m_name << ", ID : " << m_Member_ID << ", Borrowed status : ";
    if(m_borrowedBooksCount > 0) {
        std::cout << m_borrowedBooksCount << std::endl;
        std::cout << "Borrowed Books: \n";
        //MemberManager handles the display of borrowed books
    } else {
        std::cout << "No books borrowed." << std::endl;
    }
}
