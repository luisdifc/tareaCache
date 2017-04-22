#include "Translator.h"

Translator::Translator() {

}

Translator::~Translator() {

}

// void Translator::reader(char* fileName) {
//     //se abre el archivo con las direcciones
//     ifstream dataFile;
//     dataFile.open(fileName);
//     if (dataFile.is_open()) {
//     	while (!dataFile.eof()) {
//     		getline(dataFile, line);
//     		cout << line << endl;
//     	}
//     }

//     dataFile.close(); //se cierra el archivo ya que no se ocupa mas
// }

void Translator::openFile(char* fileName, ifstream& dataFile) {
    //se abre el archivo con las direcciones
    //ifstream dataFile;
    dataFile.open(fileName);
}

string Translator::readLine(char* fileName, ifstream& dataFile) {
	string line;
	if (dataFile.is_open() && !dataFile.eof())
		getline(dataFile, line);

	return line;
}

void Translator::closeFile(char* fileName, ifstream& dataFile) {
	dataFile.close(); //se cierra el archivo ya que no se ocupa mas
}

int Translator::writeOrRead (string line) {
	//L = lectura, S = escritura
	int write = 0;
	if (line[11] == 'S')
		write = 1;
	return write;
}

int* Translator::HexToBin(string Hex) {
	int* binDir = new int[32];

    for (size_t index = 0; index < 32; index++) {
        binDir[index] = 0;
    }
    for (int index = 2; index < 10; ++index) {
	    switch(Hex[index]) {
	        case '0': break; //"0000"
	        case '1': binDir[((index - 2) * 4) + 3] = 1; break;//"0001"
	        case '2': binDir[((index - 2) * 4) + 2] = 1; break;//"0010"
	        case '3': binDir[((index - 2) * 4) + 2] = binDir[((index - 2) * 4) + 3] = 1; break;//"0011"
	        case '4': binDir[((index - 2) * 4) + 1] = 1; break;//"0100"
	        case '5': binDir[((index - 2) * 4) + 1] = binDir[((index - 2) * 4) + 3] = 1; break;//"0101"
	        case '6': binDir[((index - 2) * 4) + 1] = binDir[((index - 2) * 4) + 2] = 1; break;//"0110"
	        case '7': binDir[((index - 2) * 4) + 1] = binDir[((index - 2) * 4) + 2] = binDir[((index - 2) * 4) + 3] = 1; break;//"0111"
	        case '8': binDir[((index - 2) * 4) + 0] = 1; break;//"1000"
	        case '9': binDir[((index - 2) * 4) + 0] = binDir[((index - 2) * 4) + 3] = 1; break;//"1001"
	        case 'A': binDir[((index - 2) * 4) + 0] = binDir[((index - 2) * 4) + 2] = 1; break; //"1010"
	        case 'B': binDir[((index - 2) * 4) + 0] = binDir[((index - 2) * 4) + 2] = binDir[((index - 2) * 4) + 3] = 1; break;//"1011"
	        case 'C': binDir[((index - 2) * 4) + 0] = binDir[((index - 2) * 4) + 1] = 1; break;//"1100"
	        case 'D': binDir[((index - 2) * 4) + 0] = binDir[((index - 2) * 4) + 1] = binDir[((index - 2) * 4) + 3] = 1; break;//"1101"
	        case 'E': binDir[((index - 2) * 4) + 0] = binDir[((index - 2) * 4) + 1] = binDir[((index - 2) * 4) + 2] = 1; break;//"1110"
	        case 'F': binDir[((index - 2) * 4) + 0] = binDir[((index - 2) * 4) + 1] = binDir[((index - 2) * 4) + 2] = binDir[((index - 2) * 4) + 3] = 1; break;//"1111"
	    }
    }
    return binDir;
}

int* Translator::L1Tag (int* dir) {
	int* cacheTag = new int[19];

	for (int index = 0; index < 19; ++ index)
		cacheTag[index] = dir[index];
	return cacheTag;
}

int* Translator::L1Index (int* dir) {
	int* cacheIndex = new int[8];

	for (int index = 19; index < 27; ++ index)
		cacheIndex[index - 19] = dir[index];
	return cacheIndex;
}

int* Translator::L1Offset (int* dir) {
	int* cacheOffset = new int[5];

	for (int index = 27; index < 32; ++ index)
		cacheOffset[index - 27] = dir[index];
	return cacheOffset;
}

int* Translator::L2Tag (int* dir) {
	int* cacheTag = new int[15];

	for (int index = 0; index < 15; ++ index)
		cacheTag[index] = dir[index];
	return cacheTag;
}

int* Translator::L2Index (int* dir) {
	int* cacheIndex = new int[12];

	for (int index = 15; index < 27; ++ index)
		cacheIndex[index - 15] = dir[index];
	return cacheIndex;
}

int* Translator::L2Offset (int* dir) {
	int* cacheOffset = new int[5];

	for (int index = 27; index < 32; ++ index)
		cacheOffset[index - 27] = dir[index];
	return cacheOffset;
}

int Translator::binToDec (int* binary, int size) {
	int decimalResult = 0;
	for (int index = 0; index < size; ++index)
		decimalResult += binary[(size - 1) - index] * (int) pow(2, index);
	return decimalResult;
}

int Translator::tagComparator (int* cacheTag, int* dirTag, int size) {
	int compare = 0; 
	if (binToDec(cacheTag, size) == binToDec(dirTag, size))
		compare = 1;
	return compare; //1 si lo encuentra
}

char Translator::binToMesi (int* mesi) {
	char result;

	if (mesi[0] == 0 && mesi[1] == 0) // 00 INVALID
		result = 'I';
	else if (mesi[0] == 0 && mesi[1] == 1) //01 EXCLUSIVE
		result = 'E';
	else if (mesi[0] == 1 && mesi[1] == 0) //10 MODIFIED
		result = 'M';
	else if (mesi[0] == 1 && mesi[1] == 1) //11 SHARED
		result = 'S';

	return result;
}

