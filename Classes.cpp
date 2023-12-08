#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <fstream>
#include <queue>
#include <sstream>
#include <functional>



using namespace std;

class Author
{
public:
    string authorId;
    string authorName;
    string address;
    //Author* nextAuthor;

    Author(string& authorId, string& authorName, string& address)
    {
        this->address = address;
        this->authorId = authorId;
        this->authorName = authorName;
        //nextAuthor = nullptr;
    }
    Author() {}

    string toString()
    {
        ostringstream oss;
        int sum = authorId.length()+authorName.length()+address.length()+2;
        string Sum = to_string(sum);
        if(sum < 10)
            Sum = '0' + Sum;
        oss <<Sum<<authorId << "|" << authorName << "|" << address ;
        return oss.str();
    }

    void fromString(string str)
    {
        string sumInString;
        for(int j = 0; j < 2; j++)
            sumInString+=str[j];

        int sum = stoi(sumInString);

        string member1 = "",member2 ="",member3 = "";
        char check = '|';
        int k = 0;
        for(int i = k+2; i < sum-2; i++)
        {
            if(str[i] == check)
                break;
            member1+=str[i];
            k++;
        }
        for(int i = k+3; i < sum; i++)
        {
            if(str[i] == check)
                break;
            member2+=str[i];
            k++;
        }
        for(int i = k+4; i < sum+2; i++)
        {
            if(str[i] == check)
                break;
            member3+=str[i];
            k++;
        }
        setID(member1);//I we need it , use the setters
        setName(member2);
        setaddress(member3);
    }
    string getFmember(){
        return authorId;
    }
    string getSmember(){
        return authorName;
    }

    string getTtmember(){
        return address;
    }
    string PrimaryKey(){
        return authorId;
    }
    void setID(string authorId){
        this->authorId = authorId;
    }
    void setName(string newName)
    {
        this->authorName = newName;
    }
    void setaddress(string newaddress)
    {
        this->address = newaddress;
    }
};
///******************************************************
class Book
{
public:
    string isbn;
    string title;
    string authorId;
    //Book* nextBook;

    Book(string& isbn,string& title,string& authorId)
    {
        this->authorId = authorId;
        this->title = title;
        this->isbn = isbn;
        //nextBook = nullptr;
    }
    Book() {}

    string toString()
    {
        ostringstream oss;
        int sum = isbn.length()+title.length()+authorId.length()+2;
        string Sum = to_string(sum);
        if(sum < 10)
            Sum = '0' + Sum;
        oss <<Sum<<isbn << "|" << title << "|" << authorId ;
        return oss.str();
    }

    void fromString(string str)
    {
        string sumInString;
        for(int j = 0; j < 2; j++)
            sumInString+=str[j];

        int sum = stoi(sumInString);

        string member1 = "",member2 ="",member3 = "";
        char check = '|';
        int k = 0;
        for(int i = k+2; i < sum-2; i++)
        {
            if(str[i] == check)
                break;
            member1+=str[i];
            k++;
        }
        for(int i = k+3; i < sum; i++)
        {
            if(str[i] == check)
                break;
            member2+=str[i];
            k++;
        }
        for(int i = k+4; i < sum+2; i++)
        {
            if(str[i] == check)
                break;
            member3+=str[i];
            k++;
        }
        //cout<<member1 << member2 << member3;
        this->isbn = member1;
        this->title = member2;
        this->authorId = member3;
    }
    string getFmember(){
        return isbn;
    }
    string getSmember(){
        return title;
    }
    string getTtmember(){
        return authorId;
    }
    void setID(string authorId){
        this->authorId = authorId;
    }
    void setName(string newName){
        this->title = newName;
    }
    string PrimaryKey(){
        return isbn;
    }
};
///******************************************************
struct AuthorPIndex  //Author ID As Primary Index
{
    int RRN;
    string authorId;

