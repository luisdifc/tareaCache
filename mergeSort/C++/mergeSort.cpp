#include <iostream>
#include <cstdlib>
#include <mpi.h>


using namespace std;

void merge(int arr[], int l, int m, int r);

void mergeSort(int arr[], int l, int r);

int main(int argc, char ** argv){
    int rc, id, procs;
    int amountNumbers = atoi(argv[1]);

    // rc = MPI_Init(&argc, &argv);

    // MPI_Status stat;

    // MPI_Comm_size(MPI_COMM_WORLD, &procs);
    // MPI_Comm_rank(MPI_COMM_WORLD, &id);

    // cout << "\nProceso numero: " << id << " de: " << procs << endl << endl;

    int* array;

    if(id == 0) {
        //CREACION DEL ARRAY CON NUMEROS ALEATORIOS
        array = new int[amountNumbers];

        cout << "Arreglo a ordenar: " << endl;
        for(int index = 0; index < amountNumbers; index++) {
            array[index] = rand() % amountNumbers;
            cout << array[index] << " ";        
        }
        cout << endl;
    }

    rc = MPI_Init(&argc, &argv);

    MPI_Status stat;

    MPI_Comm_size(MPI_COMM_WORLD, &procs);
    MPI_Comm_rank(MPI_COMM_WORLD, &id);

    // cout << "\nProceso numero: " << id << " de: " << procs << endl << endl;

    int size = amountNumbers/procs;
    int* sub_array = new int[size];

    MPI_Scatter(array, amountNumbers, MPI_INT, sub_array, size, MPI_INT, 0, MPI_COMM_WORLD);

    //ordenamiento
    mergeSort(sub_array, 0, size - 1);

    MPI_Gather(sub_array, size, MPI_INT, array, amountNumbers, MPI_INT, 0, MPI_COMM_WORLD);

    MPI_Barrier(MPI_COMM_WORLD);

    if(id == 0) {
        mergeSort(array, 0, amountNumbers - 1);
        cout << "\nProceso numero: " << id << " de: " << procs << endl << endl;
        cout << endl << "Arreglo ordenado: " << endl;
        //impresion del arreglo ordenado
        for(int index = 0; index < amountNumbers; index++) 
            cout << array[index] << " ";
        cout << endl;
    }

    MPI_Finalize(); 

    return 0;
}


// Merges two subarrays of arr[].
// First subarray is arr[l..m]
// Second subarray is arr[m+1..r]
void merge(int arr[], int l, int m, int r)
{
    int i, j, k;
    int n1 = m - l + 1;
    int n2 =  r - m;
 
    /* create temp arrays */
    int L[n1], R[n2];
 
    /* Copy data to temp arrays L[] and R[] */
    for (i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[m + 1+ j];
 
    /* Merge the temp arrays back into arr[l..r]*/
    i = 0; // Initial index of first subarray
    j = 0; // Initial index of second subarray
    k = l; // Initial index of merged subarray
    while (i < n1 && j < n2)
    {
        if (L[i] <= R[j])
        {
            arr[k] = L[i];
            i++;
        }
        else
        {
            arr[k] = R[j];
            j++;
        }
        k++;
    }
 
    /* Copy the remaining elements of L[], if there
       are any */
    while (i < n1)
    {
        arr[k] = L[i];
        i++;
        k++;
    }
 
    /* Copy the remaining elements of R[], if there
       are any */
    while (j < n2)
    {
        arr[k] = R[j];
        j++;
        k++;
    }
}
 
/* l is for left index and r is right index of the
   sub-array of arr to be sorted */
void mergeSort(int arr[], int l, int r)
{
    if (l < r)
    {
        // Same as (l+r)/2, but avoids overflow for
        // large l and h
        int m = l+(r-l)/2;
 
        // Sort first and second halves
        mergeSort(arr, l, m);
        mergeSort(arr, m+1, r);
 
        merge(arr, l, m, r);
    }
}
