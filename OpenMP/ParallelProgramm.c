#include "omp.h"
#include <stdio.h>            // ���������� ������������ ���� stdio.h
#include <tchar.h>
#include <stdlib.h>   // ��� ����������� ������� malloc

#define N 500

void printMatrix(int matrix[N][N]) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

int A[N][N] = { 0 };
int B[N][N] = { 0 };
int C[N][N] = { 0 };

int main()
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

    char choice;
    do {
        double start_time = 0, end_time = 0;
        int i, j, k, number;
       
        printf("\nSet_num_threads: ");
        scanf_s("%d", &number);
        omp_set_num_threads(number, "\n");

        start_time = omp_get_wtime();

        //fillMatrixRandom(A);
        #pragma omp parallel for private (i,j) shared (A)
        for (i = 0; i < N; i++) {
            for (j = 0; j < N; j++) {
                srand(NULL);
                A[i][j] = rand() % (100 + 1); // ��������� ���������� ����� �� 1 �� 100
            }
        }
        //printMatrix(B);
        #pragma omp parallel for private (i,j) shared (B)
        for (i = 0; i < N; i++) {
            for (j = 0; j < N; j++) {
                srand(NULL);
                B[i][j] = rand() % (100 + 1); // ��������� ���������� ����� �� 1 �� 100
            }
        }

        //firstShiftRowsLeftForMatrixA(A);
        #pragma omp parallel for private(i, j) shared(A)
        for (i = 0; i < N; i++) {
            for (j = 0; j < i; j++) {
                int temp = A[i][0]; // ��������� ������ ������� ������
                for (int k = 0; k < N - 1; k++) {
                    A[i][k] = A[i][k + 1]; // �������� ����� �������� ������ �� ���� ������� ������ ������ ������ 
                }
                A[i][N - 1] = temp; // ���������� ������ ������� ������ � �����
            }
        }
        //firstShiftColumnsUpForMatrixB(B);
        #pragma omp parallel for private(i, j) shared(B)
        for (j = 0; j < N; j++) {
            for (i = 0; i < j; i++) {
                int temp = B[0][j]; // ��������� ������ ������� �������
                for (int k = 0; k < N - 1; k++) {
                    B[k][j] = B[k + 1][j]; // �������� ����� �������� ������� �� ���� ������� ������ ������ �������
                }
                B[N - 1][j] = temp; // ���������� ������ ������� ������� ����
            }
        }
        //matrixMultiply(A, B, C);
        #pragma omp parallel for private(i, j) shared(A, B)
        for (i = 0; i < N; i++) {
            for (j = 0; j < N; j++) {
                C[i][j] += A[i][j] * B[i][j]; // �������� ��������������� �������� ������
            }
        }

        for (int i = 0; i < N - 1; i++) {

            //secondShiftRowsLeftForMatrixA(A);
            #pragma omp parallel for private(i, j) shared(A)
            for (i = 0; i < N; i++) {
                int temp = A[i][0]; // ��������� ������ ������� ������
                for (int j = 0; j < N - 1; j++) {
                    A[i][j] = A[i][j + 1]; // �������� �������� ������ �� ���� ������� �����
                }
                A[i][N - 1] = temp; // ���������� ������ ������� ������ � �����
            }

            //secondShiftColumnsUpForMatrixB(B);
            #pragma omp parallel for private(i, j) shared(B)
            for (j = 0; j < N; j++) {
                int temp = B[0][j]; // ��������� ������ ������� �������
                for (int i = 0; i < N - 1; i++) {
                    B[i][j] = B[i + 1][j]; // �������� �������� ������� �� ���� ������� �����
                }
                B[N - 1][j] = temp; // ���������� ������ ������� ������� � �����
            }

            //matrixMultiply(A, B, C);
            #pragma omp parallel for private(i, j) shared(A, B, C)
            for (i = 0; i < N; i++) {
                for (j = 0; j < N; j++) {
                    C[i][j] += A[i][j] * B[i][j]; // �������� ��������������� �������� ������
                }
            }
        }

        end_time = omp_get_wtime();
        //printMatrix(C);
        printf("Time taken: %f seconds\n\n", end_time - start_time);

        printf("Restart programm? (y/n): ");
        scanf_s(" %c", &choice); // ������ ����� %c ��� ������������� �������� � ��������� �����

    }while (choice == 'y' || choice == 'Y');

    return 0;
}