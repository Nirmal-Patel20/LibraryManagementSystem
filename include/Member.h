#ifndef Member_H
#define Member_H

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>


class Member {
    std::string m_name{"None"};
    std::string m_Member_ID{"None"};

public : 
    Member () = default;
    Member (std::string_view name,std::string Member_ID);

    //getters
    std::string getName () const;
    std::string getID() const;

    //I/O
    friend std::ostream& operator<< (std::ostream& os,const Member& src);
    friend std::istream& operator>> (std::istream& is,Member& src);
    void display () const;
};

#endif // Member_H