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


int* Translator::HexToBin(char Hex, int* bin) {
    for (size_t index = 0; index < 4; index++) {
        bin[index] = 0;
    }
    switch(Hex) {
        case '0': break; //"0000"
        case '1': bin[0] = 1; break;//"0001"
        case '2': bin[1] = 1; break;//"0010"
        case '3': bin[1] = bin[0] = 1; break;//"0011"
        case '4': bin[2] = 1; break;//"0100"
        case '5': bin[2] = bin[0] = 1; break;//"0101"
        case '6': bin[2] = bin[1] = 1; break;//"0110"
        case '7': bin[2] = bin[1] = bin[0] = 1; break;//"0111"
        case '8': bin[3] = 1; break;//"1000"
        case '9': bin[3] = bin[0] = 1; break;//"1001"
        case 'A': bin[3] = bin[1] = 1; break; //"1010"
        case 'B': bin[3] = bin[1] = bin[0] = 1; break;//"1011"
        case 'C': bin[3] = bin[2] = 1; break;//"1100"
        case 'D': bin[3] = bin[2] = bin[0] = 1; break;//"1101"
        case 'E': bin[3] = bin[2] = bin[1] = 1; break;//"1110"
        case 'F': bin[3] = bin[2] = bin[1] = bin[0] = 1; break;//"1111"
    }
    return bin;
}