    AuthorPIndex(string authorId,int RRN)
    {
        this->RRN = RRN;
        this->authorId = authorId;
    }
    string toString()
    {
        ostringstream oss;
        oss <<authorId << "|" << RRN << endl ;
        return oss.str();
    }
    string getId()
    {
        return authorId;
    }
    string PrimaryKey(){
        return authorId;
    }

};
///******************************************************
struct AuthorSIndex  //Author Name As Secondary Index
{
    string authorId;
    string Name;
    AuthorSIndex(string Name,string authorId)
    {
        this->Name = Name;
        this->authorId = authorId;
    }
    string toString()
    {
        ostringstream oss;
        oss <<Name << "|" << authorId << endl ;
        return oss.str();
    }

    string PrimaryKey(){
        return authorId;
    }
    void setName(string newName)
    {
        this->Name = newName;
    }

};
///******************************************************
struct BookPIndex  //ISBN As Primary Index
{
    int RRN;
    string isbn;
    BookPIndex(string isbn,int RRN)
    {
        this->RRN = RRN;
        this->isbn = isbn;
    }
    string toString()
    {
        ostringstream oss;
        oss <<isbn << "|" << RRN << endl ;
        return oss.str();
    }

    string PrimaryKey(){
        return isbn;
    }

};
///******************************************************
struct BookSIndex  //Author ID As Secondary Index
{
    string isbn;
    string authorId;
    BookSIndex(string authorId,string isbn)
    {
        this->isbn = isbn;
        this->authorId = authorId;
    }
    string toString()
    {
        ostringstream oss;
        oss <<authorId << "|" << isbn << endl ;
        return oss.str();
    }

    string PrimaryKey(){
        return isbn;
    }
};


struct AvailList
{

    struct node
    {
        int RRN;
        int size;
        node* next;

        node(int RRN, int size)
        {
            this->RRN = RRN;
            next = nullptr;
            this->size = size;
        }

        int getRRN()
        {
            return RRN;
        }

        int getSize()
        {
            return size;
        }
    };

    node* head;
    int availSize;



    AvailList()
    {
        head = nullptr;
        availSize = 0;
    }


    void insert(int RRN, int size)
    {
        node* newNode = new node(RRN, size);

        if(head == nullptr)     //if the list is empty
        {
            head = newNode;
            availSize++;
            return;
        }

        newNode->next = head;
        head = newNode;
        availSize++;
    }

    int deleteNode(int RRN)
    {
        node* temp = head;
        node* prev = nullptr;

        if(temp != nullptr && temp->RRN == RRN)     //if the deleted node is the head
        {
            int rrn = temp->RRN;
            head = temp->next;
            delete temp;
            availSize--;
            return rrn;
        }

        while(temp != nullptr && temp->RRN != RRN)  //search for the node to be deleted
        {
            prev = temp;
            temp = temp->next;
        }

        if(temp == nullptr)                         //if the node is not found
            return NULL;

        int rrn = temp->RRN;
        prev->next = temp->next;                    //unlink the node from the list
        delete temp;
        availSize--;
        return rrn;
    }

    int updateAvailList(int size)
    {
        node* temp = head;

        for (int i = 0; i < availSize; i++)
        {
            if (size > temp->size)
            {
                temp = temp->next;
            }
            else{
                cout << "size  " << size << "temp size  " << temp->size << endl;
                int rrn = deleteNode(temp->RRN);
                return rrn;
            }
        }
        return NULL;
    }


    void print()
    {
        node* temp = head;
        while(temp != nullptr)
        {
            cout<<temp->RRN<<" ";
            temp = temp->next;
        }
        cout<<endl;
    }

    int getSize()
    {
        return availSize;
    }

    int getHead()
    {
        return head->RRN;
    }

    void setHead(int RRN)
    {
        head->RRN = RRN;
    }

    void setSize(int Size)
    {
        this->availSize = Size;
    }

    bool isEmpty()
    {
        return head == nullptr;
    }

    void clear()
    {
        node* temp = head;
        while(temp != nullptr)
        {
            head = head->next;
            delete temp;
            temp = head;
        }
        availSize = 0;
    }

    ~AvailList()
    {
        clear();
    }


};
