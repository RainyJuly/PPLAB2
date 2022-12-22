#include <stdio.h>
#include <ctime>
#include <time.h>
#include <stdlib.h>
#define n 50
#pragma warning(disable : 4996)
int main() {
	FILE* M1;
	int A[n][n], B[n][n], C[n][n];
	srand(time(NULL));

	M1 = fopen("M1.txt", "w");
	for (int i = 0; i < n; i++) { //заполнение массива рандомом и запись в файл
		for (int j = 0; j < n; j++) {
			A[i][j] = rand() % 51;
			fprintf(M1, "%d ", A[i][j]);
			if (j == (n - 1)) fprintf(M1, "\n");
		}
	}
	fclose(M1);

	FILE* M2;
	M2 = fopen("M2.txt", "w");
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			B[i][j] = rand() % 101;
			fprintf(M2, "%d ", B[i][j]);
			if (j == (n - 1)) fprintf(M2, "\n");
		}
	}
	fclose(M2);

	M1 = fopen("M1.txt", "r+");
	M2 = fopen("M2.txt", "r+");
	FILE* M3;
	M3 = fopen("M3.txt", "w");

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			fscanf(M1, "%d ", &A[i][j]);
		}
	}
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			fscanf(M2, "%d ", &B[i][j]);
		}
	}

	int start = clock();
#pragma omp parallel for shared (M1, M2, M3) private (i,j,k)

	for (int i = 0; i < n; i++) { //умножение матриц
		for (int j = 0; j < n; j++) {
			C[i][j] = 0;
			for (int k = 0; k < n; k++) {
				C[i][j] += A[i][k] * B[k][j];
			}
			fprintf(M3, " %d", C[i][j]);
			if (j == (n - 1)) fprintf(M3, "\n");
		}
	}
	fclose(M1);
	fclose(M2);
	fclose(M3);

	FILE* time;
	int end = clock();
	int _time = (end - start);
	time = fopen("time.txt", "w");
	fprintf(time, "%d ms", _time);
	fclose(time);
}