#include "lzw.h"



int main(int argc, char *argv[])
{
    //Get the input filename and bit size
    string inputFileName;
    int noOfBits;
    if (argc <= 1)
	{
		cout << "Usage: " << argv[0] << " <File name>" << " <Bit Number>" << '\n';
		exit(1);
	}

	inputFileName = argv[1];
	stringstream convert(argv[2]);
	if (!(convert >> noOfBits))
		noOfBits = 0;//if can't convert to int, initialize to zero


    //Initiate an input filestream
    streampos size;
    char *inputChar;
    ifstream inputFile (inputFileName.c_str(), ios::in|ios::binary|ios::ate);
    if (inputFile.is_open())
    {
        inputFile.seekg(0, ios::end);
        size = inputFile.tellg();
        inputChar = new char [size];
        inputFile.seekg (0, ios::beg);
        inputFile.read (inputChar, size);
        inputFile.close();
    }
    else
    {
        cerr << "Can't open the file, exiting" << endl;
        exit(1);
    }



    //Initiate an ouptut filestream
    string outputFileName = inputFileName;
    outputFileName.erase(outputFileName.end()-3, outputFileName.end());
    outputFileName = outputFileName + "lzw";
    ofstream outputFile;
    outputFile.open(outputFileName.c_str(), ios::out | ios::binary);


    //Check for error in input data
    if(noOfBits < 0 || noOfBits > 16)
    {
        cerr << "Invalid bit input, exiting" << endl;
        exit(1);
    }
    else
    {
        MAX_TABLE_SIZE = pow(2,noOfBits);
    }


	//Create and initialize the table
    vector<string> encodedTable;
    initializeTable(&encodedTable);



    //temporary variables
    char curChar;
    string curString;
    int val;
    uint8_t BE[2];
    uint16_t valueIn16;

    for(int i = 0; i< size; i++)
    {
        //get input symbol if there are any
        curChar = inputChar[i];

        string testString = curString + curChar;

        //Check if the the STRING+SYMBOL in the table already
        int tempCode = findEntry(encodedTable, testString);

        //If in the table, update the STRING
        if(tempCode != NOT_FOUND)
        {
			curString = testString;
        }
        else
        {
			//Output the code for the STRING
			valueIn16 = findEntry(encodedTable, curString);
			outputFile << (uint8_t)(valueIn16 >> 8) << (uint8_t)valueIn16;

			//If table is not full, enter the STRING + SYMBOL in table
			if(encodedTable.size() < MAX_TABLE_SIZE)
			{
				enterIntoTable(&encodedTable, testString);
			}

			curString = curChar;
		}
	}

    //Output the code for the STRING
    valueIn16 = findEntry(encodedTable, curString);
    outputFile << (uint8_t)(valueIn16 >> 8) << (uint8_t)valueIn16;


	outputFile.close();
	delete [] inputChar;

    return 0;
}





