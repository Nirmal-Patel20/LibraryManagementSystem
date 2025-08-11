#include "BookManager.h"

BookManager::BookManager(std::string_view file) : m_file(file) {

}

std::string BookManager::filesExist(){
    if(!std::filesystem::exists(m_file)){
        return m_file;
    }
    return "";
}

void BookManager::LoadFile(){
    std::ifstream InfileBook (m_file);

    //load Books vector
    if(InfileBook){
        Book temp;
        while(InfileBook >> temp){
            Books.emplace_back(temp);
        }
    }else{
        std::cerr << "[Fatal ERROR] The required files \""<< m_file <<"\" is not Opening:" << std::endl;
        std::cerr << "Working directory: " << std::filesystem::current_path() << std::endl;
        std::cerr << "Program terminated due to error opening files." << std::endl;
        std::exit(EXIT_FAILURE);
    }
}

void BookManager::SaveFile() {
    std::ofstream OutfileBook (m_file);

    //save book vector
    if(OutfileBook){
        for(const Book& src : Books){
            OutfileBook << src << std::endl;
        }
    }else{
        std::cerr << "[Fatal ERROR] The required files \""<< m_file <<"\" is not Opening:" << std::endl;
        std::cerr << "Working directory: " << std::filesystem::current_path() << std::endl;
        std::cerr << "Program terminated due to error opening files." << std::endl;
        std::exit(EXIT_FAILURE);
    }
}

void BookManager::bookMenu(){
    while(true){
        cleanscreen();
        std::cout << std::string(4, '-') << " book Menu " << std::string(4, '-') << std::endl;
        std::cout << "Available options:" << std::endl;
        std::cout << "1. Add Book" << std::endl;
        std::cout << "2. View Books" << std::endl;
        std::cout << "3. Delete Book" << std::endl;
        std::cout << "4. Available Books" << std::endl;
        std::cout << "5. Borrowed Books" << std::endl;
        std::cout << "0. Return to Library Manager" << std::endl;
        int choice = getValidInput("Please select an option (0-5): ", 0, 5);

        switch (choice)
        {
        case 1:
            addBook();
            break;
        case 2:
            viewBooks();
            break;
        case 3:
            deleteBook();
            break;
        case 4:
            availableBooks();
            break;
        case 5:
            borrowedBook();
            break;
        case 0:
            std::cout << "Returning to Library Manager." << std::endl;
            std::this_thread::sleep_for(std::chrono::seconds(1));
            return;
        }
    }
}

Book* BookManager::findBookById(const std::string& id) {

    auto it = std::find_if(Books.begin(), Books.end(), [&](const Book& b) { return b.getID() == id; });

    return (it != Books.end()) ? &(*it) : nullptr;
}

Book* BookManager::findBookByTitle(const std::string& title) {

    auto it = std::find_if(Books.begin(), Books.end(), [&](const Book& b) { return getUppercase(b.getTitle()) == getUppercase(title); });

    return (it != Books.end()) ? &(*it) : nullptr;
}

void BookManager::addBook() {
    cleanscreen();
    std::string title = getValidString("Enter Title : ");
    std::string author = getValidName("Enter Author name : ");

    std::string IdPrefix{extractInitial(title),extractInitial(author)};
    std::string IdSuffix = getValidID("Enter ID : ");
    std::string bookId = IdPrefix + IdSuffix;

    auto Bookptr = findBookById(bookId);

    if(Bookptr != nullptr){
        std::cout << "A book with ID : " << bookId << " already exists." << std::endl;
        std::cout << "press <Enter> to continue...";
        std::cin.get();
        std::cout << "Returning to Book menu." << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(1));
        return;
    }else{
        Books.emplace_back(title,author,bookId);
        std::cout << "book \""  << title << "\" with ID : " << bookId << " successfully." << std::endl;
        std::cout << "press <Enter> to continue...";
        std::cin.get();
        std::cout << "Returning to Book menu." << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
  
}

void BookManager::viewBooks(){
    cleanscreen();
    std::cout << "Here are the available ways to view books:" << std::endl;
    std::cout << "Select an option to view books:" << std::endl;
    std::cout << "1. View by ID" << std::endl;
    std::cout << "2. View by Author" << std::endl;
    std::cout << "3. View by Title" << std::endl;
    std::cout << "4. view all books(one line)" << std::endl;
    std::cout << "0. Exit" << std::endl;
    int choice = getValidInput("Please select an option (0-4): ", 0, 4);

    switch (choice) {
        case 1:
            viewBooksById();
            break;
        case 2:
            viewBooksByAuthor();
            break;
        case 3:
            viewBooksByTitle();
            break;
        case 4:
            viewallBooks();
            break;
        case 0:
            std::cout << "Exiting the book view menu." << std::endl;
            std::this_thread::sleep_for(std::chrono::seconds(1));
            return;
    }
}

