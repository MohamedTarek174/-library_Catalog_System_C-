#include "Classes.cpp"
#include "Functions.cpp"
#include "Search.cpp"

using namespace std;

class LibraryCatalog
{
private:

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
        offsetAuthors.push(0);
        offsetBooks.push(0);
        ImportDataFile("Authors.txt",Authors);
        ImportDataFile("Books.txt",Books);
        ImportPIDataFile("PrimaryAu.txt",AuthorsPrimaryIndex,offsetAuthors);
        ImportPIDataFile("PrimaryBo.txt",BooksPrimaryIndex,offsetBooks);
        ImportSIDataFile("SecondaryAu.txt",AutherSecondaryIndex);
        ImportSIDataFile("SecondaryBo.txt",BooksSecondaryIndex);
    }

///***************************************************************************************************************
    ~LibraryCatalog(){}

///********************************Import DATA********************************************************************
    template <typename T>
        void ImportDataFile(string filepath,vector<T>& OriginalVector){
        fstream File;
        File.open(filepath, ios::in|ios::out|ios::app);
        string str,newline;
        getline(File,str);

        int counter = 0,k = 0,AllLengths = 0;

        if(str == "")
            return;
        while(true){
            if(newline == str)
                return;
            string sumInString;//The first two digits in the record
            for(int j = AllLengths;j < AllLengths+2;j++)
                sumInString+=str[j];


            int sum = stoi(sumInString);//switch it to int

            AllLengths = AllLengths + sum + 2;

            string member1 = "",member2 = "",member3 = "";

            char check = '|';

            int charCounter = 0;
            for(int i = k+2;i < AllLengths+sum;i++){
                charCounter++;
                if(str[i] == check)
                    break;
                member1+=str[i];
                k++;
            }
            for(int i = k+3;i < AllLengths+sum;i++){
                charCounter++;
                if(str[i] == check)
                    break;
                member2+=str[i];
                k++;
            }
            for(int i = k+4;i < AllLengths+sum;i++){
                if(charCounter == sum)
                    break;
                charCounter++;
                member3+=str[i];
                k++;
            }
            k = AllLengths;
            T newT;
            newT.setFirst(member1);
            newT.setSecond(member2);
            newT.setThird(member3);
            string newTinString = newT.toString();
            newline = newline + newTinString;
            OriginalVector.push_back(newT);

        }
        File.close();
    }

    template <typename T>
    void ImportPIDataFile(string filepath,vector<T>& OriginalVector,queue<int>& QueuefOffsets)
    {
        fstream File;
        File.open(filepath, ios::in|ios::out|ios::app);
        string line;

        while (getline(File, line))
        {
            string member1;
            string member2;

            int i;
            for (i = 0; i < line.length(); i++)
            {
                if (line[i] == '|')
                    break;
                member1 += line[i];
            }
            i = 0;
            for (int j = 0; j < line.length(); j++)
            {
                if(line[i] == member1[i] || line[i] == '|'){
                    i++;
                    continue;
                }

                member2+=line[i];
                i++;
            }
            int member2INT = stoi(member2);
            T newT;
            newT.setFirst(member1);
            newT.setSecond(member2INT);
            OriginalVector.push_back(newT);
            QueuefOffsets.push(member2INT);
        }
        File.close();
    }

    template <typename T>
    void ImportSIDataFile(string filepath,vector<T>& OriginalVector)
    {
        fstream File;
        File.open(filepath, ios::in|ios::out|ios::app);
        string line;

        while (getline(File, line))
        {

            istringstream ss(line);
            string token;

            T newT;

            if (getline(ss, token, '|')) {
                newT.setFirst(token);
            }

            if (getline(ss, token, '|')) {
                newT.setSecond(token);
            }

            OriginalVector.push_back(newT);
        }
        File.close();
    }

///*************************************Check IDs/ISBNs*********************************************************
    bool checkAuthorForUpdate(string authorId)
    {
        if(!CheckIDs(authorId,Authors))
            return false;
        return true;
    }

    bool checkBookForUpdate(string isbn)
    {
        if(!CheckIDs(isbn,Books))
            return false;
        return true;
    }

