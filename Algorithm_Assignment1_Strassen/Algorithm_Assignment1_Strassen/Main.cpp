#include <stdio.h>
#include <stdlib.h>
#include <math.h>

const int N = 4;													// �̹� �˰��򿡼��� 4X4 ����� �Է°����� ��� �� ���̹Ƿ� N = 4 ����

void Strassen(int, int*, int*, int*);
void MatrixRePlace(int, int*);
void MatrixSum(int, int*, int*, int*);
void MatrixDif(int, int*, int*, int*);

void main() {
	int* mA = (int*)malloc(N * N * sizeof(int*));					// ù��° ����� ���� 16���� ���� (4X4����̹Ƿ� 16���� int�� ���� ���)
	int* mB = (int*)malloc(N * N * sizeof(int*));					// �ι�° ����� ���� 16���� ����
	int* mC = (int*)malloc(N * N * sizeof(int*));					// ��� ����� ���� 16���� ����

	printf("ù��° %d X %d ����� ���� �Է� �Ͻÿ�.\n", N, N);		// �������� ������ ���� �ϱ����� 4X4����� ���ٷ� ����
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			printf("A%d%d = ", i + 1, j + 1);
			scanf("%d", mA + (i*N) + j);
		}
	}
	printf("\n");

	printf("�Էµ� ù��° ��� : \n");
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			printf("%d ", *(mA + (i*N) + j));
		}
		printf("\n");
	}
	printf("\n");

	printf("�ι�° %d X %d ����� ���� �Է� �Ͻÿ�.\n", N, N);
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			printf("B%d%d = ", i + 1, j + 1);
			scanf("%d", mB + (i*N) + j);
		}
	}
	printf("\n");

	printf("�Էµ� �ι�° ��� : \n");
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			printf("%d ", *(mB + (i*N) + j));
		}
		printf("\n");
	}
	printf("\n");


	Strassen(N, mA, mB, mC);

	printf("��Ʈ�� �˰����� �̿��Ͽ� ���� �� ����� ���� �� : \n");
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