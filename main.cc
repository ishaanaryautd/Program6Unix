//Name: Ishaan Arya
//NetID: ixa160130
//Program6
//CS 3377.502
#include <iostream>
#include <string>
#include <stdio.h>
#include "cdk.h"
#include <stdint.h>
#include <fstream>
#include <sstream>

#define MATRIX_WIDTH 3
#define MATRIX_HEIGHT 5
#define BOX_WIDTH 20
#define MATRIX_NAME_STRING "Binary File Contents"

using namespace std;

class BinaryFileHeader
{
	public:

		uint32_t magicNumber;
		uint32_t versionNumber;
		uint64_t numRecords;
};

const int maxRecordStringLength = 25;

class BinaryFileRecord
{
	public:
		uint8_t strLength;
		char stringBuffer[maxRecordStringLength];
};

int main()
{

	WINDOW *window;
	CDKSCREEN *cdkscreen;
	CDKMATRIX *myMatrix;           // CDK Screen Matrix                                                                                                          

	// Remember that matrix starts out at 1,1.                                                                                                                       
	// Since arrays start out at 0, the first entries                                                                                                                
	// below ("R0", and "C0") are just placeholders                                                                                                                  
	//                                                                                                                                                               
	// Finally... make sure your arrays have enough entries given the                                                                                                
	// values you choose to set for MATRIX_WIDTH and MATRIX_HEIGHT                                                                                                   
	// above.                                                                                                                                                        

	const char *rowTitles[] = {"R0", "a", "b", "c", "d", "e"};
	const char *columnTitles[] = {"C0", "a", "b", "c"};
	int boxWidths[] = {BOX_WIDTH, BOX_WIDTH, BOX_WIDTH, BOX_WIDTH, BOX_WIDTH, BOX_WIDTH};
	int boxTypes[] = {vMIXED, vMIXED, vMIXED, vMIXED,  vMIXED,  vMIXED};
	/*                                                                                                                                                               
	* Initialize the Cdk screen.                                                                                                                                    
	*                                                                                                                                                               
	* Make sure the putty terminal is large enough                                                                                                                  
 	*/
	window = initscr();
	cdkscreen = initCDKScreen(window);

	/* Start CDK Colors */
	initCDKColor();

	/*                                                                                                                                                               
	* Create the matrix.  Need to manually cast (const char**) to (char **)                                                                                         
 	*/
	myMatrix = newCDKMatrix(cdkscreen, CENTER, CENTER, MATRIX_HEIGHT, MATRIX_WIDTH, MATRIX_HEIGHT, MATRIX_WIDTH,
        MATRIX_NAME_STRING, (char **) rowTitles, (char **) columnTitles, boxWidths, boxTypes, 1, 1, ' ', ROW, true, true, false);
	if (myMatrix ==NULL)
   	{
      		printf("Error creating Matrix\n");
      		_exit(1);
    	}

 	/* Display the Matrix */
	drawCDKMatrix(myMatrix, true);

 	/*                                                                                                                                                               
  	* Dipslay a message                                                                                                                                             
  	*/
	
	BinaryFileHeader *myHeader = new BinaryFileHeader();
	ifstream binInFile("cs3377.bin", ios::in | ios::binary);
        binInFile.read((char*)myHeader,sizeof(BinaryFileHeader));
        unsigned int magicNumber = myHeader->magicNumber;
	unsigned int versionNumber = myHeader->versionNumber;
	unsigned long long numRecords = myHeader->numRecords;
	
	char magic_number[10];
	sprintf(magic_number,"%x",magicNumber);//convert to hex
	string s = magic_number;
	for (unsigned int i = 0; i < s.length() ; i++) //comvert to uppercase
	{
		magic_number[i] = toupper(magic_number[i]);
	}
	string version_number = to_string(versionNumber);
	string num_records = to_string(numRecords);
	string a = "Magic : 0x" + string(magic_number);

	setCDKMatrixCell(myMatrix, 1, 1, a.c_str());
	setCDKMatrixCell(myMatrix, 1, 2, version_number.c_str());
	setCDKMatrixCell(myMatrix, 1, 3, num_records.c_str());
	
	BinaryFileRecord *myRecord = new BinaryFileRecord();
	
	//reading the records from the binary file and displaying it in the matrix
	for (int i = 2; i <= int(numRecords) + 1; i++)
	{
		binInFile.read((char*)myRecord,sizeof(BinaryFileRecord));
		char* str = myRecord->stringBuffer;
		int length = string(str).length();
		string len = to_string(length);//we need string to write into matrix
		setCDKMatrixCell(myMatrix, i, 1, len.c_str()); //putting it in matrix
		setCDKMatrixCell(myMatrix, i, 2, str);
	}
	
	binInFile.close(); //closing the file
	
	drawCDKMatrix(myMatrix, true);    /* required  */

 	/* So we can see results, pause until a key is pressed. */
	unsigned char x;
	cin >> x;

 	 // Cleanup screen                                                                                                                                                
	endCDK();
}
