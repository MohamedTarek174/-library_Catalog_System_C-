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

    Author(string& authorId, string& authorName, string& address)
    {
        this->address = address;
        this->authorId = authorId;
        this->authorName = authorName;
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


    ///Getters
    string getFmember(){
        return authorId;
    }
    string getSmember(){
        return authorName;
    }
    string getTmember(){
        return address;
    }
    ///Setters
    void setFirst(string authorId){
        this->authorId = authorId;
    }
    void setSecond(string authorName){
        this->authorName = authorName;
    }
    void setThird(string address)
    {
        this->address = address;
    }
    string PrimaryKey(){
        return authorId;
    }
};
///******************************************************
class Book
{
public:
    string isbn;
    string title;
    string authorId;

    Book(string& isbn,string& title,string& authorId)
    {
        this->authorId = authorId;
        this->title = title;
        this->isbn = isbn;
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

    ///Getters
    string getFmember(){
        return isbn;
    }
    string getSmember(){
        return title;
    }
    string getTmember(){
        return authorId;
    }
    ///Setters
    void setFirst(string isbn){
        this->isbn = isbn;
    }
    void setSecond(string title){
        this->title = title;
    }
    void setThird(string authorId)
    {
        this->authorId = authorId;
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
    AuthorPIndex(){}
    string toString()
    {
        ostringstream oss;
        oss <<authorId << "|" << RRN << endl ;
        return oss.str();
    }

    string PrimaryKey(){
        return authorId;
    }
       ///Setters
    void setFirst(string authorId){
        this->authorId = authorId;
    }
    void setSecond(int RRN){
        this->RRN = RRN;
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
    AuthorSIndex(){}
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
       ///Setters
    void setFirst(string Name){
        this->Name = Name;
    }
    void setSecond(string authorId){
        this->authorId = authorId;
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
    BookPIndex(){}
    string toString()
    {
        ostringstream oss;
        oss <<isbn << "|" << RRN << endl ;
        return oss.str();
    }

    string PrimaryKey(){
        return isbn;
    }
       ///Setters
    void setFirst(string isbn){
        this->isbn = isbn;
    }
    void setSecond(int RRN){
        this->RRN = RRN;
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
    BookSIndex(){}
    string toString()
    {
        ostringstream oss;
        oss <<authorId << "|" << isbn << endl ;
        return oss.str();
    }

    string PrimaryKey(){
        return isbn;
    }
       ///Setters
    void setFirst(string authorId){
        this->authorId = authorId;
    }
    void setSecond(string isbn){
        this->isbn = isbn;
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

        if(temp == nullptr)
            return NULL;

        int rrn = temp->RRN;
        prev->next = temp->next;
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
struct Condition {
    string leftHand;
    string relationalOperator;
    string rightHand;
};

struct QueryInfo {
    string operation;
    string Value;
    string tableName;
    Condition condition;
    bool hasCondition;
};
