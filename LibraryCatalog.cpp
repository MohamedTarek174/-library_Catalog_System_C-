#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <fstream>
#include <queue>

#include "Classes.cpp"


using namespace std;
/*
template <typename T>//Function to return vector (Template) to assign it into the vectors
void fileToVector(fstream& inputFile,vector<T> resultVector) {
    if (inputFile.is_open()) {
        string line;
        T value;
        while (getline(inputFile, value,'|')) {
            resultVector.push_back(value);
        }
        inputFile.close();
    }
}
*/
class LibraryCatalog {
private:
    fstream fileAuthors,fileBooks,PrimIndexAuthor,ScndIndexAuthor,PrimIndexBook,ScndIndexBook;

    vector<Author*> Authors;
    vector<Book*> Books;

    vector<AuthorPIndex*> AuthorsPrimaryIndex;
    vector<BookPIndex*> BooksPrimaryIndex;

    vector<AuthorSIndex*> AutherSecondaryIndex;
    vector<BookSIndex*> BooksSecondaryIndex;
    queue<int> offset;


public:

	LibraryCatalog(){
        offset.push(0);
        //fileAuthors.open("Authors.txt", ios::out|ios::app|ios::in);
        fileBooks.open("Books.txt", ios::out|ios::app|ios::in);

        //PrimIndexAuthor.open("PrimaryAu.txt", ios::out|ios::app|ios::in);
        //ScndIndexAuthor.open("SecondaryAu.txt", ios::out|ios::app|ios::in);

        PrimIndexBook.open("PrimaryBo.txt", ios::out|ios::app|ios::in);
        ScndIndexBook.open("SecondaryBo.txt", ios::out|ios::app|ios::in);

	}
	~LibraryCatalog(){
        fileAuthors.close();
        fileBooks.close();

        PrimIndexAuthor.close();
        ScndIndexAuthor.close();

        PrimIndexBook.close();
        ScndIndexBook.close();
	}
//****************************************************************************************************
void SortFile(string filePath){
    fstream File(filePath);
    vector<string> lines;
    if (File.is_open()) {
        string line;
        while (getline(File, line)) {
            lines.push_back(line);
        }
        File.close();
    }
    sort(lines.begin(), lines.end());//Sort the vector
    File.open(filePath,std::fstream::out | std::fstream::trunc );//Empty the original one
    for (const auto& line : lines) {
            File << line << endl;
        }
    File.close();

}
//****************************************************************************************************
int calculateQueueSum(queue<int>& myQueue) {
    queue<int> tempQueue = myQueue;
    int sum = 0;

    while (!tempQueue.empty()) {
        sum += tempQueue.front();
        tempQueue.pop();
    }
    return sum;
}

//****************************************************************************************************
    void addAuthor(string authorId,string authorName,string address) {//Done

        fileAuthors.open("Authors.txt", ios::out|ios::app|ios::in);
        PrimIndexAuthor.open("PrimaryAu.txt", ios::out|ios::app|ios::in);
        ScndIndexAuthor.open("SecondaryAu.txt", ios::out|ios::app|ios::in);

        Author* newAuthor = new Author(authorId, authorName, address);//Create one

        string newAuthorString = newAuthor->toString();
        fileAuthors << newAuthorString;//Add the Author to the file

        Authors.push_back(newAuthor);//Add it to the vector

        int Size = newAuthorString.length();//Calc the Offset
        int Offset = calculateQueueSum(offset);
        offset.push(Size);

        PrimIndexAuthor << newAuthor->authorId << "|" <<Offset << endl;//Add the Primary Index to the file
        AuthorPIndex* newAuthorPIndex = new AuthorPIndex(Offset,newAuthor->authorId);
        AuthorsPrimaryIndex.push_back(newAuthorPIndex);//Add it to the primary list
        SortFile("PrimaryAu.txt");


        ScndIndexAuthor << newAuthor->authorName << "|" <<newAuthor->authorId << endl;//Add the Secondry Index to the file
        AuthorSIndex* newAuthorSIndex = new AuthorSIndex(newAuthor->authorName,newAuthor->authorId);
        AutherSecondaryIndex.push_back(newAuthorSIndex);//Add it to the Secondary list
        SortFile("SecondaryAu.txt");

        fileAuthors.close();
        PrimIndexAuthor.close();
        ScndIndexAuthor.close();
    }
    /*
//****************************************************************************************************
    void addBook(string& isbn, string& title, string& authorId) {
        Book* newBook = new Book(isbn, title, authorId);
        booksPrimaryIndex.push_back(newBook);
        booksSecondaryIndex.push_back(newBook);

        sort(booksPrimaryIndex.begin(), booksPrimaryIndex.end(),comparebooksByisbn);

        sort(booksSecondaryIndex.begin(), booksSecondaryIndex.end(),compareBooksByAuthorsId);
    }
//****************************************************************************************************
    void deleteAuthor(string& authorId) {
        auto it = find_if(authorsPrimaryIndex.begin(), authorsPrimaryIndex.end(),
                          [authorId](Author* author) { return author->authorId == authorId; });

        if (it != authorsPrimaryIndex.end()) {
            // Mark as deleted (optional: free memory)
            (*it)->authorId = "*DELETED*";
            // Update indexes
            sort(authorsPrimaryIndex.begin(), authorsPrimaryIndex.end(),compareAuthorsById);
            sort(booksSecondaryIndex.begin(), booksSecondaryIndex.end(),comparebooksByisbn);
        } else {
            cout << "Author not found." << endl;
        }
    }
//****************************************************************************************************
    void deleteBook(string& isbn) {
        auto it = find_if(booksPrimaryIndex.begin(), booksPrimaryIndex.end(),
                          [isbn](Book* book) { return book->isbn == isbn; });

        if (it != booksPrimaryIndex.end()) {
            // Mark as deleted (optional: free memory)
            (*it)->isbn = "*DELETED*";
            // Update indexes
            sort(booksPrimaryIndex.begin(), booksPrimaryIndex.end(),
                 [](Book* a, Book* b) { return a->isbn < b->isbn; });
            sort(booksSecondaryIndex.begin(), booksSecondaryIndex.end(),comparebooksByisbn);
        } else {
            cout << "Book not found." << endl;
        }
    }
//****************************************************************************************************
    void searchByAuthorId(string& authorId) {
        auto it = binary_search(authorsPrimaryIndex.begin(), authorsPrimaryIndex.end(),
                                [authorId](Author* author) { return author->authorId == authorId; });

        if (it) {
            // Display author information
            cout << "Author found: " << (*it)->authorName << ", " << (*it)->address << endl;
        } else {
            cout << "Author not found." << endl;
        }
    }
//****************************************************************************************************
    void searchByIsbn(string& isbn) {
        auto it = binary_search(booksPrimaryIndex.begin(), booksPrimaryIndex.end(),
                                [isbn](Book* book) { return book->isbn == isbn; });

        if (it) {
            // Display book information
            cout << "Book found: " << (*it)->title << ", Author: " << (*it)->authorId << endl;
        } else {
            cout << "Book not found." << endl;
        }
    }
//****************************************************************************************************
    void updateBook(string& isbn, string& newTitle) {
        auto it = find_if(booksPrimaryIndex.begin(), booksPrimaryIndex.end(),
                          [isbn](Book* book) { return book->isbn == isbn; });

        if (it != booksPrimaryIndex.end()) {
            // Update book title
            (*it)->title = newTitle;
            // Update indexes
            sort(booksPrimaryIndex.begin(), booksPrimaryIndex.end(),comparebooksByisbn);
            sort(booksSecondaryIndex.begin(), booksSecondaryIndex.end(),
                 [](Book* a, Book* b) { return a->authorId < b->authorId; });
        } else {
            cout << "Book not found." << endl;
        }
    }
//****************************************************************************************************
    void updateAuthorName(string& authorId, string& newAuthorName) {
        auto it = find_if(authorsPrimaryIndex.begin(), authorsPrimaryIndex.end(),
                          [authorId](Author* author) { return author->authorId == authorId; });

        if (it != authorsPrimaryIndex.end()) {
            // Update author's name
            (*it)->authorName = newAuthorName;
            // Update indexes
            sort(authorsPrimaryIndex.begin(), authorsPrimaryIndex.end(),compareAuthorsById);
            sort(booksSecondaryIndex.begin(), booksSecondaryIndex.end(),comparebooksByisbn);
        } else {
            cout << "Author not found." << endl;
        }
    }
    */
};
