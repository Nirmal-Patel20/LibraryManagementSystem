#include "Member.h"

Member::Member (std::string_view name,std::string Member_ID) : m_name (name), m_Member_ID(Member_ID){

}

std::string Member::getName () const {
    return m_name;
} 

std::string Member::getID () const {
    return m_Member_ID;
}

std::ostream& operator<< (std::ostream& os,const Member& src){
    os << src.m_name << "," << src.m_Member_ID;
    return os;
}

std::istream& operator>> (std::istream& is,Member& src){
    std::string line;
    if(std::getline(is,line)){
        std::istringstream iss (line);
        std::string stringTo;

        std::getline(iss,src.m_name,',');

        std::getline(iss,stringTo);
        src.m_Member_ID = std::stoi(stringTo);
    }

    return is;
}

void Member::display() const {
    std::cout << "Name : " << m_name << ", ID : " << m_Member_ID << std::endl;
}