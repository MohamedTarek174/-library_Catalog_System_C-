#include <iostream>
//#include "Classes.cpp"
using namespace std;

///**********************************************Select All*************************************************
template <typename T>
int searchbYFirstA(string ID,vector<T>& OriginalVector)//ID , ISBN (all)
{
    for(T elem : OriginalVector){
        string First = elem.getFmember();
        if(First == ID){
            cout<<elem.getFmember() <<" "<<elem.getSmember()<<" "<<elem.getTmember()<<endl;
        }
    }

}
///**********************************************Select All**************************************************
int searchBookbyIDA(string ID,vector<Book>& OriginalVector)//author ID (book)(all)
{
    for(Book elem : OriginalVector){
        string First = elem.getTmember();
        if(First == ID){
            cout<<elem.getFmember() <<" "<<elem.getSmember()<<" "<<elem.getTmember()<<endl;
        }
    }

}
///*************************************************Select All***********************************************
int searchAuthorbyNameA(string Name,vector<Author>& OriginalVector)//author name (Author)(all)
{
    for(Author elem : OriginalVector){
        string First = elem.getSmember();
        if(First == Name){
            cout<<elem.getFmember() <<" "<<elem.getSmember()<<" "<<elem.getTmember()<<endl;
        }
    }

}
//---------------------------------------------------------------------------------------------------------------
///*********************************************Select member1***************************************************
template <typename T>
int searchBYFirst1(string ID,vector<T>& OriginalVector)//ID , ISBN (all)
{
    for(T elem : OriginalVector){
        string First = elem.getFmember();
        if(First == ID){
            cout<<elem.getFmember()<<endl;
        }
    }

}
///*************************************************Select member1**********************************************
int searchBookbyID1(string ID,vector<Book>& OriginalVector)//author ID (book)(all)
{
    for(Book elem : OriginalVector){
        string First = elem.getTmember();
        if(First == ID){
            cout<<elem.getFmember()<<endl;
        }
    }

}
///************************************************Select member1*********************************************
int searchAuthorbyName1(string Name,vector<Author>& OriginalVector)//author name (Author)(all)
{
    for(Author elem : OriginalVector){
        string First = elem.getSmember();
        if(First == Name){
            cout<<elem.getFmember()<<endl;
        }
    }

}
//---------------------------------------------------------------------------------------------------------------
///*********************************************Select member2***************************************************
template <typename T>
int searchBYFirst2(string ID,vector<T>& OriginalVector)//ID , ISBN (all)
{
    for(T elem : OriginalVector){
        string First = elem.getFmember();
        if(First == ID){
            cout<<elem.getSmember()<<endl;
        }
    }

}
///*************************************************Select member2**********************************************
int searchBookbyID2(string ID,vector<Book>& OriginalVector)//author ID (book)(all)
{
    for(Book elem : OriginalVector){
        string First = elem.getTmember();
        if(First == ID){
            cout<<elem.getSmember()<<endl;
        }
    }

}
///************************************************Select member2*********************************************
int searchAuthorbyName2(string Name,vector<Author>& OriginalVector)//author name (Author)(all)
{
    for(Author elem : OriginalVector){
        string First = elem.getSmember();
        if(First == Name){
            cout<<elem.getSmember()<<endl;
        }
    }

}
//---------------------------------------------------------------------------------------------------------------
///*********************************************Select member3***************************************************
template <typename T>
int searchBYFirst3(string ID,vector<T>& OriginalVector)//ID , ISBN (all)
{
    for(T elem : OriginalVector){
        string First = elem.getFmember();
        if(First == ID){
            cout<<elem.getTmember()<<endl;
        }
    }

}
///*************************************************Select member3**********************************************
int searchBookbyID3(string ID,vector<Book>& OriginalVector)//author ID (book)(all)
{
    for(Book elem : OriginalVector){
        string First = elem.getTmember();
        if(First == ID){
            cout<<elem.getTmember()<<endl;
        }
    }

}
///************************************************Select member3*********************************************
int searchAuthorbyName3(string Name,vector<Author>& OriginalVector)//author name (Author)(all)
{
    for(Author elem : OriginalVector){
        string First = elem.getSmember();
        if(First == Name){
            cout<<elem.getTmember()<<endl;
        }
    }

}
///**********************************************************************************************************
template <typename T>
int searchAllF(vector<T>& OriginalVector){
    for(T elem : OriginalVector){
        string First = elem.getSmember();
        cout<<First<<endl;
    }
}
///**********************************************************************************************************
template <typename T>
int searchAllS(vector<T>& OriginalVector){
    for(T elem : OriginalVector){
        string First = elem.getSmember();
        cout<<First<<endl;
    }
}
///**********************************************************************************************************
template <typename T>
int searchAllT(vector<T>& OriginalVector){
    for(T elem : OriginalVector){
        string First = elem.getSmember();
        cout<<First<<endl;
    }
}
