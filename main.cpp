#include <iostream>
#include "LibraryCatalog.cpp"

using namespace std;

int main() {
    LibraryCatalog librarySystem;

    while (true)
    {
        cout<<endl;
        cout << "Welcome to the library system ..." << endl;
        cout << "1- add an author" << endl;
        cout << "2- add a book" << endl;
        cout << "3- update an author's name" << endl;
        cout << "4- update a book's title" << endl;
        cout << "5- delete a author by ID" << endl;
        cout << "6- delete an book by ISBN" << endl;
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
            if(librarySystem.checkAuthorForUpdate(authorId)){
                cout<<"this Author ID already exist"<<endl;
                continue;
            }
            cout << "Enter the author's name: ";
            getline(cin, authorName);
            cout << "Enter the author's address: ";
            getline(cin, address);
            librarySystem.addAuthor(authorId, authorName, address);


        }else if (choice == 2){
            string isbn, title, authorId;
            cout << "Enter the book's ISBN: ";
            getline(cin, isbn);
            if(librarySystem.checkBookForUpdate(isbn )){
                cout<<"this Book ISBN already exist"<<endl;
                continue;
            }
            cout << "Enter the book's title: ";
            getline(cin, title);
            cout << "Enter the author's ID: ";
            getline(cin, authorId);
            librarySystem.addBook(isbn, title, authorId);


        }else if (choice == 3){
            string authorId, newName;
            cout << "Enter the author's ID: ";
            getline(cin, authorId);
            if(!librarySystem.checkAuthorForUpdate(authorId)){
                cout<<"this Author ID is not exist!!"<<endl;
                continue;
            }
            cout << "Enter the author's new name: ";
            getline(cin, newName);
            librarySystem.updateAuthorName(authorId, newName);


        }else if (choice == 4){
            string isbn, newTitle;
            cout << "Enter the book's ISBN: ";
            getline(cin, isbn);
            if(!librarySystem.checkBookForUpdate(isbn)){
                cout<<"this Book ISBN is not exist!!"<<endl;
                continue;
            }
            cout << "Enter the book's new title: ";
            getline(cin, newTitle);
            librarySystem.updateBook(isbn, newTitle);


        }else if (choice == 5){
            string authorId;
            cout << "Enter the author's ID: ";
            getline(cin, authorId);
            if(!librarySystem.checkAuthorForUpdate(authorId)){
                cout<<"this Author ID is not exist!!"<<endl;
                continue;
            }
            librarySystem.deleteAuthorByID(authorId);


        }else if (choice == 6){
            string isbn;
            cout << "Enter the book's ISBN: ";
            getline(cin, isbn);
            if(!librarySystem.checkBookForUpdate(isbn)){
                cout<<"this Book ISBN is not exist!!"<<endl;
                continue;
            }
            librarySystem.deleteBookByISBN(isbn);


        }else if (choice == 7){
            string authorId;
            cout << "Enter the author's ID: ";
            getline(cin, authorId);
            if(!librarySystem.checkAuthorForUpdate(authorId)){
                cout<<"this Author ID is not exist!!"<<endl;
                continue;
            }
            librarySystem.PrintAuthor(authorId);


        }else if (choice == 8){
            string isbn;
            cout << "Enter the book's ISBN: ";
            getline(cin, isbn);
            if(!librarySystem.checkBookForUpdate(isbn)){
                cout<<"this Book ISBN is not exist!!"<<endl;
                continue;
            }
            librarySystem.PrintBook(isbn);


        }else if (choice == 9){
            librarySystem.CallQuery();


        }
        else if (choice == 10){
            break;
        }
        else{
            cout << "Invalid choice." << endl;
        }
    }
    return 0;
}

