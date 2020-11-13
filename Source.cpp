#include <stdio.h>
#include <conio.h>
#include <Windows.h>
#include <stdlib.h>
#include <queue>
#include <iostream>
using namespace std;
int BFS(int**A, int*M, int i, int N) {
	queue <int> Q;
	int j;
		Q.push(i);
		M[i] = 1;
		while (Q.empty() != true) {
			i = Q.front();
			Q.pop();
			printf("%d ", i + 1);
			for (j = 0; j < N; j++) {
				if ((A[i][j] == 1) && (M[j] != 1)) {
					Q.push(j);
					M[j] = 1;
				}
			}
		}
	return 0;
}

int main(void)
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	int N, i, j;
	printf("Ведите размер матрицы \n");
	scanf_s("%d", &N);
	srand(11);
	int *M = (int*)malloc(N * sizeof(int));
	int **A = (int **)malloc(N * sizeof(int *));
	for (int i = 0; i < N; i++) {
		A[i] = (int *)malloc(N * sizeof(int));
	}
	for (i = 0; i < N; i++) {
		for (j = 0; j < N; j++) {
			A[i][j] = rand() % 2;
			A[j][i] = A[i][j];
			if (i == j) {
				A[i][j] = 0;
			}
		}
	}
	for (i = 0; i < N; i++) {
		for (j = 0; j < N; j++) {
			printf("%d  ", A[i][j]);
		}
		printf("\n");
	}

	printf("\nОбход в ширину:\n");
	for (i = 0; i < N; i++) {
		if (M[i] != 1) {
			BFS(A, M, i, N);
			printf("\n");
		}
	}

	free(A);
	free(M);
	_getch();
}