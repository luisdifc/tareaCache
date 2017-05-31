CORES ?= 1
DATA ?= 1000000

SOURCES = main.cpp
MPI_ARGS = -np 1


all: build run 

build:
	mpicxx.mpich $(SOURCES)	-o mergeSort

run:
	mpiexec.mpich $(MPI_ARGS) ./mergeSort $(DATA) > out.txt

install:
	sudo apt-get install openmpi-common openmpi-bin openmpi-doc libopenmpi* mpich

clean:
	rm mergeSort out.txt
