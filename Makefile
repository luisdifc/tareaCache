all: build run clean

build:
	g++ -std=c++11 -o main *.cpp
	
run:
	./main prueba5_0.txt prueba5_1.txt >out.txt

clean:
	rm main
