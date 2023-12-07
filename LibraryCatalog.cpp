#include "Classes.cpp"
#include "Functions.cpp"

using namespace std;

class LibraryCatalog
{
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
    LibraryCatalog()
    {
        fstream FileAu("Authors.txt", std::fstream::out | std::fstream::trunc);
        fstream FilePIAu("PrimaryAu.txt", std::fstream::out | std::fstream::trunc);
        fstream FileSIAu("SecondaryAu.txt", std::fstream::out | std::fstream::trunc);
        fstream FileBo("Books.txt", std::fstream::out | std::fstream::trunc);
        fstream FilePIBo("PrimaryBo.txt", std::fstream::out | std::fstream::trunc);
        fstream FileSIBo("SecondaryBo.txt", std::fstream::out | std::fstream::trunc);
        offsetAuthors.push(0);
        offsetBooks.push(0);
    }
///****************************************************************************************************
    ~LibraryCatalog()//Just for check
    {
        fileAuthors.close();
        fileBooks.close();

        PrimIndexAuthor.close();
        ScndIndexAuthor.close();

        PrimIndexBook.close();
        ScndIndexBook.close();
    }
///****************************************************************************************************
    void addAuthor(string authorId,string authorName,string address)  //Done
    {
        //cout<<"efwrgewgr  "<<authorId<<" "<<authorName<<" "<<address<<endl;
        AddForDataFile("Authors.txt",Authors,authorId,authorName,address);
        AddForPIFile("PrimaryAu.txt",AuthorsPrimaryIndex,authorId,offsetAuthors);
        AddForSIFile("SecondaryAu.txt",AutherSecondaryIndex,authorName,authorId);

    }
///****************************************************************************************************
    void addBook(string isbn, string title, string authorId)
    {
        AddForDataFile("Books.txt",Books,isbn,title,authorId);
        AddForPIFile("PrimaryBo.txt",BooksPrimaryIndex,isbn,offsetBooks);
        AddForSIFile("SecondaryBo.txt",BooksSecondaryIndex,authorId,isbn);
    }

///****************************************************************************************************
/*
    void deleteAuthorByID(string authorId)
    {
        DeleteForAll(Authors,"Authors.txt",authorId);
        DeleteForAll(AuthorsPrimaryIndex,"PrimaryAu.txt",authorId);
        DeleteForAll(AutherSecondaryIndex,"SecondaryAu.txt",authorId);
    }

///****************************************************************************************************
    void deleteBookByISBN(string isbn)
    {
        DeleteForAll(Books,"Books.txt",isbn);
        DeleteForAll(BooksPrimaryIndex,"PrimaryBo.txt",isbn);
        DeleteForAll(BooksSecondaryIndex,"SecondaryBo.txt",isbn);
    }
*/


///****************************************************************************************************
    void updateAuthorName(string authorId, string newAuthorName)//Error occur after making UpdateForAll function
    {

        fstream FileData("Authors.txt", std::fstream::out | std::fstream::trunc);
        fstream FilePI("PrimaryAu.txt", std::fstream::out | std::fstream::trunc);
        fstream FileSI("SecondaryAu.txt", std::fstream::out | std::fstream::trunc);
        UpdateForAll(Authors, authorId, newAuthorName,offsetAuthors);

        for (Author elem : Authors){
            string ID = elem.getFmember();
            string Name = elem.getSmember();
            string Address = elem.getTtmember();
            addAuthor(ID,Name,Address);
            FileData.close();
        }

    }
///****************************************************************************************************
    void updateBook(string isbn, string newTitle)
    {
        fstream FileData("Books.txt", std::fstream::out | std::fstream::trunc);
        fstream FilePI("PrimaryBo.txt", std::fstream::out | std::fstream::trunc);
        fstream FileSI("SecondaryBo.txt", std::fstream::out | std::fstream::trunc);
        UpdateForAll(Books, isbn, newTitle, offsetBooks);

        for (Book elem : Books){
            string Isbn = elem.getFmember();
            string title = elem.getSmember();
            string AuId = elem.getTtmember();
            addBook(Isbn,title,AuId);
        }
    }


};
