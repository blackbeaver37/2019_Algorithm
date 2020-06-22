/*
#include <stdio.h>

void strassen(int, int*, int*, int*);

void main() {
	int MatrixA[4], MatrixB[4];					// 입력 행렬 A, B
	int MatrixC[4];									// 결과 행렬 C
	MatrixA[0] = 2;
	MatrixA[1] = 8;
	MatrixB[0] = 5;
	MatrixC[0] = 4;
	printf("%d, %d", MatrixA[0], MatrixB[0]);
	//MatrixC[0] = MatrixA[0] * MatrixB[0];
	printf("\n%d", MatrixC[0]);
	strassen(4, MatrixA, MatrixB, MatrixC);
	printf("\naaaaa%d", MatrixA);
	printf("\naaaaa%d", &MatrixA[0]);
	printf("\naaaaa%d", &MatrixA[1]);
	printf("\n%d * %d = %d", *MatrixA, *MatrixB, *MatrixC);
	getchar();
}






void strassen(int n, int* A, int* B, int* C) {		// 행렬 크기를 나타내는 n, 입력값 A 와B, 결과값 C
	if (n = 1) {
		C[0] = A[0] * B[0];								// 크기가 1인 행렬이면 입력값의 곱을 결과값에 반환
		printf("\naaaaa%d", *A);
		printf("\naaaaa%d", *A + *(A+1));
	
	}
//	else if (n = 2) {
		int M1, M2, M3, M4, M5, M6, M7;
//		M1 = (A[0][0] + A[1][1]);
//	}
}
*/