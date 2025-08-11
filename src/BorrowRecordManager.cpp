#include "BorrowRecordManager.h"
#include "BookManager.h" // Full definition needed here to use their utility methods and BookManager include Book definition
#include "MemberManager.h"

BorrowRecordManager::BorrowRecordManager(BookManager& bookManager, MemberManager& memberManager, std::string_view file)
                                             : books(bookManager), members(memberManager), m_file(file){

}

std::string BorrowRecordManager::filesExist(){
    if(!std::filesystem::exists(m_file)){
        return m_file;
    }
    return "";
}

void BorrowRecordManager::LoadFile(){
    std::ifstream InfileBorrowRecords (m_file);

    //load BorrowRecords vector
    if(InfileBorrowRecords){
        std::string BookID;
        std::string MemberID;

        while(InfileBorrowRecords >> BookID >> MemberID){
            BorrowRecords[BookID] = MemberID;
        }
    }else{
        std::cerr << "[Fatal ERROR] The required files \""<< m_file <<"\" is not Opening:" << std::endl;
        std::cerr << "Working directory: " << std::filesystem::current_path() << std::endl;
        std::cerr << "Program terminated due to error opening files." << std::endl;
        std::exit(EXIT_FAILURE);
    }
}

void BorrowRecordManager::SaveFile() {
    std::ofstream OutfileBorrowRecord (m_file);

    //save BorrowRecord vector
    if(OutfileBorrowRecord){
        for (const auto& [key,value] : BorrowRecords){
            OutfileBorrowRecord << key << " " << value << std::endl;
        }
    }else{
        std::cerr << "[Fatal ERROR] The required files \""<< m_file <<"\" is not Opening:" << std::endl;
        std::cerr << "Working directory: " << std::filesystem::current_path() << std::endl;
        std::cerr << "Program terminated due to error opening files." << std::endl;
        std::exit(EXIT_FAILURE);
    }
}

void BorrowRecordManager::BorrowMenu() {
    while(true){
        cleanscreen();
        std::cout << std::string(4, '-') << " Borrow Book Menu " << std::string(4, '-') << std::endl;

        std::cout << "1. Borrow Book" << std::endl;
        std::cout << "2. Return Book" << std::endl;
        std::cout << "0. Return to Library Manager" << std::endl;

        int choice = getValidInput("Please select an option (0-2): ", 0, 2);

        switch (choice)
        {
        case 1:
            borrowBook();
            break;
        case 2:
            returnBook();
            break;
        case 0:
            std::cout << "Returning to Library Manager." << std::endl;
            std::this_thread::sleep_for(std::chrono::seconds(1));
            return;
        }
    }
}

void BorrowRecordManager::borrowBook() {
    cleanscreen();
    std::string MemberId = getIdFromUser("Enter Member ID : ",true); //for member ID
    std::cout << "searching for Member ID: " << MemberId << std::endl;
    auto Memberptr = members.findMemberById(MemberId);

    if(Memberptr != nullptr){
        std::cout << "Member found: ";
        Memberptr->displayOneLine();
        if(Memberptr->getBorrowedBooksCount() >= 3){
            std::cout << "Member has reached the maximum limit(3) of borrowed books." << std::endl;
            std::cout << "press <Enter> to continue...";
            std::cin.get();
            std::cout << "Returning to Book menu." << std::endl;
            std::this_thread::sleep_for(std::chrono::seconds(1));
            return;
        }
    }else{
        std::cout << "No member found with ID: " << MemberId << std::endl;
        std::cout << "press <Enter> to continue...";
        std::cin.get();
        std::cout << "Returning back to menu." << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(1));
        return;
    }

    std::cout << "would you like to see the available books? [y/n] (default: y) : ";
    char choice = getValidYnN();
    if(choice == 'Y'){
        std::cout << "Book is available for borrowing." << std::endl;
        books.availableBooks(true); //indirect call to availableBooks
    }

    std::string bookId = getIdFromUser("Enter Book ID : "); //for book ID
    std::cout << "searching for Book ID: " << bookId << std::endl;
    auto Bookptr = books.findBookById(bookId);

    if(Bookptr != nullptr){
        std::cout << "Book found: ";
        Bookptr->displayOneline();
        if(Bookptr->getBorrowedStatus()){
            std::cout << "This book is already borrowed." << std::endl;
            std::cout << "press <Enter> to continue...";
            std::cin.get();
            std::cout << "Returning back to menu." << std::endl;
            std::this_thread::sleep_for(std::chrono::seconds(1));
            return;
        }
    }else{
        std::cout << "No book found with ID: " << bookId << std::endl;
        std::cout << "press <Enter> to continue...";
        std::cin.get();
        std::cout << "Returning back to menu." << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(1));
        return;
    }

    // If we reach here, the book is available for borrowing
    BorrowRecords[bookId] = MemberId;
    Bookptr->setBorrowedStatus(true);
    Memberptr->incrementBorrowedBooksCount();
    std::cout << "Book borrowed successfully." << std::endl;
    std::cout << "press <Enter> to continue...";
    std::cin.get();
    std::cout << "Returning back to menu." << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(1));
}

void BorrowRecordManager::returnBook(){
    cleanscreen();
    std::string MemberId = getIdFromUser("Enter Member ID : ",true); //for member ID
    std::cout << "searching for Member ID: " << MemberId << std::endl;
    auto Memberptr = members.findMemberById(MemberId);
    std::vector<Book*> borrowRecordsOfMember;
    int returnBookIndex = 0;



    if(Memberptr != nullptr){


        if(Memberptr->getBorrowedBooksCount() != 0){
            borrowRecordsOfMember = getBorrowedBooksRecord(MemberId);

            std::cout << "Member found: ";
            Memberptr->display();
            int i = 1;

            for(const auto& src : borrowRecordsOfMember){
                std::cout << i << ". Title : " << src->getTitle() << ", BookId : " << src->getID() << " .\n";
                ++i;
            }

        }else{
            std::cout << "Member found: ";
            Memberptr->displayOneLine();
            std::cout << "this member has not borrowed any books." << std::endl;
            std::cout << "press <Enter> to continue...";
            std::cin.get();
            std::cout << "Returning back to menu." << std::endl;
            std::this_thread::sleep_for(std::chrono::seconds(1));
            return;
        }
    }else{
        std::cout << "No member found with ID: " << MemberId << std::endl;
        std::cout << "press <Enter> to continue...";
        std::cin.get();
        std::cout << "Returning back to menu." << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(1));
        return;
    }

    returnBookIndex = getValidInput(("Enter the number of the book you want to return (1-" 
                        + std::to_string(borrowRecordsOfMember.size()) + "): "), 1, static_cast<int>(borrowRecordsOfMember.size()));
    --returnBookIndex; // Convert to 0-based index

    //if we reach here, the book is ready to return
    BorrowRecords.erase(borrowRecordsOfMember[returnBookIndex]->getID());
    borrowRecordsOfMember[returnBookIndex]->setBorrowedStatus(false);
    members.findMemberById(MemberId)->decrementBorrowedBooksCount();
    std::cout << "Book returned successfully." << std::endl;
    std::cout << "press <Enter> to continue...";
    std::cin.get();
    std::cout << "Returning back to menu." << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(1));
}

std::vector<Book*> BorrowRecordManager::getBorrowedBooksRecord(const std::string& MemberId){

    std::vector<Book*> Bookptr;
    
    for(const auto& src : BorrowRecords){
        if(src.second == MemberId){
            Bookptr.emplace_back(books.findBookById(src.first));
        }
    }

    return Bookptr;
}