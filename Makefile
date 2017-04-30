PRUEBA1 ?= 0
PRUEBA2 ?= 0
PRUEBA3 ?= 0
PRUEBA4 ?= 0

SOURCES = src/*.cpp
INCLUDES = include/

ifeq ($(PRUEBA1),1)
	PRUEBAS = Pruebas/prueba1_0.txt Pruebas/prueba1_1.txt
else ifeq ($(PRUEBA2),1)
	PRUEBAS = Pruebas/prueba2_0.txt Pruebas/prueba2_1.txt
else ifeq ($(PRUEBA3),1)
	PRUEBAS = Pruebas/prueba3_0.txt Pruebas/prueba3_1.txt
else ifeq ($(PRUEBA4),1)
	PRUEBAS = Pruebas/prueba4_0.txt Pruebas/prueba4_1.txt
else
	PRUEBAS = Pruebas/mem_trace_core1.txt Pruebas/mem_trace_core2.txt
endif

all: build run clean

build:
	g++ -std=c++11 -o main -I$(INCLUDES) $(SOURCES)	

run:
	./main $(PRUEBAS) >out.txt

clean:
	rm main 
