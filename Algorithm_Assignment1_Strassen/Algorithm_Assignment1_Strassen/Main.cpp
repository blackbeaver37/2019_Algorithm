#include <stdio.h>
#include <stdlib.h>
#include <math.h>

const int N = 4;													// 이번 알고리즘에서는 4X4 행렬을 입력값으로 사용 할 것이므로 N = 4 정의

void Strassen(int, int*, int*, int*);
void MatrixRePlace(int, int*);
void MatrixSum(int, int*, int*, int*);
void MatrixDif(int, int*, int*, int*);

void main() {
	int* mA = (int*)malloc(N * N * sizeof(int*));					// 첫번째 행렬을 받을 16개의 공간 (4X4행렬이므로 16개의 int형 공간 사용)
	int* mB = (int*)malloc(N * N * sizeof(int*));					// 두번째 행렬을 받을 16개의 공간
	int* mC = (int*)malloc(N * N * sizeof(int*));					// 결과 행렬을 받을 16개의 공간

	printf("첫번째 %d X %d 행렬의 값을 입력 하시오.\n", N, N);		// 포인터의 접근을 쉽게 하기위해 4X4행렬을 한줄로 받음
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			printf("A%d%d = ", i + 1, j + 1);
			scanf("%d", mA + (i*N) + j);
		}
	}
	printf("\n");

	printf("입력된 첫번째 행렬 : \n");
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			printf("%d ", *(mA + (i*N) + j));
		}
		printf("\n");
	}
	printf("\n");

	printf("두번째 %d X %d 행렬의 값을 입력 하시오.\n", N, N);
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			printf("B%d%d = ", i + 1, j + 1);
			scanf("%d", mB + (i*N) + j);
		}
	}
	printf("\n");

	printf("입력된 두번째 행렬 : \n");
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			printf("%d ", *(mB + (i*N) + j));
		}
		printf("\n");
	}
	printf("\n");


	Strassen(N, mA, mB, mC);

	printf("슈트라센 알고리즘을 이용하여 구한 두 행렬의 곱셈 값 : \n");
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			printf("%d ", *(mC + (i*N) + j));
		}
		printf("\n");
	}
	free(mA);
	free(mB);
	free(mC);
	while (1);
}

void Strassen(int n, int* A, int* B, int* C) {
	if (n <= 1) {
		*C = (*A) * (*B);
	}
	else {
		int* TempA = (int*)malloc(n * sizeof(int*));
		int* TempB = (int*)malloc(n * sizeof(int*));
		int* M[7];
		for (int i = 0; i < 7; i++) {
			M[i] = (int*)malloc(n * sizeof(int*));
		}

		MatrixRePlace(n, A);
		MatrixRePlace(n, B);

		MatrixSum(n / 2, A, A + 3 * (int)pow((n / 2), 2), TempA);
		MatrixSum(n / 2, B, B + 3 * (int)pow((n / 2), 2), TempB);
		Strassen(n / 2, TempA, TempB, M[0]);

		MatrixSum(n / 2, A + 2 * (int)pow((n / 2), 2), A + 3 * (int)pow((n / 2), 2), TempA);
		Strassen(n / 2, TempA, B, M[1]);

		MatrixDif(n / 2, B + 1 * (int)pow((n / 2), 2), B + 3 * (int)pow((n / 2), 2), TempB);
		Strassen(n / 2, A, TempB, M[2]);

		MatrixDif(n / 2, B + 2 * (int)pow((n / 2), 2), B, TempB);
		Strassen(n / 2, A + 3 * (int)pow((n / 2), 2), TempB, M[3]);

		MatrixSum(n / 2, A, A + 1 * (int)pow((n / 2), 2), TempA);
		Strassen(n / 2, TempA, B + 3 * (int)pow((n / 2), 2), M[4]);

		MatrixDif(n / 2, A + 2 * (int)pow((n / 2), 2), A, TempA);
		MatrixSum(n / 2, B, B + 1 * (int)pow((n / 2), 2), TempB);
		Strassen(n / 2, TempA, TempB, M[5]);

		MatrixDif(n / 2, A + 1 * (int)pow((n / 2), 2), A + 3 * (int)pow((n / 2), 2), TempA);
		MatrixSum(n / 2, B + 2 * (int)pow((n / 2), 2), B + 3 * (int)pow((n / 2), 2), TempB);
		Strassen(n / 2, TempA, TempB, M[6]);

		free(TempA);
		free(TempB);
		
		int* TempC1 = (int*)malloc(n * sizeof(int*));
		int* TempC2 = (int*)malloc(n * sizeof(int*));

		MatrixSum(n / 2, M[0], M[3], TempC1);
		MatrixDif(n / 2, TempC1, M[4], TempC2);
		MatrixSum(n / 2, TempC2, M[6], C);

		MatrixSum(n / 2, M[2], M[4], C + 1 * (int)pow((n / 2), 2));

		MatrixSum(n / 2, M[1], M[3], C + 2 * (int)pow((n / 2), 2));

		MatrixSum(n / 2, M[0], M[2], TempC1);
		MatrixDif(n / 2, TempC1, M[1], TempC2);
		MatrixSum(n / 2, TempC2, M[5], C + 3 * (int)pow((n / 2), 2));

		free(TempC1);
		free(TempC2);

		MatrixRePlace(n, C);
	}
}

void MatrixRePlace(int n, int* M) {
	int temp;
	if ( n > 2 ) {
		for (int i = 0; i < n / 2; i++) {
			for (int j = 0; j < n / 2; j++) {
				temp = *(M + 2 + j + 2 * n*i);
				*(M + 2 + j + 2 * n*i) = *(M + 4 + j + 2 * n*i);
				*(M + 4 + j + 2 * n*i) = temp;
			}
		}
	}
}

void MatrixSum(int n, int* A, int* B, int* C) {
	for (int i = 0; i < n*n; i++) {
		*(C + i) = *(A + i) + *(B + i);
	}
}

void MatrixDif(int n, int* A, int* B, int* C) {
	for (int i = 0; i < n*n; i++) {
		*(C + i) = *(A + i) - *(B + i);
	}
}