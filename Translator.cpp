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

void Translator::openFile(char* fileName) {
    //se abre el archivo con las direcciones
    //ifstream dataFile;
    dataFile.open(fileName);
}

string Translator::readLine(char* fileName) {
	string line;
	if (dataFile.is_open() && !dataFile.eof())
		getline(dataFile, line);

	return line;
}

void Translator::closeFile(char* fileName) {
	dataFile.close(); //se cierra el archivo ya que no se ocupa mas
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