///****************************************ADD*****************************************************************
    void addAuthor(string authorId,string authorName,string address)
    {
        if(AddForDataFile("Authors.txt",Authors,authorId,authorName,address)){
            fstream FilePI("PrimaryAu.txt", std::fstream::out | std::fstream::trunc);
            fstream FileSI("SecondaryAu.txt", std::fstream::out | std::fstream::trunc);
            queue<int> EmptyoffsetT;
            swap(offsetAuthors, EmptyoffsetT);
            offsetAuthors.push(0);
            AuthorsPrimaryIndex.clear();
            AutherSecondaryIndex.clear();
            for(Author elements : Authors){
                AddForPIFile("PrimaryAu.txt",AuthorsPrimaryIndex,elements.PrimaryKey(),offsetAuthors);
                AddForSIFile("SecondaryAu.txt",AutherSecondaryIndex,elements.getSmember(),elements.PrimaryKey());
            }
        }
        else{
            AddForPIFile("PrimaryAu.txt",AuthorsPrimaryIndex,authorId,offsetAuthors);
            AddForSIFile("SecondaryAu.txt",AutherSecondaryIndex,authorName,authorId);
        }

    }

    void addBook(string isbn, string title, string authorId){

        AddForDataFile("Books.txt",Books,isbn,title,authorId);
        AddForPIFile("PrimaryBo.txt",BooksPrimaryIndex,isbn,offsetBooks);
        AddForSIFile("SecondaryBo.txt",BooksSecondaryIndex,authorId,isbn);
    }

///*************************************Delete*****************************************************************
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
        cout<<"DONE"<<endl;

    }

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
        cout<<"DONE"<<endl;
    }


///***************************************Update**************************************************************
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
        cout<<"DONE"<<endl;
    }

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
        cout<<"DONE"<<endl;
    }

///*************************************Query******************************************************************
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
                        if(query.condition.leftHand == "authorname"){
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
                            searchBookbyIDA(query.condition.rightHand,Books);
                        }
                        else if(query.condition.leftHand == "bookisbn"){
                            searchbYFirstA(query.condition.rightHand,Books);
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
                searchAllF(Authors);
                cout << "Get AuthorID column from table Authors" << endl;
        }
        else if (query.Value == "AuthorName" && query.tableName == "Authors")
        {
                searchAllS(Authors);
                cout << "Get AuthorName column from table Authors" << endl;
        }
        else if (query.Value == "Address" && query.tableName == "Authors")
        {
                searchAllT(Authors);
                cout << "Get Address column from table Authors" << endl;
        }
        else if (query.Value == "ISBN" && query.tableName == "Books")
        {
                searchAllF(Books);
                cout << "Get ISBN column from table Books" << endl;
        }
        else if (query.Value == "BookTitle" && query.tableName == "Books")
        {
                searchAllS(Books);
                cout << "Get BookTitle column from table Books" << endl;
        }
        else if (query.Value == "AuthorID" && query.tableName == "Books")
        {
                searchAllT(Books);
                cout << "Get AuthorID column from table Books" << endl;
        }
        else
            cout << "Wrong inputs";
    }

///*************************************Print******************************************************************
    void PrintAuthor(string authorId)
    {
        if(!checkAuthorForUpdate(authorId)){
            cout<<"this Author ID is not exist!!"<<endl;
            return;
        }else{
            int low = 0;
            int high = Authors.size() - 1;

            while (low <= high) {
                int mid = low + (high - low) / 2;
                Author midValue = Authors[mid];
                string Key = midValue.PrimaryKey();
                if (Key == authorId) {
                    cout<<midValue.getFmember()<<" "<<midValue.getSmember()<<" "<<midValue.getTmember()<<endl;
                    break;
                } else if (Key < authorId) {
                    low = mid + 1;
                } else {
                    high = mid - 1;
                }
            }
        }

    }

    void PrintBook(string isbn)
    {
        if(!checkBookForUpdate(isbn)){
            cout<<"this Book ISBN is not exist!!"<<endl;
            return;
        }else{
            int low = 0;
            int high = Books.size() - 1;

            while (low <= high) {
                int mid = low + (high - low) / 2;
                Book midValue = Books[mid];
                string Key = midValue.PrimaryKey();
                if (Key == isbn) {
                    cout<<midValue.getFmember()<<" "<<midValue.getSmember()<<" "<<midValue.getTmember()<<endl;
                    break;
                } else if (Key < isbn) {
                    low = mid + 1;
                } else {
                    high = mid - 1;
                }
            }
        }

    }

};
