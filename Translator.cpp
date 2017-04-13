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


