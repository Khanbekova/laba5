#include <stdio.h>
#include <conio.h>
#include <Windows.h>
#include <stdlib.h>
#include <queue>
#include <iostream>
#include <time.h>
using namespace std;
typedef int tData;
typedef struct sNode {
	tData value;
	struct sNode *next;
} tNode;
tNode* create_list(int N, int k, int **A, int i)
{
	tNode *p_begin = NULL;
	tNode *p = NULL;
	//заполним односвязный список
	p_begin = (tNode *)malloc(sizeof(tNode));
	if (p_begin == NULL) {
		printf("не удалось выделить память");
		return NULL;

	}
	p = p_begin;
	p->next = NULL;
	p->value = i + 1;
	for (int x = 1; x < N; x++) {
		if (A[i][x]) {
			p->next = (tNode *)malloc(sizeof(tNode));
			if (p->next == NULL) {
				printf("не удалось выделить память Х = %d I = %d", x, i);
				return NULL;
			}
			p = p->next;
			//заполнить _новую_ структуру данных
			p->next = NULL;
			p->value = x + 1;
		}
	}
	return p_begin;
}

void print_list(tNode *p_begin)
{
	tNode *p = p_begin;
	while (p != NULL) {
		printf("-> %d ", p->value);
		p = p->next;
	}
}
tNode **p_begin;
void BFSSPISOK(int i, int *M) {
	queue <int> Q;
	Q.push(i);
	
	while (Q.empty() != true) {
		
		i = Q.front();
		tNode *p_b = p_begin[i];
		Q.pop();
		if (M[i] != 1) {
			M[i] = 1;
			//printf("%d ", i + 1);
		}
		while (p_b->next != NULL) {
			i = p_b->next->value - 1;
			p_b = p_b->next;
			if (M[i] != 1) {
				Q.push(i);
				M[i] = 1;
			//printf("%d ", i + 1);
			}
		}
	}
}

int BFS(int**A, int*M, int i, int N) {
	queue <int> Q;
	int j;
	Q.push(i);
	M[i] = 1;
	while (Q.empty() != true) {
		i = Q.front();
		Q.pop();
		//printf("%d ", i + 1);
		for (j = 0; j < N; j++) {
			if ((A[i][j] == 1) && (M[j] != 1)) {
				Q.push(j);
				M[j] = 1;
			}
		}
	}
	return 0;
}

int BFSMASS(int**A, int*M, int*MASS,  int i, int N) {
	queue <int> Q;
	int j, first = 0, last = 0;
	MASS[last] = i;
	last++;
	M[i] = 1;
	while (last!=first) {
		i = MASS[first];
		first++;
		//printf("%d ", i + 1);
		for (j = 0; j < N; j++) {
			if ((A[i][j] == 1) && (M[j] != 1)) {
				MASS[last] = j;
				last++;
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
	clock_t start, end;
	int *M = (int*)malloc(N * sizeof(int));
	int *MASS = (int*)malloc(N * sizeof(int));
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
	/*for (i = 0; i < N; i++) {
		for (j = 0; j < N; j++) {
			printf("%d  ", A[i][j]);
		}
		printf("\n");
	}*/

	printf("\nОбход в ширину\n");
	start = clock();
	for (i = 0; i < N; i++) {
		if (M[i] != 1) {
			BFS(A, M, i, N);
			//printf("\n");
		}
	}
	end = clock();
	printf("Время: %lf   \n", (float)(end - start) / CLOCKS_PER_SEC);
	//printf("\n\n Список :\n");

	p_begin = (tNode**)malloc(N * sizeof(tNode*));

	for (i = 0; i < N; i++) {
		int k = 0;
		for (j = 0; j < N; j++) {
			if (A[i][j] == 1)
				k++;

		}
		p_begin[i] = create_list(N, k, A, i);
		if (p_begin[i] == NULL) {
			_getch();
			exit(-1);
		}
		//print_list(p_begin[i]);
		//printf("\n");
	}
	for (i = 0; i < N; i++) {
		M[i] = 0;
	}
	printf("\nОбход в ширину списками\n");
	start = clock();
	for (i = 0; i < N; i++) {
		if (M[i] != 1) {
			BFSSPISOK(i, M);
			//printf("\n");
		}
	}
	end = clock();
	printf("Время: %lf \n", (float)(end - start) / CLOCKS_PER_SEC);
	for (i = 0; i < N; i++) {
		M[i] = 0;
	}
	printf("\nОбход в ширину ручной очередью\n");
	start = clock();
	for (i = 0; i < N; i++) {
		if (M[i] != 1) {
			BFSMASS(A, M, MASS, i, N);
			//printf("\n");
		}
	}
	end = clock();
	printf("Время: %lf \n", (float)(end - start) / CLOCKS_PER_SEC);
	free(A);
	free(M);
	free(p_begin);
	_getch();
}