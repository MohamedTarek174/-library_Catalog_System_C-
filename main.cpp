#include <iostream>
#include "LibraryCatalog.cpp"

using namespace std;

int main() {
    // Example usage:
    LibraryCatalog librarySystem;

    librarySystem.addAuthor("A001", "John Doe", "123 Main St");
    librarySystem.addAuthor("C002", "Jane Smith", "456 Oak St");
    librarySystem.addAuthor("B003", "ronald Sam", "153 Osten St");
    librarySystem.deleteAuthorByID("C002");
    librarySystem.addAuthor("1234", "Je Smith", "456 Oak St");

    //librarySystem.updateAuthorName("A001", "Jane Johnson");

    librarySystem.addBook("B001", "Introduction to C++", "A001");
    librarySystem.addBook("A002", "Data Structures and Algorithms", "C002");
    librarySystem.addBook("C002", "Data Structures and Algorithms", "B003");

    //librarySystem.updateBook("B001", "C++ Programming");

    //librarySystem.deleteAuthorByID("B003");
    //librarySystem.deleteBookByISBN("B001");




    //librarySystem.deleteAuthor("A003"); // This will print "Author not found."

    return 0;
}
