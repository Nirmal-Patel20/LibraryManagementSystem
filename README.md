# 📚 Library Management System (c++23)

A console-based C++23 Library Management System for managing books, members, and borrowing records.
Data is stored in text files and loaded automatically on startup.
Features cross-manager access using pointers & references to avoid code duplication and circular dependencies.

---

## 📌 Purpose

- This project is a cleaner, more maintainable successor to my earlier **tudent Management System**(Link : https://github.com/Nirmal-Patel20/StudentManagementSystem).
- The StudentManagementSystem was functional but messy, with limited modularity and poor separation of concerns.
- This new version focuses on:

- Clear modular structure with multiple managers
  - Proper use of OOP principles
  - Better error handling and file management
  - Expandable design for future features

## ✅ Features

- **Book Management:** Add, search, view, and delete books from the library database.

- **Member Management:** Add, search, view, and delete members.

- **Borrow & Return Tracking:** Record which member has borrowed which book, and manage returns efficiently.

- **Persistent Storage:** All data is stored in the DataBase/ folder as text files to ensure it is preserved between program runs.

- **Console-Based UI:** User-friendly, menu-driven interface for all operations.

- **Error Handling:** Most input and operation errors are handled automatically by the InputHelper utility.

- **Cross-Manager Utility Access:** Managers share utilities via references/pointers from LibraryManager.

- **File Integrity Check:** On startup, the program verifies the existence of required data files. If any are missing, the program terminates to prevent data corruption.

---

## 📁 Project Structure
```LibraryManagementSystem/
├── DataBase/ 
│   ├── Book.txt 
│   ├── Member.txt 
│   └── BorrowRecords.txt 
├── include/ 
│   ├── Book.h 
│   ├── BookManager.h 
│   ├── BorrowRecordManager.h 
│   ├── InputHelper.h 
│   ├── LibraryManager.h 
│   ├── Member.h 
│   └── MemberManager.h 
├── src/ 
│   ├── Book.cpp 
│   ├── BookManager.cpp
│   ├── BorrowRecordManager.cpp 
│   ├── InputHelper.cpp 
│   ├── LibraryManager.cpp 
│   ├── main.cpp 
│   ├── Member.cpp 
│   └── MemberManager.cpp 
├── CMakeLists.txt 
├── README.md 
```

---

## ⚒️ How to Build & Run

### Using g++ (Linux/macOS/WSL):

```bash
g++ src/*.cpp -o LibraryManagementSystem
./StudentApp
```
> [!caution]
> Make sure your terminal path is inside the project root(..\LibraryManagementSystem).

### using g++(window)

```bash
g++ src/*.cpp -o LibraryManagementSystem
StudentApp.exe
```
> [!caution]
> Make sure your terminal path is inside the project root(..\LibraryManagementSystem).

### using Cmake(Linux/macOS/Window)(Recommended)

```bash
git clone https://github.com/Nirmal-Patel20/LibraryManagementSystem.git
cd LibraryManagementSystem
cmake --preset ninja-release
cmake --build build/ninja-release
.\build\ninja-release\LibraryManagementSystem.exe 
```
> [!Note]
> Run from the project root. Executable will be inside build/ninja-release/. and named `LibraryManagementSystem.exe`.

---

## 🏢 How the Program Works

1. ### 📝 Overview
- Manages **books, members, and borrow records** in memory using **`std::vector`** and **`std::unordered_map`**.  
- Data is **auto-loaded on startup** and **auto-saved on exit**.

2. ### 🗂 Architecture
- 📚 **BookManager** – Handles all book-related operations.  
- 👥 **MemberManager** – Handles member records.  
- 📄 **BorrowRecordManager** – Tracks borrow/return with fast lookups.  
- 🏛 **LibraryManager** – Main control hub connecting all managers.  
- 🛡 **InputHelper** – Centralized input validation & error handling.

3. ### 💾 Data Handling
- Text files in **`DataBase/`** are **read into memory** using overloaded **`>>`** operators.  
- Written back on exit using overloaded **`<<`** operators.

4. ### 🔄 Cross-Manager Access
- BorrowRecordManager calls BookManager & MemberManager functions directly with copies of them.

- MemberManager also needs BorrowRecordManager utilites that why after construction `setBorrowRecordManager` function is called to pass pointer of BorrowRecordManager to MemberManager.

- Library passes references or pointer to BorrowRecordManager and MemberManager.

- This avoids circular dependencies while allowing managers to share functionality.

- Uses **forward declarations** + **pointer passing** to avoid circular dependency.

- 

5. ### ⚠️ Error Handling

 - If the DataStore/ folder or required files are missing, the program terminates with an error message.

 - Invalid inputs are caught by InputHelper and prompt the user to retry.

6. ### 🖥 Program Flow

 - **Load Data** from `DataBase/`.  
 -  **Main Menu**  
    - 1️⃣ Book Menu 
    - 2️⃣ Member Menu 
    - 3️⃣ Borrow Menu
    - 0️⃣ Exit  
 - **In-Memory Changes** happen during runtime.  
 - **Save & Exit** writes all changes to files.

> [!WARNING] If the folder DataBase does not exist in the current directory, the program will terminate immediately to prevent inconsistent or incomplete data states.

---

## 🧠 Concepts Practiced
- **Object-Oriented Programming (OOP)** — classes, encapsulation, and modular design
- Forward declarations & circular dependency prevention
- Pointer & reference usage for cross-manager access
- auto-loading and saving data on object lifecycle
- File I/O — reading/writing structured data with std::fstream
- Operator overloading for intuitive object output
- Error handling with a dedicated input helper
- Use of STL containers (std::vector, std::unordered_map) in a real-world context
- Console-based menu navigation with input validation
- Multi-manager coordination through a central controller

---

## 🔐 GitHub Setup
- Git tracked .txt files store student data (data/students.txt)
- `.gitignore` used to exclude build files
- Modular layout for clean version control

## 📢 Status
>Project completed as a learning exercise. No further development planned.

## 🧑‍💻 Author
- Nirmal Patel — Aspiring C++ developer working on real-world practice projects.