/*
#include <stdio.h>

void strassen(int, int*, int*, int*);
void MatrixRePlalce(int, int*);
void MatrixSum(int*, int*, int*);
void MatrixDif(int*, int*, int*);

void main() {
	int MatrixA[4][4], MatrixB[4][4];					// 입력 행렬 A, B
	int MatrixC[4][4];									// 결과 행렬 C

	MatrixA[0][0] = 1;
	MatrixA[0][1] = 2;
	MatrixA[0][2] = 3;
	MatrixA[0][3] = 4;
	MatrixA[1][0] = 5;
	MatrixA[1][1] = 6;
	MatrixA[1][2] = 7;
	MatrixA[1][3] = 8;
	MatrixA[2][0] = 9;
	MatrixA[2][1] = 1;
	MatrixA[2][2] = 2;
	MatrixA[2][3] = 3;
	MatrixA[3][0] = 4;
	MatrixA[3][1] = 5;
	MatrixA[3][2] = 6;
	MatrixA[3][3] = 7;

	MatrixB[0][0] = 8;
	MatrixB[0][1] = 9;
	MatrixB[0][2] = 1;
	MatrixB[0][3] = 2;
	MatrixB[1][0] = 3;
	MatrixB[1][1] = 4;
	MatrixB[1][2] = 5;
	MatrixB[1][3] = 6;
	MatrixB[2][0] = 7;
	MatrixB[2][1] = 8;
	MatrixB[2][2] = 9;
	MatrixB[2][3] = 1;
	MatrixB[3][0] = 2;
	MatrixB[3][1] = 3;
	MatrixB[3][2] = 4;
	MatrixB[3][3] = 5;

	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			printf("%d ", MatrixA[i][j]);
		}
		printf("\n");
	}

	printf("\n");

	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			printf("%d ", MatrixB[i][j]);
		}
		printf("\n");
	}

	printf("\n");

	strassen(4, &MatrixA[0][0], &MatrixB[0][0], &MatrixC[0][0]);

	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			printf("%d ", MatrixC[i][j]);
		}
		printf("\n");
	}
	int M1[2][2], M2[2][2],
		getchar();

	void strassen(int n, int* A, int* B, int* C) {			// 행렬 크기를 나타내는 n, 입력값 A 와B, 결과값 C
		if (n <= 1) {
			*C = *A * *B;									// 크기가 1인 행렬이면 입력값의 곱을 결과값에 반환
		}
		else if (n == 2) {
			int M[7];
			int temp1, temp2;

			temp1 = *A + *(A + 3);
			temp2 = *B + *(B + 3);
			strassen(n / 2, &temp1, &temp2, M);

			temp1 = *(A + 2) + *(A + 3);
			strassen(n / 2, &temp1, B, M + 1);

			temp1 = *(B + 1) - *(B + 3);
			strassen(n / 2, A, &temp1, M + 2);

			temp1 = *(B + 2) - *B;
			strassen(n / 2, A + 3, &temp1, M + 3);

			temp1 = *A + *(A + 1);
			strassen(n / 2, &temp1, B + 3, M + 4);

			temp1 = *(A + 2) - *A;
			temp2 = *B + *(B + 1);
			strassen(n / 2, &temp1, &temp2, M + 5);

			temp1 = *(A + 1) - *(A + 3);
			temp2 = *(B + 2) + *(B + 3);
			strassen(n / 2, &temp1, &temp2, M + 6);

			C[0] = M[0] + M[3] - M[4] + M[6];
			C[1] = M[2] + M[4];
			C[2] = M[1] + M[3];
			C[3] = M[0] + M[2] - M[1] + M[5];
		}
		else {
			MatrixRePlalce(n, A);
			MatrixRePlalce(n, B);

			int tempM1[4];
			int tempM2[4];
			int M[7][4];

			MatrixSum(A, A + 3, tempM1);
			MatrixSum(B, B + 3, tempM2);
			strassen(2, tempM1, tempM2, M[0]);

			MatrixSum(A + 2, A + 3, tempM1);
			strassen(2, tempM1, B, M[1]);

			MatrixDif(B + 1, B + 3, tempM1);
			strassen(2, A, tempM1, M[2]);

			MatrixDif(B + 2, B, tempM1);
			strassen(2, A + 3, tempM1, M[3]);

			MatrixSum(A, A + 1, tempM1);
			strassen(2, tempM1, B + 3, M[4]);

			MatrixDif(A + 2, A, tempM1);
			MatrixSum(B, B + 1, tempM2);
			strassen(2, tempM1, tempM2, M[5]);

			MatrixDif(A + 1, A + 3, tempM1);
			MatrixSum(B + 2, B + 3, tempM2);
			strassen(2, tempM1, tempM2, M[6]);


			MatrixSum(M[0], M[3], tempM1);
			MatrixDif(tempM1, M[4], tempM2);
			MatrixSum(tempM2, M[6], C);

			MatrixSum(M[2], M[4], C + n);

			MatrixSum(M[1], M[3], C + 2 * n);

			MatrixSum(M[0], M[2], tempM1);
			MatrixDif(tempM1, M[1], tempM2);
			MatrixSum(tempM2, M[5], C + 3 * n);

			MatrixRePlalce(4, C);
		}
	}

	void MatrixRePlalce(int n, int* M) {
		int temp;
		for (int i = 0; i < n / 2; i++) {
			for (int j = 0; j < n / 2; j++) {
				temp = *(M + 2 + j + 2 * n*i);
				*(M + 2 + j + 2 * n*i) = *(M + 4 + j + 2 * n*i);
				*(M + 4 + j + 2 * n*i) = temp;
			}
		}
	}

	void MatrixSum(int* A, int* B, int* C) {
		for (int i = 0; i < 4; i++) {
			*(C + i) = *(A + i) + *(B + i);
		}
	}

	void MatrixDif(int* A, int* B, int* C) {
		for (int i = 0; i < 4; i++) {
			*(C + i) = *(A + i) - *(B + i);
		}
	}
	*/