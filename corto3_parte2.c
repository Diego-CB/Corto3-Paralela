#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <mpi.h>

// Generacion de vector de numeros aleatorios
int* randGen() {
    srand(1);
    int* numeros = (int*)malloc(5000 * sizeof(int));

    for (int i = 0; i < 5000; i++) {
        int val = rand() % 1000;
        val = val < 0 ? val * -1 : val;
        // printf("> %d\n", val);
        numeros[i] = val;
    }
    return numeros;
}

int main(int argc, char** argv) {
    MPI_Init(&argc, &argv); // Iniciar ambiente de MPI

    // Obtener numero de procesos
    int world_size;
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);

    // Obtener rank (id) del proceso
    int world_rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);

    int* vector = randGen(); // Generar numeros aleatorios
    
    // Reduccion de suma
    int suma;
    MPI_Reduce(&vector, &suma, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);

    // Reduccion de producto
    int producto;
    MPI_Reduce(&vector, &producto, 1, MPI_INT, MPI_PROD, 0, MPI_COMM_WORLD);

    // Reduccion de Maximo
    int maximo;
    MPI_Reduce(&vector, &maximo, 1, MPI_INT, MPI_MAX, 0, MPI_COMM_WORLD);

    if (world_rank == 0) {
        printf("suma: %d\n", suma);
        printf("Producto: %d\n", producto);
        printf("Maximo: %d\n", maximo);
    }

    MPI_Finalize(); // Finalizar el ambiente
}
