#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <mpi.h>

using namespace std;

//Definicion de las funciones de ordenamiento
void merge(int *, int *, int, int, int);
void mergeSort(int *, int *, int, int);

int main(int argc, char ** argv){

    //Declaración de variables.
    int rc, amountNumbers, rank, amountProcesses, sizeSubArrays;
    int *unsortedArray, *subArray, *tempArray, *sortedArray, *temp2Array; 

    //Inicializacion del ambiente de MPI. 	
	rc = MPI_Init(&argc, &argv);

	//Arreglo desordenado con numeros generados aleatoreamente.
	amountNumbers = atoi(argv[1]);
	unsortedArray = (int*) malloc(amountNumbers * sizeof(int));
    srand(time(NULL));
	for(int index = 0; index < amountNumbers; index++) {	
		unsortedArray[index] = rand() % amountNumbers;
	}

    //Obtengo el numero de procesos y un identificador para cada uno de ellos.
	MPI_Comm_size(MPI_COMM_WORLD, &amountProcesses);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    //Tamaño del arreglo asinado a cada core.
    sizeSubArrays = amountNumbers/amountProcesses;
	
	//Marca de tiempo para medicion de inicio de ejecucion.
    clock_t begin = clock();

    //Reserva de espacio en memoria para el arreglo asinado a cada core.
	subArray = (int*) malloc(sizeSubArrays * sizeof(int));

    //Funcion que separa el arreglo desordenado y le asigna una seccion a cada core.
	MPI_Scatter(unsortedArray, sizeSubArrays, MPI_INT, subArray, sizeSubArrays, MPI_INT, 0, MPI_COMM_WORLD);
	
	//Arrego temporal para obtener los sub arreglos ordenados de cada core.
    tempArray = (int*) malloc(sizeSubArrays * sizeof(int));
	mergeSort(subArray, tempArray, 0, (sizeSubArrays - 1));
	
	//Se procede a unir los resultados. Esta tarea solo la realiza el core 0.
    if(rank == 0)
		sortedArray = (int*) malloc(amountNumbers * sizeof(int));

    //Funcion que une todo sub arreglos ordenados por cada core y almacena el resultado en sortedArray.	
	MPI_Gather(subArray, sizeSubArrays, MPI_INT, sortedArray, sizeSubArrays, MPI_INT, 0, MPI_COMM_WORLD);

    //Ordenamiento final. Solo lo realiza el core 0.
	if(rank == 0) {
        //Se aplica finalmente el algoritmo de ordenamiento sobre el arreglo final.
		temp2Array = (int*) malloc(amountNumbers * sizeof(int));
		mergeSort(sortedArray, temp2Array, 0, (amountNumbers - 1));

        //Marca de tiempo para medicion de fin de ejecucion.
		clock_t end = clock();

		//impresion de la cantidad de procesos utilizados.
		cout << "Processes: " << amountProcesses << endl;

        //Se obtiene el tiempo de ejecucion y se imprime.
		float totalTime = (1000 * (end - begin)) / CLOCKS_PER_SEC;
		if (totalTime == 0) { 
			totalTime = (1000000 * (end - begin)) / CLOCKS_PER_SEC;
			cout << "Sorting time: " << totalTime << "\u00B5s" << endl;
		}
		else
			cout << "Sorting time: " << totalTime << "ms" << endl;
		

		//Impresion del arreglo NO ordenado
		cout << "\nUnsorted array: ";
		for (int index = 0; index < amountNumbers; index++)
			cout << unsortedArray[index] << " ";
		cout << endl;

		//Impresion del arreglo ordenado
		cout << "\nSorted array: ";
		for (int index = 0; index < amountNumbers; index++)
			cout << sortedArray[index] << " ";
		cout << endl;
		
		//Liberacion de memoria reservada.
        free(sortedArray);
		free(temp2Array);
			
		}
	
	//Liberacion de memoria reservada.
    free(unsortedArray);
	free(subArray);
	free(tempArray);
	
	//Espera a que todos los procesos terminen y finaliza el ambiente de MPI.
	MPI_Barrier(MPI_COMM_WORLD);
	MPI_Finalize();
	
	}

//Algoritmo de merge.
void merge(int *a, int *b, int l, int m, int r) {
	
	int h, i, j, k;
	h = l;
	i = l;
	j = m + 1;
	
	while((h <= m) && (j <= r)) {
		if(a[h] <= a[j]) {
			b[i] = a[h];
			h++;
		} else {
			b[i] = a[j];
			j++;
		}	
		i++;	
	}
		
	if(m < h) {
		for(k = j; k <= r; k++) {
			b[i] = a[k];
			i++;
		}	
	} else {
		for(k = h; k <= m; k++) {
			b[i] = a[k];
			i++;
		}	
	}
		
	for(k = l; k <= r; k++) 
		a[k] = b[k];

}

//Funcion recursiva para algoritmo de merge.
void mergeSort(int *a, int *b, int l, int r) {
	
	int m;
	
	if(l < r) {
		m = (l + r)/2;
		
		mergeSort(a, b, l, m);
		mergeSort(a, b, (m + 1), r);
		merge(a, b, l, m, r);
	}
}
