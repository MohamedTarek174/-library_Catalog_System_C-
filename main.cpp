#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Author {
public:
    string authorId;
    string authorName;
    string address;
    Author* nextAuthor;

    Author(const string& id, const string& name, const string& addr)
        : authorId(id), authorName(name), address(addr), nextAuthor(nullptr) {}
};

class Book {
public:
    string isbn;
    string title;
    string authorId;
    Book* nextBook;

    Book(const string& isbn, const string& title, const string& authorId)
        : isbn(isbn), title(title), authorId(authorId), nextBook(nullptr) {}
};

class LibraryCatalog {
private:
    vector<Author*> authorsPrimaryIndex;
    vector<Book*> booksPrimaryIndex;
    vector<Book*> booksSecondaryIndex;

public:
    void addAuthor(const string& authorId, const string& authorName, const string& address) {
        Author* newAuthor = new Author(authorId, authorName, address);
        authorsPrimaryIndex.push_back(newAuthor);
        sort(authorsPrimaryIndex.begin(), authorsPrimaryIndex.end(),
             [](const Author* a, const Author* b) { return a->authorId < b->authorId; });
    }

    void addBook(const string& isbn, const string& title, const string& authorId) {
        Book* newBook = new Book(isbn, title, authorId);
        booksPrimaryIndex.push_back(newBook);
        booksSecondaryIndex.push_back(newBook);
        sort(booksPrimaryIndex.begin(), booksPrimaryIndex.end(),
             [](const Book* a, const Book* b) { return a->isbn < b->isbn; });
        sort(booksSecondaryIndex.begin(), booksSecondaryIndex.end(),
             [](const Book* a, const Book* b) { return a->authorId < b->authorId; });
    }

    void deleteAuthor(const string& authorId) {
        auto it = find_if(authorsPrimaryIndex.begin(), authorsPrimaryIndex.end(),
                          [authorId](const Author* author) { return author->authorId == authorId; });

        if (it != authorsPrimaryIndex.end()) {
            // Mark as deleted (optional: free memory)
            (*it)->authorId = "*DELETED*";
            // Update indexes
            sort(authorsPrimaryIndex.begin(), authorsPrimaryIndex.end(),
                 [](const Author* a, const Author* b) { return a->authorId < b->authorId; });
            sort(booksSecondaryIndex.begin(), booksSecondaryIndex.end(),
                 [](const Book* a, const Book* b) { return a->authorId < b->authorId; });
        } else {
            cout << "Author not found." << endl;
        }
    }

    void deleteBook(const string& isbn) {
        auto it = find_if(booksPrimaryIndex.begin(), booksPrimaryIndex.end(),
                          [isbn](const Book* book) { return book->isbn == isbn; });

        if (it != booksPrimaryIndex.end()) {
            // Mark as deleted (optional: free memory)
            (*it)->isbn = "*DELETED*";
            // Update indexes
            sort(booksPrimaryIndex.begin(), booksPrimaryIndex.end(),
                 [](const Book* a, const Book* b) { return a->isbn < b->isbn; });
            sort(booksSecondaryIndex.begin(), booksSecondaryIndex.end(),
                 [](const Book* a, const Book* b) { return a->authorId < b->authorId; });
        } else {
            cout << "Book not found." << endl;
        }
    }

    void searchByAuthorId(const string& authorId) {
        auto it = binary_search(authorsPrimaryIndex.begin(), authorsPrimaryIndex.end(),
                                [authorId](const Author* author) { return author->authorId == authorId; });

        if (it) {
            // Display author information
            cout << "Author found: " << (it)->authorName << ", " << (*it)->address << endl;
        } else {
            cout << "Author not found." << endl;
        }
    }

    void searchByIsbn(const string& isbn) {
        auto it = binary_search(booksPrimaryIndex.begin(), booksPrimaryIndex.end(),
                                [isbn](const Book* book) { return book->isbn == isbn; });

        if (it) {
            // Display book information
            cout << "Book found: " << (*it)->title << ", Author: " << (*it)->authorId << endl;
        } else {
            cout << "Book not found." << endl;
        }
    }


    void updateBook(const string& isbn, const string& newTitle) {
        auto it = find_if(booksPrimaryIndex.begin(), booksPrimaryIndex.end(),
                          [isbn](const Book* book) { return book->isbn == isbn; });

        if (it != booksPrimaryIndex.end()) {
            // Update book title
            (*it)->title = newTitle;
            // Update indexes
            sort(booksPrimaryIndex.begin(), booksPrimaryIndex.end(),
                 [](const Book* a, const Book* b) { return a->isbn < b->isbn; });
            sort(booksSecondaryIndex.begin(), booksSecondaryIndex.end(),
                 [](const Book* a, const Book* b) { return a->authorId < b->authorId; });
        } else {
            cout << "Book not found." << endl;
        }
    }
    void updateAuthorName(const string& authorId, const string& newAuthorName) {
        auto it = find_if(authorsPrimaryIndex.begin(), authorsPrimaryIndex.end(),
                          [authorId](const Author* author) { return author->authorId == authorId; });

        if (it != authorsPrimaryIndex.end()) {
            // Update author's name
            (*it)->authorName = newAuthorName;
            // Update indexes
            sort(authorsPrimaryIndex.begin(), authorsPrimaryIndex.end(),
                 [](const Author* a, const Author* b) { return a->authorId < b->authorId; });
            sort(booksSecondaryIndex.begin(), booksSecondaryIndex.end(),
                 [](const Book* a, const Book* b) { return a->authorId < b->authorId; });
        } else {
            cout << "Author not found." << endl;
        }
    }
};

int main() {
    // Example usage:
    LibraryCatalog librarySystem;

    librarySystem.addAuthor("A001", "John Doe", "123 Main St");
    librarySystem.addAuthor("A002", "Jane Smith", "456 Oak St");

    librarySystem.addBook("B001", "Introduction to C++", "A001");
    librarySystem.addBook("B002", "Data Structures and Algorithms", "A002");

    librarySystem.searchByAuthorId("A001");
    librarySystem.searchByIsbn("B002");

    librarySystem.updateBook("B001", "C++ Programming");
    librarySystem.updateAuthorName("A002", "Jane Johnson");


    librarySystem.deleteAuthor("A003"); // This will print "Author not found."

    return 0;
}
