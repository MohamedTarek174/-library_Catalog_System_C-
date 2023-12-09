#include <iostream>
#include "LibraryCatalog.cpp"

using namespace std;

int main() {
    // Example usage:

    LibraryCatalog librarySystem;

    while (true)
    {
        cout << "Welcome to the library system ..." << endl;
        cout << "1- add an author" << endl;
        cout << "2- add a book" << endl;
        cout << "3- update an author's name" << endl;
        cout << "4- update a book's title" << endl;
        cout << "5- delete a book by ISBN" << endl;
        cout << "6- delete an author by ID" << endl;
        cout << "7- search for an author by ID" << endl;
        cout << "8- search for a book by ISBN" << endl;
        cout << "9- Write Query" << endl;
        cout << "10- exit" << endl;
        cout << "Enter your choice: ";
        int choice;
        cin >> choice;
        cin.ignore();

        if (choice == 1){
            string authorId, authorName, address;
            cout << "Enter the author's ID: ";
            getline(cin, authorId);
            cout << "Enter the author's name: ";
            getline(cin, authorName);
            cout << "Enter the author's address: ";
            getline(cin, address);
            librarySystem.addAuthor(authorId, authorName, address);


        }else if (choice == 2){
            string isbn, title, authorId;
            cout << "Enter the book's ISBN: ";
            getline(cin, isbn);
            cout << "Enter the book's title: ";
            getline(cin, title);
            cout << "Enter the author's ID: ";
            getline(cin, authorId);
            librarySystem.addBook(isbn, title, authorId);


        }else if (choice == 3){
            string authorId, newName;
            cout << "Enter the author's ID: ";
            getline(cin, authorId);
            cout << "Enter the author's new name: ";
            getline(cin, newName);
            librarySystem.updateAuthorName(authorId, newName);


        }else if (choice == 4){
            string isbn, newTitle;
            cout << "Enter the book's ISBN: ";
            getline(cin, isbn);
            cout << "Enter the book's new title: ";
            getline(cin, newTitle);
            librarySystem.updateBook(isbn, newTitle);


        }else if (choice == 5){
            string isbn;
            cout << "Enter the book's ISBN: ";
            getline(cin, isbn);
            librarySystem.deleteBookByISBN(isbn);


        }else if (choice == 6){
            string authorId;
            cout << "Enter the author's ID: ";
            getline(cin, authorId);
            librarySystem.deleteAuthorByID(authorId);


        }/*else if (choice == 7){
            string authorId;
            cout << "Enter the author's ID: ";
            getline(cin, authorId);
            librarySystem.searchAuthorByID(authorId);


        }else if (choice == 8){
            string isbn;
            cout << "Enter the book's ISBN: ";
            getline(cin, isbn);
            librarySystem.searchBookByISBN(isbn);


        }*/else if (choice == 9){
            librarySystem.writeQuery();


        }
        else if (choice == 10){
            break;
        }
        else{
            cout << "Invalid choice." << endl;
        }
    }


     //librarySystem.addAuthor("A001", "John Doe", "123 Main St");
     //librarySystem.addAuthor("C002", "Jane Smith", "456 Oak St");//27
     //librarySystem.addAuthor("B003", "ronald Sam", "153 Osten St");
     //librarySystem.deleteAuthorByID("C002");
     //librarySystem.addAuthor("D004", "Je Smith", "456 Oak St");

    // //librarySystem.updateAuthorName("A001", "Jane Johnson");

    // librarySystem.addBook("B001", "Introduction to C++", "A001");
    // librarySystem.addBook("A002", "Data Structures and Algorithms", "C002");
    // librarySystem.addBook("C002", "Data Structures and Algorithms", "B003");

    // //librarySystem.updateBook("B001", "C++ Programming");

    // //librarySystem.deleteAuthorByID("B003");
    // //librarySystem.deleteBookByISBN("B001");




    // //librarySystem.deleteAuthor("A003"); // This will print "Author not found."

    return 0;
}

