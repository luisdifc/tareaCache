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
	
	int rc;
	rc = MPI_Init(&argc, &argv);

	/********** Create and populate the array **********/
	int amountNumbers = atoi(argv[1]);
	int *unsortedArrayArray = (int*) malloc(amountNumbers * sizeof(int));
	
	srand(time(NULL));
	//printf("This is the unsortedArray array: ");
	for(int index = 0; index < amountNumbers; index++) {	
		unsortedArrayArray[index] = rand() % amountNumbers;
		//printf("%d ", unsortedArrayArray[c]);		
	}

	//printf("\n");
	//printf("\n");
	
	/********** Initialize MPI **********/

	int rank;
	int amountProcesses;

	MPI_Comm_size(MPI_COMM_WORLD, &amountProcesses);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);

	//printf("\namountProcesses: %d\n", amountProcesses);
	//printf("\nId: %d\n", rank);
		
	/********** Divide the array in equal-sized chunks **********/
	int size = amountNumbers/amountProcesses;
	
	/********** Send each subarray to each process **********/
	clock_t begin = clock(); //se inicia un clock

	int *subArray = (int*) malloc(size * sizeof(int));
	MPI_Scatter(unsortedArrayArray, size, MPI_INT, subArray, size, MPI_INT, 0, MPI_COMM_WORLD);
	
	/********** Perform the mergesort on each process **********/
	int *tempArray = (int*) malloc(size * sizeof(int));
	
	mergeSort(subArray, tempArray, 0, (size - 1));
	
	
	/********** Gather the sortedArray subarrays into one **********/
	int *sortedArray = NULL;
	if(rank == 0) {
		
		sortedArray = (int*) malloc(amountNumbers * sizeof(int));
		
		}
	
	MPI_Gather(subArray, size, MPI_INT, sortedArray, size, MPI_INT, 0, MPI_COMM_WORLD);

	

	
	/********** Make the final mergeSort call **********/
	if(rank == 0) {
		
		int *temp2Array = (int*) malloc(amountNumbers * sizeof(int));
		mergeSort(sortedArray, temp2Array, 0, (amountNumbers - 1));


	/********** INFO **********/
		clock_t end = clock(); //se inicia otro clock

		float totalTime = (1000 * (end - begin)) / CLOCKS_PER_SEC;

		cout << "Processes: " << amountProcesses << endl;
		cout << "Time: " << totalTime << "ms" << endl;
		
		/********** Display the sortedArray array **********/
		// printf("This is the sortedArray array: ");
		// for(c = 0; c < n; c++) {
			
		// 	printf("%d ", sortedArray[c]);
			
		// 	}
			
		// printf("\n");
		// printf("\n");
			
		/********** Clean up root **********/
		free(sortedArray);
		free(temp2Array);
			
		}
	
	/********** Clean up rest **********/
	free(unsortedArrayArray);
	free(subArray);
	free(tempArray);
	
	/********** Finalize MPI **********/
	MPI_Barrier(MPI_COMM_WORLD);
	MPI_Finalize();
	
	}

/********** Merge Function **********/
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

/********** Recursive Merge Function **********/
void mergeSort(int *a, int *b, int l, int r) {
	
	int m;
	
	if(l < r) {
		m = (l + r)/2;
		
		mergeSort(a, b, l, m);
		mergeSort(a, b, (m + 1), r);
		merge(a, b, l, m, r);
	}
}