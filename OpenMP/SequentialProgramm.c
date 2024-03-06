#include "omp.h"
#include <stdio.h>            // подключаем заголовочный файл stdio.h
#include <tchar.h>

#define N 250

void fillMatrixRandom(int matrix[N][N]) {
    srand(NULL);
    for (int i = 0; i < N; i++) {
        //srand(13 + i);
        for (int j = 0; j < N; j++) {
            matrix[i][j] = rand() % (100 + 1); // Генерация случайного числа от 1 до 100
        }
    }
}

void printMatrix(int matrix[N][N]) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

void firstShiftRowsLeftForMatrixA(int matrix[N][N]) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < i; j++) {
            int temp = matrix[i][0]; // Сохраняем первый элемент строки
            for (int k = 0; k < N - 1; k++) {
                matrix[i][k] = matrix[i][k + 1]; // Сдвигаем элементы строки на одну позицию влево
            }
            matrix[i][N - 1] = temp; // Перемещаем первый элемент строки в конец
        }
    }
}

void secondShiftRowsLeftForMatrixA(int matrix[N][N]) {
    for (int i = 0; i < N; i++) {
        int temp = matrix[i][0]; // Сохраняем первый элемент строки
        for (int j = 0; j < N - 1; j++) {
            matrix[i][j] = matrix[i][j + 1]; // Сдвигаем элементы строки на одну позицию влево
        }
        matrix[i][N - 1] = temp; // Перемещаем первый элемент строки в конец
    }
}

void firstShiftColumnsUpForMatrixB(int matrix[N][N]) {
    for (int j = 0; j < N; j++) {
        for (int i = 0; i < j; i++) {
            int temp = matrix[0][j]; // Сохраняем первый элемент столбца
            for (int k = 0; k < N - 1; k++) {
                matrix[k][j] = matrix[k + 1][j]; // Сдвигаем элементы столбца на одну позицию вверх
            }
            matrix[N - 1][j] = temp; // Перемещаем первый элемент столбца вниз
        }
    }
}

void secondShiftColumnsUpForMatrixB(int matrix[N][N]) {
    for (int j = 0; j < N; j++) {
        int temp = matrix[0][j]; // Сохраняем первый элемент столбца
        for (int i = 0; i < N - 1; i++) {
            matrix[i][j] = matrix[i + 1][j]; // Сдвигаем элементы столбца на одну позицию вверх
        }
        matrix[N - 1][j] = temp; // Перемещаем первый элемент столбца в конец
    }
}

void matrixMultiply(int matrixA[N][N], int matrixB[N][N], int matrixC[N][N]) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            matrixC[i][j] += matrixA[i][j] * matrixB[i][j]; // Умножаем соответствующие элементы матриц
        }
    }
}

int A[N][N] = { 0 };
int B[N][N] = { 0 };
int C[N][N] = { 0 };

int _tmain(int argc, _TCHAR* argv[])
{   
    /*
    int A[N][N] = {
        {2, 3, 4, 5},
        {9, 8, 7, 6},
        {5, 4, 2, 3},
        {8, 7, 3, 4}
    };
    int B[N][N] = {
        {3, 5, 7, 6},
        {2, 7, 6, 3},
        {7, 5, 3, 2},
        {4, 3, 2, 5}
    };
    */

    double start_time, end_time;

    start_time = omp_get_wtime();

    fillMatrixRandom(A);
    fillMatrixRandom(B);

    //printMatrix(A);
    //printMatrix(B);

    firstShiftRowsLeftForMatrixA(A);
    firstShiftColumnsUpForMatrixB(B);
    matrixMultiply(A, B, C);

    for (int i = 0; i < N-1; i++) {
        secondShiftRowsLeftForMatrixA(A);
        secondShiftColumnsUpForMatrixB(B);
        matrixMultiply(A, B, C);
    }

    end_time = omp_get_wtime();
    //printMatrix(C);
    printf("Time taken: %f seconds\n", end_time - start_time);
    
    return 0;                       
}     