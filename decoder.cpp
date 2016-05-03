

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
		noOfBits = 0;



    //Initiate an input filestream
    ifstream inputFile;
    inputFile.open(inputFileName.c_str(), ios::binary);

    // getting the length of file:
    int length;
    inputFile.seekg (0, ios::end);
    length = inputFile.tellg();
    inputFile.seekg (0, ios::beg);


    //Initiate an ouptut filestream
    string outputFileName = inputFileName;
    outputFileName.erase(outputFileName.end()-4, outputFileName.end());
    outputFileName = outputFileName + "_decoded.txt";
    ofstream outputFile;
    outputFile.open(outputFileName.c_str());


    //Check for error in input data
    if(inputFile.fail())
    {
        cerr << "Can't open the file, exiting" << endl;
        exit(1);
    }
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
    vector<string> decoderTable;
    initializeTable(&decoderTable);

    //get the first code
    char dataIn[2];
    int curCode;
    uint16_t firstByte, lastByte;
    inputFile.read(dataIn, 2);
    firstByte = (uint8_t)dataIn[0];
    firstByte = firstByte << 8;
    lastByte = (uint8_t)dataIn[1];
    curCode =  firstByte  | lastByte;


    //output the string for the code
    string curString = findEntryDecoder(decoderTable, curCode);
    outputFile << curString;

    for(unsigned int i=2; i <=length-2; i=i+2)
    {
        //get the code
        inputFile.read(dataIn, 2);
        firstByte = (uint8_t)dataIn[0];
        firstByte = firstByte << 8;
        lastByte = (uint8_t)dataIn[1];
        curCode =  firstByte  | lastByte;

        string newString;
        if(findEntryDecoder(decoderTable, curCode) == "-99999")
        {
			//assign STRING + STRING[0] to the new string
			newString = curString + curString[0];
        }
        else
        {
            //assign the string associated with the code
            newString = findEntryDecoder(decoderTable, curCode);
        }

        //output the NEWSTRING
        outputFile << newString;

        if(decoderTable.size() < MAX_TABLE_SIZE)
        {
				//If size permits enter into the table
				enterIntoTable(&decoderTable, curString + newString[0]);
        }

       curString = newString;
	}

	outputFile.close();

    return 0;
}