void BookManager::viewBooksById(bool indirectCall) {
    if(!indirectCall){
        cleanscreen();
        std::cout << "A Book ID is formed by taking the first letters of the Book Title and Author's name, followed by a unique four-digit number (e.g., AB1134)." << std::endl;
    }

    std::string BookID = getIdFromUser("Enter Book ID : ");

    auto Bookptr = findBookById(BookID);

    if(Bookptr != nullptr){
        std::cout << std::string(40,'-') << std::endl;
        Bookptr->display();
        std::cout << std::string(40,'-') << std::endl;

        std::cout << "would you like to view more Books[y,n] ? (default: y) : ";
    }else{
        std::cout << "There is no Book with ID : " << BookID << std::endl;
        std::cout << "would you like to try again with diffrent Book ID[y,n] ? (default: y) : ";
    }

    askforTryAgain([&]() {viewBooksById(true);});
}

void BookManager::viewBooksByAuthor() {
    cleanscreen();
    std::string author = getValidName("Enter Author name : ");
    bool found = false;

    for(auto it = Books.begin(); it != Books.end(); ++it){
        if(getUppercase(it->getAuthor()) == getUppercase(author)){
            if(!found){
                std::cout << std::string(15,'=') << "Books by \"" << author << "\"." << std::string(15,'=') << std::endl;
                it->displayOneline();
                found = true;
            }else{
                it->displayOneline();
            }
        }
    }

    if(!found){
        std::cout << "No books found by author \"" << author << "\"." << std::endl;
    }

    std::cout << "would you like to try again with diffrent Book author[y,n] ? (default: y) : ";

    askforTryAgain([&](){viewBooksByAuthor();});
    
}

void BookManager::viewBooksByTitle() {
    cleanscreen();
    std::string title = getValidString("Enter Book Title : ");

    auto Bookptr = findBookByTitle(title);

    if(Bookptr != nullptr){
        std::cout << std::string(40,'-') << std::endl;
        Bookptr->display();
        std::cout << std::string(40,'-') << std::endl;
    }else{
        std::cout << "There is no Book with Title : " << title << std::endl;
    }

    std::cout << "would you like to try again with diffrent Book Title[y,n] ? (default: y) : ";
    askforTryAgain([&](){ viewBooksByAuthor();});
}

void BookManager::viewallBooks() {
    cleanscreen();
    std::cout << "Here are all the books:" << std::endl;
    for(const Book& src : Books){
        src.displayOneline();
    }

    std::cout << "would you like to view specific book details by ID[y,n] ? (default: y) : ";
    
    askforTryAgain([&](){ viewBooksById(true);});
}

void BookManager::deleteBook() {
    cleanscreen();
    std::cout << "Enter the ID of the book you want to delete." << std::endl;
    std::string bookId = getIdFromUser("Book ID : ");

    auto Bookptr = findBookById(bookId);

    if(Bookptr != nullptr){
        std::cout << "Book found : ";
        Bookptr->displayOneline();

        std::cout << "Are you sure to want to delete this book [y,n] ? (default: y) : ";
        char choice = getValidYnN();

        if(choice == 'Y'){
            auto it = std::find_if(Books.begin(), Books.end(),
                            [Bookptr](const Book& b) { return &b == Bookptr; });
            Books.erase(it);
            std::cout << "Book with ID : " << bookId << " deleted successfully." << std::endl;
        } else {
            std::cout << "Deletion cancelled." << std::endl;
        }
        std::cout << "press <Enter> to continue...";
        std::cin.get();
        std::cout << "Returning to Book menu." << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(1));
        return;
    }else{
        std::cout << "No book found with ID : " << bookId << std::endl;

        std::cout << "Would you like to try again with a different Book ID [y,n] ? (default: y) : ";
        askforTryAgain([&](){ deleteBook();});
        return;
    }
}

void BookManager::availableBooks() {
    cleanscreen();
    std::cout << "Searching Available Books:" << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(2));
    bool found = false;

    for(const Book& src : Books){
        if(!src.getBorrowedStatus()){
            src.displayOneline();
            found = true;
        }
    }

    if(!found){
        std::cout << "No available books." << std::endl;
    }

    std::cout << "press <Enter> to continue...";
    std::cin.get();
    std::cout << "Returning to Book menu." << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(1));
}

void BookManager::borrowedBook() {
    cleanscreen();
    std::cout << "Searching borrowed Books : " << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(2));
    bool found = false;

    for(const Book& src : Books){
        if(src.getBorrowedStatus()){
            src.displayOneline();
            found = true;
        }
    }

    if(!found){
        std::cout << "No borrow Books." << std::endl;
    }

    std::cout << "press <Enter> to continue...";
    std::cin.get();
    std::cout << "Returning to Book menu." << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(1));
}