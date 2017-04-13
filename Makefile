all: build run clean

build:
	g++ -std=c++11 -o main *.cpp
	
run:
	./main prueba.txt

clean:
	rm main
