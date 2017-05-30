#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <mpi.h>

using namespace std;

//Definicion de las funciones de ordenamiento
void merge(int *, int *, int, int, int);
void mergeSort(int *, int *, int, int);

int main(int argc, char ** argv){
	
	int rc;
	rc = MPI_Init(&argc, &argv);

	/********** Create and populate the array **********/
	int n = atoi(argv[1]);
	int *original_array = (int*) malloc(n * sizeof(int));
	
	int c;
	srand(time(NULL));
	//printf("This is the unsorted array: ");
	for(c = 0; c < n; c++) {
		
		original_array[c] = rand() % n;
		//printf("%d ", original_array[c]);
		
		}

	//printf("\n");
	//printf("\n");
	
	/********** Initialize MPI **********/

	int world_rank;
	int world_size;

	MPI_Comm_size(MPI_COMM_WORLD, &world_size);
	MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);

	//printf("\nworld_size: %d\n", world_size);
	//printf("\nId: %d\n", world_rank);
		
	/********** Divide the array in equal-sized chunks **********/
	int size = n/world_size;
	
	/********** Send each subarray to each process **********/
	clock_t begin = clock(); //se inicia un clock
	int *sub_array = (int*) malloc(size * sizeof(int));
	MPI_Scatter(original_array, size, MPI_INT, sub_array, size, MPI_INT, 0, MPI_COMM_WORLD);
	
	/********** Perform the mergesort on each process **********/
	int *tmp_array = (int*) malloc(size * sizeof(int));
	
	mergeSort(sub_array, tmp_array, 0, (size - 1));
	
	
	/********** Gather the sorted subarrays into one **********/
	int *sorted = NULL;
	if(world_rank == 0) {
		
		sorted = (int*) malloc(n * sizeof(int));
		
		}
	
	MPI_Gather(sub_array, size, MPI_INT, sorted, size, MPI_INT, 0, MPI_COMM_WORLD);

	

	
	/********** Make the final mergeSort call **********/
	if(world_rank == 0) {
		
		int *other_array = (int*) malloc(n * sizeof(int));
		mergeSort(sorted, other_array, 0, (n - 1));
		clock_t end = clock(); //se inicia otro clock

		
		float total_time = (1000 * (end - begin)) / CLOCKS_PER_SEC;
		printf("Processes: %d\n", world_size);
		printf ("Time: %f ms\n", total_time);
		
		/********** Display the sorted array **********/
		// printf("This is the sorted array: ");
		// for(c = 0; c < n; c++) {
			
		// 	printf("%d ", sorted[c]);
			
		// 	}
			
		// printf("\n");
		// printf("\n");
			
		/********** Clean up root **********/
		free(sorted);
		free(other_array);
			
		}
	
	/********** Clean up rest **********/
	free(original_array);
	free(sub_array);
	free(tmp_array);
	
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
			
			}
			
		else {
			
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
			
		}
		
	else {
		
		for(k = h; k <= m; k++) {
			
			b[i] = a[k];
			i++;
			
			}
			
		}
		
	for(k = l; k <= r; k++) {
		
		a[k] = b[k];
		
		}
		
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