/*
#include <stdio.h>

void strassen(int, int*, int*, int*);

void main() {
	int MatrixA[4], MatrixB[4];					// �Է� ��� A, B
	int MatrixC[4];									// ��� ��� C
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






void strassen(int n, int* A, int* B, int* C) {		// ��� ũ�⸦ ��Ÿ���� n, �Է°� A ��B, ����� C
	if (n = 1) {
		C[0] = A[0] * B[0];								// ũ�Ⱑ 1�� ����̸� �Է°��� ���� ������� ��ȯ
		printf("\naaaaa%d", *A);
		printf("\naaaaa%d", *A + *(A+1));
	
	}
//	else if (n = 2) {
		int M1, M2, M3, M4, M5, M6, M7;
//		M1 = (A[0][0] + A[1][1]);
//	}
}
*/