#include <iostream>
#include "LibraryCatalog.cpp"

using namespace std;

int main() {
    // Example usage:
    LibraryCatalog librarySystem;

    librarySystem.addAuthor("A001", "John Doe", "123 Main St");
    librarySystem.addAuthor("C002", "Jane Smith", "456 Oak St");
    librarySystem.addAuthor("B003", "ronald Sam", "153 Osten St");


    librarySystem.addBook("B001", "Introduction to C++", "A001");
    librarySystem.addBook("A002", "Data Structures and Algorithms", "C002");
    librarySystem.addBook("C002", "Data Structures and Algorithms", "B003");


/*
    librarySystem.searchByIsbn("B002");

    librarySystem.updateBook("B001", "C++ Programming");
    librarySystem.updateAuthorName("A002", "Jane Johnson");


    librarySystem.deleteAuthor("A003"); // This will print "Author not found."
*/
    return 0;
}
