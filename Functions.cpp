#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <fstream>
#include <queue>
#include <sstream>
#include <functional>
using namespace std;
int SizeAll = 0;
///****************************************************************************************************
template <typename T>
bool CheckIDs(string ID,vector<T>& OriginalVector){
    for(T elem : OriginalVector){
        if(elem.PrimaryKey() == ID)
            return true;
    }
}
///****************************************************************************************************
void SortFile(string filePath){
    fstream File(filePath);
    vector<string> lines;
    if (File.is_open())
    {
        string line;
        while (getline(File, line))
        {
            lines.push_back(line);
        }
        File.close();
    }
    if(lines.size() == 1)
        return;
    sort(lines.begin(), lines.end());//Sort the vector
    File.open(filePath,std::fstream::out | std::fstream::trunc );//Empty the original one
    for (const auto& line : lines)
    {
        File << line << endl;
    }
    File.close();

}
///****************************************************************************************************
int calculateQueueSum(queue<int>& myQueue){
    queue<int> tempQueue = myQueue;
    int sum = 0;

    while (!tempQueue.empty())
    {
        sum += tempQueue.front();
        tempQueue.pop();
    }
    return sum;
}
///****************************************************************************************************
template <typename T>
void AddtoFiles(string filepath,vector<T>& OriginalVector,T newT){
    fstream File;
    File.open(filepath, ios::out|ios::app|ios::in);
    string newTString = newT.toString();
    SizeAll = newTString.length();
    File << newTString;//Add the Author to the file
    string key = newT.PrimaryKey();
    if(!CheckIDs(key,OriginalVector))
        OriginalVector.push_back(newT);//Add it to the vector
    if(!CheckIDs(key,OriginalVector))
        OriginalVector.push_back(newT);//Add it to the vector
}
///****************************************************************************************************
template <typename T>
void AddForDataFile(string filepath,vector<T>& OriginalVector,string member1,string member2,string member3){
    T newT(member1, member2, member3);//Create one
    AddtoFiles(filepath,OriginalVector,newT);
}
///****************************************************************************************************
template <typename T>
void AddForPIFile(string filepath,vector<T>& OriginalVector,string member,queue<int>& offsetTemp){
    int Offset = calculateQueueSum(offsetTemp);
    offsetTemp.push(SizeAll);

    T newT(member, Offset);//Create one
    AddtoFiles(filepath,OriginalVector,newT);
    SortFile(filepath);

}
///****************************************************************************************************
template <typename T>
void AddForSIFile(string filepath,vector<T>& OriginalVector,string member1,string member2){
    T newT(member1, member2);//Create one
    AddtoFiles(filepath,OriginalVector,newT);
    SortFile(filepath);
}
///****************************************************************************************************
template <typename T>
void UpdateForAll(vector<T>& OriginalVector,string Old,string New,queue<int>& offsetTemp)
{
    queue<int> EmptyoffsetT;
    swap(offsetTemp, EmptyoffsetT);
    offsetTemp.push(0);
    vector<T> TempOfdata;
    for (T elem : OriginalVector)
    {
        if (elem.getFmember() == Old)
        {
            elem.setName(New);
        }
        TempOfdata.push_back(elem);
    }

    OriginalVector.clear();
    OriginalVector = TempOfdata;




}
///****************************************************************************************************
template <typename T>
void DeleteForAll(string filepath,vector<T>& OriginalVector,string DeletedTarget)
 {
    queue<int> EmptyoffsetT;
    swap(offsetTemp, EmptyoffsetT);
    offsetTemp.push(0);
    vector<T> TempOfdata;
    for (T elem : OriginalVector)
    {
        if (elem.getFmember() == Old)
        {
            elem.setID("*");
        }
        TempOfdata.push_back(elem);
    }

    OriginalVector.clear();
    OriginalVector = TempOfdata;
}
