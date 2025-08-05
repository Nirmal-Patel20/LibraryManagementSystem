#include "LibraryManager.h"

LibraryManager::LibraryManager () {
    filesExist(); //check files
    LoadData(); //load files
}

LibraryManager::~LibraryManager () {
    SaveData();
}

void LibraryManager::filesExist() {
    const std::vector<std::string> requiredFiles = {
        "Database/Book.txt",
        "Database/Member.txt",
        "Database/BorrowRecords.txt"
    };

    std::vector<std::string> missingFiles;

    for (const auto& path : requiredFiles) {
        if (!std::filesystem::exists(path)) {
            missingFiles.push_back(path);
        }
    }

    if (!missingFiles.empty()) {
        std::cerr << "[Fatal ERROR] The following required files are missing:" << std::endl;
        for (const auto& file : missingFiles) {
            std::cerr << "  - " << file << std::endl;
        }
        std::cerr << "Working directory: " << std::filesystem::current_path() << std::endl;
        std::cerr << "Program terminated due to missing files." << std::endl;
        std::exit(EXIT_FAILURE);
    }
}

void LibraryManager::LoadData() {
    std::ifstream InFileBook ("DataBase/Book.txt");
    std::ifstream InFileMember ("DataBase/Member.txt");
    std::ifstream InFileBorrowRecords ("DataBase/BorrowRecords.txt");

    std::vector<std::string> ErrorOpeningFiles;

    //load Books vector
    if(InFileBook){
        Book temp;
        while(InFileBook >> temp){
            Books.emplace_back(temp);
        }
    }else{
        ErrorOpeningFiles.emplace_back("DataBase/Book.txt");
    }

    //load Members vector
    if(InFileMember){
        Member temp;
        while(InFileMember >> temp){
            Members.emplace_back(temp);
        }
    }else{
        ErrorOpeningFiles.emplace_back("DataBase/Member.txt");
    }

    //load BorrowRecord
    if(InFileBorrowRecords){
        std::string BookID;
        std::string MemberID;

        while(InFileBorrowRecords >> BookID >> MemberID){
            borrowRecords[BookID] = MemberID;
        }
    }else{
        ErrorOpeningFiles.emplace_back("DataBase/BorrowRecords.txt");
    }


    if (!ErrorOpeningFiles.empty()) {
        std::cerr << "[Fatal ERROR] The following required files are not Opening:" << std::endl;
        for (const auto& file : ErrorOpeningFiles) {
            std::cerr << "  - " << file << std::endl;
        }
        std::cerr << "Working directory: " << std::filesystem::current_path() << std::endl;
        std::cerr << "Program terminated due to error opening files." << std::endl;
        std::exit(EXIT_FAILURE);
    }
}

void LibraryManager::SaveData() {
    std::ofstream OutFileBook ("DataBase/Book.txt");
    std::ofstream OutFileMember ("DataBase/Member.txt");
    std::ofstream OutFileBorrowRecords ("DataBase/BorrowRecords.txt");

    std::vector<std::string> ErrorOpeningFiles;

    //save BorrowRecords
    if(OutFileBorrowRecords){
        for(const auto& [key,value] : borrowRecords){
            OutFileBorrowRecords << key << " " << value << std::endl;
        }
    }else{
        ErrorOpeningFiles.emplace_back("DataBase/BorrowRecords.txt");
    }

    //save Members
    if(OutFileBook){
        for(const Member& src : Members){
            OutFileBook << src << std::endl;
        }
    }else{
        ErrorOpeningFiles.emplace_back("DataBase/Member.txt");
    }

    //save Books
    if(OutFileBook){
        for(const Book& src : Books){
            OutFileBook << src << std::endl;
        }
    }else{
        ErrorOpeningFiles.emplace_back("DataBase/Book.txt");
    }

    if (!ErrorOpeningFiles.empty()) {
        std::cerr << "[Fatal ERROR] The following required files are not Opening:" << std::endl;
        for (const auto& file : ErrorOpeningFiles) {
            std::cerr << "  - " << file << std::endl;
        }
        std::cerr << "Working directory: " << std::filesystem::current_path() << std::endl;
        std::cerr << "Program terminated due to error opening file." << std::endl;
        std::exit(EXIT_FAILURE);
    }
}

