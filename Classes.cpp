#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
#include <sstream>
#include <string>


using namespace std;

class Author {
public:
    string authorId;
    string authorName;
    string address;
    //Author* nextAuthor;

    Author(string& authorId, string& authorName, string& address){
        this->address = address;
        this->authorId = authorId;
        this->authorName = authorName;
        //nextAuthor = nullptr;
    }
    Author(){}

    string toString() {
        ostringstream oss;
        int sum = authorId.length()+authorName.length()+address.length()+2;
        string Sum = to_string(sum);
        if(sum < 10)
            Sum = '0' + Sum;
        oss <<Sum<<authorId << "|" << authorName << "|" << address ;
        return oss.str();
    }

    void fromString(string str) {
        string sumInString;
        for(int j = 0;j < 2;j++)
            sumInString+=str[j];

        int sum = stoi(sumInString);

        string member1 = "",member2 ="",member3 = "";
        char check = '|';
        int k = 0;
        for(int i = k+2;i < sum-2;i++){
            if(str[i] == check)
                break;
            member1+=str[i];
            k++;
        }
        for(int i = k+3;i < sum;i++){
            if(str[i] == check)
                break;
            member2+=str[i];
            k++;
        }
        for(int i = k+4;i < sum+2;i++){
            if(str[i] == check)
                break;
            member3+=str[i];
            k++;
        }
        //cout<<member1 << member2 << member3;
        this->authorId = member1;
        this->authorName = member2;
        this->address = member3;
    }
    string getId(){return authorId;}
};


class Book {
public:
    string isbn;
    string title;
    string authorId;
    //Book* nextBook;

    Book(string& isbn,string& title,string& authorId){
        this->authorId = authorId;
        this->title = title;
        this->isbn = isbn;
        //nextBook = nullptr;
    }
    Book(){}

    string toString() {
        ostringstream oss;
        int sum = isbn.length()+title.length()+authorId.length()+2;
        string Sum = to_string(sum);
        if(sum < 10)
            Sum = '0' + Sum;
        oss <<Sum<<isbn << "|" << title << "|" << authorId ;
        return oss.str();
    }

    void fromString(string str) {
        string sumInString;
        for(int j = 0;j < 2;j++)
            sumInString+=str[j];

        int sum = stoi(sumInString);

        string member1 = "",member2 ="",member3 = "";
        char check = '|';
        int k = 0;
        for(int i = k+2;i < sum-2;i++){
            if(str[i] == check)
                break;
            member1+=str[i];
            k++;
        }
        for(int i = k+3;i < sum;i++){
            if(str[i] == check)
                break;
            member2+=str[i];
            k++;
        }
        for(int i = k+4;i < sum+2;i++){
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
    string getId(){return isbn;}


};

struct AuthorPIndex {//Author ID As Primary Index
	int RRN;
	string authorId;

    AuthorPIndex(string authorId,int RRN) {
        this->RRN = RRN;
        this->authorId = authorId;
    }
    string toString() {
        ostringstream oss;
        oss <<authorId << "|" << RRN << endl ;
        return oss.str();
    }
    string getId(){return authorId;}


};
struct AuthorSIndex {//Author Name As Secondary Index
	string authorId;
	string Name;
	AuthorSIndex(string Name,string authorId) {
        this->Name = Name;
        this->authorId = authorId;
    }
    string toString() {
        ostringstream oss;
        oss <<authorId << "|" << Name << endl ;
        return oss.str();
    }
    string getId(){return authorId;}

};

struct BookPIndex {//ISBN As Primary Index
	int RRN;
	string isbn;
	BookPIndex(string isbn,int RRN) {
        this->RRN = RRN;
        this->isbn = isbn;
    }
    string toString() {
        ostringstream oss;
        oss <<isbn << "|" << RRN << endl ;
        return oss.str();
    }
    string getId(){return isbn;}

};
struct BookSIndex {//Author ID As Secondary Index
	string isbn;
    string authorId;
	BookSIndex(string authorId,string isbn) {
        this->isbn = isbn;
        this->authorId = authorId;
    }
    string toString() {
        ostringstream oss;
        oss <<authorId << "|" << isbn << endl ;
        return oss.str();
    }
    string getId(){return isbn;}

};

/*
//functions to make them reference in the sort function as third parametar
bool compareAuthorsById(Author* a,Author* b) {//In Primary Authors
    return a->authorId < b->authorId;
}

bool compareAuthorsByName(Author* a,Author* b) {//In secondary Authors
    return a->authorName < b->authorName;
}

bool comparebooksByisbn(Book* a, Book* b) {//In Primary Books
     return a->isbn < b->isbn;
}

bool compareBooksByAuthorsId(Book* a,Book* b) {//In secondary Books
    return a->authorId < b->authorId;
}
*/
