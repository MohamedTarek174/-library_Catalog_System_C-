#include "Classes.cpp"
#include "Functions.cpp"
#include "Search.cpp"

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
        //fstream FileAu("Authors.txt", std::fstream::out | std::fstream::trunc);
        //fstream FilePIAu("PrimaryAu.txt", std::fstream::out | std::fstream::trunc);
        //fstream FileSIAu("SecondaryAu.txt", std::fstream::out | std::fstream::trunc);
        //fstream FileBo("Books.txt", std::fstream::out | std::fstream::trunc);
        //fstream FilePIBo("PrimaryBo.txt", std::fstream::out | std::fstream::trunc);
        //fstream FileSIBo("SecondaryBo.txt", std::fstream::out | std::fstream::trunc);
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
    void deleteAuthorByID(string authorId)
    {
        int RRN = searchByAuthorId(authorId);
        fstream FileData("Authors.txt", std::fstream::out | std::fstream::trunc);
        fstream FilePI("PrimaryAu.txt", std::fstream::out | std::fstream::trunc);
        fstream FileSI("SecondaryAu.txt", std::fstream::out | std::fstream::trunc);
        DeleteForAll("Authors.txt",Authors,authorId,offsetAuthors,RRN);

        for (Author elem : Authors){
            string ID = elem.getFmember();
            string Name = elem.getSmember();
            string Address = elem.getTmember();
            addAuthor(ID,Name,Address);
            FileData.close();
        }

    }

///****************************************************************************************************
    void deleteBookByISBN(string isbn)
    {
        int RRN = searchByIsbn(isbn);
        fstream FileData("Books.txt", std::fstream::out | std::fstream::trunc);
        fstream FilePI("PrimaryBo.txt", std::fstream::out | std::fstream::trunc);
        fstream FileSI("SecondaryBo.txt", std::fstream::out | std::fstream::trunc);
        DeleteForAll("Books.txt",Books,isbn,offsetBooks,RRN);

        for (Book elem : Books){
            string ID = elem.getFmember();
            string Name = elem.getSmember();
            string Address = elem.getTmember();
            addBook(ID,Name,Address);
            FileData.close();
        }
    }


///****************************************************************************************************
    void updateAuthorName(string authorId, string newAuthorName)
    {

        fstream FileData("Authors.txt", std::fstream::out | std::fstream::trunc);
        fstream FilePI("PrimaryAu.txt", std::fstream::out | std::fstream::trunc);
        fstream FileSI("SecondaryAu.txt", std::fstream::out | std::fstream::trunc);
        UpdateForAll(Authors, authorId, newAuthorName,offsetAuthors);

        for (Author elem : Authors){
            string ID = elem.getFmember();
            string Name = elem.getSmember();
            string Address = elem.getTmember();
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
            string AuId = elem.getTmember();
            addBook(Isbn,title,AuId);
        }
    }
///*********************************************************************************************************
    QueryInfo parseQuery(const string& query)
{
    QueryInfo info;

    istringstream iss(query);

    iss >> info.operation;

    if (info.operation != "select")
    {
        cout << "Invalid operation in the query." << endl;
        return info;
    }

    iss >> info.Value;

    iss >> info.tableName;

    getline(iss >> ws, info.tableName, ' ');

    string whereKeyword;
    iss >> whereKeyword;

    if (whereKeyword == "where")
    {
        info.hasCondition = true;

        iss >> info.condition.leftHand >> info.condition.relationalOperator >> info.condition.rightHand;

        getline(iss >> ws, info.condition.rightHand);
    }
    else
    {
        info.hasCondition = false;
    }

    return info;
}

void CallQuery ()
{
    string userQuery;

    cout << "Enter a query: ";
    getline(cin, userQuery);

    QueryInfo query = parseQuery(userQuery);

    if (query.Value == "all")
    {
        if (query.tableName == "Authors")
        {
            if (query.hasCondition)
                if (query.condition.relationalOperator == "=")
                {
                    if(query.condition.leftHand == "authurname"){
                        searchAuthorbyNameA(query.condition.rightHand,Authors);
                    }
                    else if(query.condition.leftHand == "authurid"){
                        searchbYFirstA(query.condition.rightHand,Authors);
                    }

                }
                else
                    cout << "Get all columns from table authors" << endl;
        }
        else if (query.tableName == "Books")
        {
            if (query.hasCondition)
                if (query.condition.relationalOperator == "=")
                {
                    if(query.condition.leftHand == "authorid"){
                        searchBookbyIDA(query.condition.rightHand,Authors);
                    }
                    else if(query.condition.leftHand == "bookisbn"){
                        searchbYFirstA(query.condition.rightHand,Authors);
                    }

                }
                else
                    cout << "Get all columns from table authors" << endl;
        }
        else
            cout << "table doesn't exist";
    }
    else if (query.Value == "AuthorID" && query.tableName == "Authors")
    {
        if (query.hasCondition)
            if (query.condition.relationalOperator == "=")
            {
                if(query.condition.leftHand == "authorid"){
                    searchAuthorbyName1(query.condition.rightHand,Authors);
                }
                else if(query.condition.leftHand == "authurid"){
                    searchbYFirstA(query.condition.rightHand,Authors);
                }

            }
            else
                cout << "Get AuthorID column from table Authors" << endl;
    }
    }
    else if (query.Value == "AuthorName" && query.tableName == "Authors")
    {
        if (query.hasCondition)
            if (query.condition.relationalOperator == "=")
            {
                cout << "the left hand : " << query.condition.leftHand << endl;
                cout << "the operator : " << query.condition.relationalOperator << endl;
                cout << "the right hand : " << query.condition.rightHand << endl;
            }
            else
                cout << "Get AuthorName column from table Authors" << endl;
    }
    else if (query.Value == "Address" && query.tableName == "Authors")
    {
        if (query.hasCondition)
            if (query.condition.relationalOperator == "=")
            {
                cout << "the left hand : " << query.condition.leftHand << endl;
                cout << "the operator : " << query.condition.relationalOperator << endl;
                cout << "the right hand : " << query.condition.rightHand << endl;
            }
            else
                cout << "Get Address column from table Authors" << endl;
    }
    else if (query.Value == "ISBN" && query.tableName == "Books")
    {
        if (query.hasCondition)
            if (query.condition.relationalOperator == "=")
            {
                cout << "the left hand : " << query.condition.leftHand << endl;
                cout << "the operator : " << query.condition.relationalOperator << endl;
                cout << "the right hand : " << query.condition.rightHand << endl;
            }
            else
                cout << "Get ISBN column from table Books" << endl;
    }
    else if (query.Value == "BookTitle" && query.tableName == "Books")
    {
        if (query.hasCondition)
            else if (query.condition.relationalOperator == "=")
            {
                cout << "the left hand : " << query.condition.leftHand << endl;
                cout << "the operator : " << query.condition.relationalOperator << endl;
                cout << "the right hand : " << query.condition.rightHand << endl;
            }
            else
                cout << "Get BookTitle column from table Books" << endl;
    }
    else if (query.Value == "AuthorID" && query.tableName == "Books")
    {
        if (query.hasCondition)
            if (query.condition.relationalOperator == "=")
            {
                cout << "the left hand : " << query.condition.leftHand << endl;
                cout << "the operator : " << query.condition.relationalOperator << endl;
                cout << "the right hand : " << query.condition.rightHand << endl;
            }
            else
                cout << "Get AuthorID column from table Books" << endl;
    }
    else
        cout << "Wrong inputs";
}

};