void LibraryManager::addBook() {
    cleanscreen();
    std::string title = getValidString("Enter Title : ");
    std::string author = getValidName("Enter Author name : ");

    std::string IdPrefix{extractInitial(title),extractInitial(author)};
    std::string IdSuffix = getValidID("Enter ID : ");
    std::string bookId = IdPrefix + IdSuffix;
    
    auto it = std::find_if(Books.begin(),Books.end(), [&](const Book& b){return b.getID() == bookId;});
    if(it != Books.end()){
        std::cout << "BookID : " << bookId << " already exits." << std::endl;
        return;
    }

    it = std::find_if(Books.begin(),Books.end(), [&](const Book& b){return getUppercase(b.getTitle()) == getUppercase(title);});
    if(it != Books.end()){
        std::cout << "Book : \"" << title << "\" Already exits." << std::endl;
        return;
    }

    Books.emplace_back(title,author,bookId);
    std::cout << "book \""  << title << "\" with ID : " << bookId << " successfully." << std::endl;
}

void LibraryManager::viewBooks(){
    cleanscreen();
    std::cout << "Here are the available ways to view books:" << std::endl;
    std::cout << "Select an option to view books:" << std::endl;
    std::cout << "1. View by ID" << std::endl;
    std::cout << "2. View by Author" << std::endl;
    std::cout << "3. View by Title" << std::endl;
    std::cout << "4. view all books(one line)" << std::endl;
    std::cout << "5. Exit" << std::endl;
    int choice = getValidInput("Please select an option (1-5): ", 1, 5);

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
        case 5:
            std::cout << "Exiting the book view menu." << std::endl;
    }
}

void LibraryManager::viewBooksById(bool calledbyViewallBooks) {
    if(!calledbyViewallBooks){
        cleanscreen();
        std::cout << "A Book ID is formed by taking the first letters of the Book Title and Author's name, followed by a unique four-digit number (e.g., AB1234)." << std::endl;
    }
    std::string ID = getIdFromUser("Enter Book ID : ");
    
    auto it = std::find_if(Books.begin(),Books.end(), [&](const Book& src){return src.getID() == ID;});

    if(it != Books.end()){
        std::cout << std::string(40,'-') << std::endl;
        it->display();
        std::cout << std::string(40,'-') << std::endl;
        std::cout << "would you like to view more Books[y,n] ? : ";
    }else{
        std::cout << "There is no Book with ID : " << ID << std::endl;
        std::cout << "would you like to try again with diffrent Book ID[y,n] ? : ";
    }

    char choice = getValidYnN();
    if(choice == 'Y'){
        viewBooksById();
    } else {
        std::cout << "Returning to main menu." << std::endl;
    }
}

void LibraryManager::viewBooksByAuthor() {
    cleanscreen();
    std::string author = getValidName("Enter Author name : ");
    bool found = false;

    for(auto it = Books.begin(); it != Books.end(); ++it){
        if(getUppercase(it->getAuthor()) == getUppercase(author)){
            if(!found){
                std::cout << std::string(15,'=') << "Books by \"" << author << "\"." << std::string(15,'=') << std::endl;
                it->display();
                std::cout << std::string(40,'-') << std::endl;
                found = true;
            }else{
                it->display();
                std::cout << std::string(40,'-') << std::endl;
            }
        }
    }

    if(!found){
        std::cout << "No books found by author \"" << author << "\"." << std::endl;
        std::cout << "would you like to try again with diffrent Book Title[y,n] ? : ";

        char choice = getValidYnN();
        if(choice == 'Y'){
            viewBooksById();
        } else {
            std::cout << "Returning to main menu." << std::endl;
        }
    }
    

    
}

void LibraryManager::viewBooksByTitle() {
    cleanscreen();
    std::string title = getValidString("Enter Book Title : ");
    
    auto it = std::find_if(Books.begin(),Books.end(), [&](const Book& src){return getUppercase(src.getTitle()) == getUppercase(title);});

    if(it != Books.end()){
        std::cout << std::string(40,'-') << std::endl;
        it->display();
        std::cout << std::string(40,'-') << std::endl;
    }else{
        std::cout << "There is no Book with Title : " << title << std::endl;
        std::cout << "would you like to try again with diffrent Book Title[y,n] ? : ";
        char choice = getValidYnN();
        if(choice == 'Y'){
            viewBooksById();
        } else {
            std::cout << "Returning to main menu." << std::endl;
        }
    }
}

void LibraryManager::viewallBooks() {
    cleanscreen();
    std::cout << "Here are all the books:" << std::endl;
    for(const Book& src : Books){
        src.displayOneline();
    }

    std::cout << "would you like to view specific book details by ID[y,n] ? : ";
    char choice = getValidYnN();

    if(choice == 'Y'){
        viewBooksById(true);
    } else {
        std::cout << "Returning to main menu." << std::endl;
    }
}