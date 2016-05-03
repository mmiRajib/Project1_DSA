//                                           ITCS 6114/8114: Algorithms and Data Structures
// 					      Programming Project 1: LZW Compression
// 					            Md Rajib, mrajib@uncc.edu


#ifndef LZW_H
#define LZW_H

#include <iostream> //For simple input output operation
#include <vector>   //For data
#include <algorithm> //For seraching in code table
#include <string> //For string manipulation
#include <fstream> //For file manipulation
#include <sstream> //Used in accordance with stream
#include <stdlib.h> //To throw error
#include <math.h> //To use power function
#include <stdint.h> //For using uint16_t data type


//Constants that were used insode the functions
const int NOT_FOUND = -9999;
unsigned long MAX_TABLE_SIZE;

using namespace std;


//Auxiliary function prototypes
void initializeTable(vector<string>* myTable);
void enterIntoTable(vector<string>* myTable, string wordEntry);
int findEntry(vector<string> myTable, string findWord);
string findEntryDecoder(vector<string> myTable, int code);




//This function initializes table with ASCII and Extended ASCII values
void initializeTable(vector<string>* myTable)
{
    for(int i =0; i <=255; i++)
    {
        char c = i;
        string s(1, c);//entry of one character
        enterIntoTable(myTable,s);
    }

}


//This is used to enter strings into the table
void enterIntoTable(vector<string>* myTable, string wordEntry)
{
    if(myTable->size() < MAX_TABLE_SIZE)
        myTable->push_back(wordEntry);
    else
    {
        cerr << "Can't enter, table Overflow" << endl;
        exit(1);
    }
}


//This function search a string in the table and
//returns associated code
int findEntry(vector<string> myTable, string findWord)
{
	int i = find(myTable.begin(), myTable.end(), findWord) - myTable.begin();

	if ( i < myTable.size())
			return i;
	else
        return NOT_FOUND;
}


//This function returns associated string with respect to code
string findEntryDecoder(vector<string> myTable, int code)
{
    if((unsigned int)code < myTable.size())
        return myTable.at(code);
    else
        return "-99999";
}

#endif
