#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <fstream>
#include <queue>
#include <sstream>
#include <functional>
#include "Classes.cpp"


using namespace std;

class LibraryCatalog {
private:
    fstream fileAuthors,fileBooks,PrimIndexAuthor,ScndIndexAuthor,PrimIndexBook,ScndIndexBook;

    vector<Author> Authors;
    vector<Book> Books;

    vector<AuthorPIndex> AuthorsPrimaryIndex;
    vector<BookPIndex> BooksPrimaryIndex;

    vector<AuthorSIndex> AutherSecondaryIndex;
    vector<BookSIndex> BooksSecondaryIndex;
    queue<int> offsetAuthors;
    queue<int> offsetBooks;



public:

	LibraryCatalog(){
        offsetAuthors.push(0);
        offsetBooks.push(0);
        //fileAuthors.open("Authors.txt", ios::out|ios::app|ios::in);
        //fileBooks.open("Books.txt", ios::out|ios::app|ios::in);

        //PrimIndexAuthor.open("PrimaryAu.txt", ios::out|ios::app|ios::in);
        //ScndIndexAuthor.open("SecondaryAu.txt", ios::out|ios::app|ios::in);

        //PrimIndexBook.open("PrimaryBo.txt", ios::out|ios::app|ios::in);
        //ScndIndexBook.open("SecondaryBo.txt", ios::out|ios::app|ios::in);

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

        Author newAuthor(authorId, authorName, address);//Create one

        string newAuthorString = newAuthor.toString();
        fileAuthors << newAuthorString;//Add the Author to the file

        Authors.push_back(newAuthor);//Add it to the vector

        int Size = newAuthorString.length();//Calc the Offset
        int Offset = calculateQueueSum(offsetAuthors);
        offsetAuthors.push(Size);

        ///Primary Index
        PrimIndexAuthor << newAuthor.authorId << "|" <<Offset << endl;//Add the Primary Index to the file
        AuthorPIndex newAuthorPIndex (newAuthor.authorId,Offset);
        AuthorsPrimaryIndex.push_back(newAuthorPIndex);//Add it to the primary list
        SortFile("PrimaryAu.txt");

        ///Secondary Index
        ScndIndexAuthor << newAuthor.authorName << "|" <<newAuthor.authorId << endl;//Add the Secondry Index to the file
        AuthorSIndex newAuthorSIndex (newAuthor.authorName,newAuthor.authorId);
        AutherSecondaryIndex.push_back(newAuthorSIndex);//Add it to the Secondary list
        SortFile("SecondaryAu.txt");

        fileAuthors.close();
        PrimIndexAuthor.close();
        ScndIndexAuthor.close();
    }

//****************************************************************************************************
    void addBook(string isbn, string title, string authorId) {
        fileBooks.open("Books.txt", ios::out|ios::app|ios::in);
        PrimIndexBook.open("PrimaryBo.txt", ios::out|ios::app|ios::in);
        ScndIndexBook.open("SecondaryBo.txt", ios::out|ios::app|ios::in);

        Book newBook (isbn, title, authorId);
        string newBookString = newBook.toString();
        fileBooks << newBookString;//Add the Author to the file

        Books.push_back(newBook);//Add it to the vector

        int Size = newBookString.length();//Calc the Offset
        int Offset = calculateQueueSum(offsetBooks);
        offsetBooks.push(Size);

        ///Primary Index
        PrimIndexBook << newBook.isbn << "|" <<Offset << endl;//Add the Primary Index to the file
        BookPIndex newBookPIndex(newBook.isbn,Offset);
        BooksPrimaryIndex.push_back(newBookPIndex);//Add it to the primary list
        SortFile("PrimaryBo.txt");

        ///Secondary Index
        ScndIndexBook << newBook.isbn << "|" <<newBook.authorId << endl;//Add the Secondry Index to the file
        BookSIndex newBookSIndex(newBook.authorId,newBook.isbn);
        BooksSecondaryIndex.push_back(newBookSIndex);//Add it to the Secondary list
        SortFile("SecondaryBo.txt");

        fileBooks.close();
        PrimIndexBook.close();
        ScndIndexBook.close();

    }
//****************************************************************************************************
void deleteAuthorByID(string authorId) {//I got so many problems while trying with vectors
    fileAuthors.open("Authors.txt", ios::out|ios::app|ios::in);
    string line;
    getline(fileAuthors, line);
    int rrn = searchByAuthorId(authorId);
    if (!rrn){
        cout<<"Author is not exist"<<endl;
        return;
    }
    string SizeOfAuthorLine;
    for(int i = rrn+1;i < rrn+3;i++)
        SizeOfAuthorLine+=line[i];
    int Size = stoi(SizeOfAuthorLine);
    for(int i = rrn+3;i <= Size;i++){

    }


}
/*
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
*/
//**** ************************************************************************************************
    int searchByAuthorId(string authorId) {
        //I could make it with the vectors but its more professional
        PrimIndexAuthor.open("PrimaryAu.txt", ios::out|ios::app|ios::in);
        string line;
        while (getline(PrimIndexAuthor, line)) {
            istringstream iss(line);
            string currentID;
            int currentRRN;

            // Parsing ID and RRN from the line
            if (getline(iss, currentID, '|') && iss >> currentRRN) {
                // Check if the current line's ID matches the target ID
                if (currentID == authorId) {
                    PrimIndexAuthor.close();
                    return currentRRN; // Return RRN if ID is found
                }
            }
        }
        return 0;
    }

//****************************************************************************************************
    int searchByIsbn(string isbn) {
        PrimIndexBook.open("PrimaryBo.txt", ios::out|ios::app|ios::in);
        string line;
        while (getline(PrimIndexBook, line)) {
            istringstream iss(line);
            string currentisbn;
            int currentRRN;

            // Parsing ID and RRN from the line
            if (getline(iss, currentisbn, '|') && iss >> currentRRN) {
                // Check if the current line's ID matches the target ID
                if (currentisbn == isbn) {
                    PrimIndexBook.close();
                    return currentRRN; // Return RRN if ID is found
                }
            }
        }
        return 0;
    }
    /*
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
