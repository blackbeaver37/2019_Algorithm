#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <Windows.h>

// �̹� �˰��򿡼��� 4X4 ����� �Է°����� ��� �� ���̹Ƿ� N = 4 ����
const int N = 4;

void Strassen(int, int*, int*, int*);
void MatrixRePlace(int, int*);
void MatrixSum(int, int*, int*, int*);
void MatrixDif(int, int*, int*, int*);

void main() {
	int* ptA = (int*)malloc(N * N * sizeof(int*));					// ù��° ����� ���� 16���� ���� (4X4����̹Ƿ� 16���� int�� ���� ���)
	int* ptB = (int*)malloc(N * N * sizeof(int*));					// �ι�° ����� ���� 16���� ����
	int* ptC = (int*)malloc(N * N * sizeof(int*));					// ��� ����� ���� 16���� ����

	// �������� ������ ���� �ϱ����� 4X4����� ���ٷ� ����
	printf("ù��° %d X %d ����� ���� �Է� �Ͻÿ�.\n", N, N);
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {								// 1���� ���ҵ��� ptA, ptA+1, ptA+2, ptA+3�� �ּҿ� ����
			printf("A%d%d = ", i + 1, j + 1);						// 2���� ���ҵ��� �� ���� ptA+4 ���� ptA+7�� �ּҿ� ����
			scanf("%d", ptA + (i*N) + j);							// ������ ��鵵 ���� ���� ������� ptA+15���� 16���� ���Ҹ� ���ٷ� ����
		}															 
	}																
	printf("\n");

	// �Է¹��� ����� ���
	printf("�Էµ� ù��° ��� : \n");
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			printf("%d ", *(ptA + (i*N) + j));
		}
		printf("\n");												// ���Ҹ� 4�� ��� �Ŀ��� ���� �ٲ�� ������ ����
	}
	printf("\n");

	// �ι�° ��� �Է�
	printf("�ι�° %d X %d ����� ���� �Է� �Ͻÿ�.\n", N, N);
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			printf("B%d%d = ", i + 1, j + 1);
			scanf("%d", ptB + (i*N) + j);
		}
	}
	printf("\n");

	// �ι�° ��� ���
	printf("�Էµ� �ι�° ��� : \n");
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			printf("%d ", *(ptB + (i*N) + j));
		}
		printf("\n");
	}
	printf("\n");

	// ����� ���� N, ����� �� ����� �ּҸ� ������ �ִ� mA, mB, �������� ���� ������ �ּҸ� ������ �ִ� mC�� ���� ������ ���
	Strassen(N, ptA, ptB, ptC);

	// ��Ʈ�� �˰����� �̿��Ͽ� ���� ��� �� ���
	printf("��Ʈ�� �˰����� �̿��Ͽ� ���� �� ����� ���� �� : \n");
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			printf("%d ", *(ptC + (i*N) + j));
		}
		printf("\n");
	}
	printf("\n");

	// ���α׷� ���� �� ����ߴ� ���� ����
	free(ptA);
	free(ptB);
	free(ptC);
	
	system("pause");
}

// ��Ʈ�� �˰��� �Լ�
void Strassen(int n, int* A, int* B, int* C) {
	
	// n = 1 �϶��� �ܼ� �� ���
	if (n <= 1) {
		*C = *A * *B;
	}

	// ���� ó��
	else {
		int* M[7];																				// M�� M1���� M7������ �ּҰ��� ������ ������ �迭
		for (int i = 0; i < 7; i++) {															// TempA�� M����� ���ϴ� �������� A11+A22�� ���� A�� ���ҵ� ��ĵ��� �� �Ǵ� �� ����� �ӽ������� �����ϴ� �ּҸ� ���� ������
			M[i] = (int*)malloc((int)pow((n/2), 2) * sizeof(int*));								// TempB�� ���� TempA �����Ϳ� ���� ����
		}																						// �޸� �Ҵ��� n = 4�϶��� ���� �Լ��� 2X2, n = 1�϶��� ���� �Լ��� 1X1�̹Ƿ� n/2�� ���� ��ŭ�� ������ �ʿ�
		int* TempA = (int*)malloc((int)pow((n/2), 2) * sizeof(int*));							
		int* TempB = (int*)malloc((int)pow((n/2), 2) * sizeof(int*));
		
		// n = 4�� ��� 4���� ���� �Լ� A11�� A, A+1, A+4, A+5�� �ּҿ� ����
		// �� �� ������ ������ ���ϰ� �ϱ����ؼ� A11�� ���� ������ A���� A+3�� �ּҿ� ����, A12�� ���� ������ A+4���� A+7�ּҿ� �����ϴ� ������ ���ҵ��� ��ġ�� ����
		MatrixRePlace(n, A);
		MatrixRePlace(n, B);

		// M1 ���
		// A11�� A�ּҿ��� ����, A12�� n=4�� ��쿡�� A+4�ּҿ��� ����, n=1�� ��쿡�� A+1���� �����ϹǷ� �Ʒ��� ���� ���
		MatrixSum(n/2, A, A + 3*(int)pow((n / 2), 2), TempA);		// A11 + A22
		MatrixSum(n/2, B, B + 3*(int)pow((n / 2), 2), TempB);		// B11 + B22
		Strassen(n/2, TempA, TempB, M[0]);

		// M2 ���
		MatrixSum(n/2, A + 2*(int)pow((n/2), 2), A + 3*(int)pow((n/2), 2), TempA);
		Strassen(n/2, TempA, B, M[1]);

		// M3 ���
		MatrixDif(n/2, B + 1*(int)pow((n/2), 2), B + 3*(int)pow((n/2), 2), TempB);
		Strassen(n/2, A, TempB, M[2]);

		// M4 ���
		MatrixDif(n/2, B + 2*(int)pow((n/2), 2), B, TempB);
		Strassen(n/2, A + 3*(int)pow((n/2), 2), TempB, M[3]);

		// M5 ���
		MatrixSum(n/2, A, A + 1*(int)pow((n/2), 2), TempA);
		Strassen(n/2, TempA, B + 3*(int)pow((n/2), 2), M[4]);

		// M6 ���
		MatrixDif(n/2, A + 2*(int)pow((n/2), 2), A, TempA);
		MatrixSum(n/2, B, B + 1*(int)pow((n/2), 2), TempB);
		Strassen(n/2, TempA, TempB, M[5]);

		// M7 ���
		MatrixDif(n/2, A + 1*(int)pow((n/2), 2), A + 3*(int)pow((n/2), 2), TempA);
		MatrixSum(n/2, B + 2*(int)pow((n/2), 2), B + 3*(int)pow((n/2), 2), TempB);
		Strassen(n/2, TempA, TempB, M[6]);

		// TempA�� TempB �� �����ʹ� ����� �������Ƿ� ���� ���� 
		free(TempA);
		free(TempB);

		// M����� �̿��Ͽ� C���(������) ����ϴ� �������� M��ĵ��� �� �Ǵ� ���� �ӽ� �����ϱ����� ���� �Ҵ�
		int* TempC1 = (int*)malloc((int)pow((n/2), 2) * sizeof(int*));
		int* TempC2 = (int*)malloc((int)pow((n/2), 2) * sizeof(int*));

		// C11 ���
		MatrixSum(n/2, M[0], M[3], TempC1);
		MatrixDif(n/2, TempC1, M[4], TempC2);
		MatrixSum(n/2, TempC2, M[6], C);

		// C12 ���
		MatrixSum(n/2, M[2], M[4], C + 1*(int)pow((n/2), 2));

		// C21 ���
		MatrixSum(n/2, M[1], M[3], C + 2*(int)pow((n/2), 2));

		// C22 ���
		MatrixSum(n/2, M[0], M[2], TempC1);
		MatrixDif(n/2, TempC1, M[1], TempC2);
		MatrixSum(n/2, TempC2, M[5], C + 3*(int)pow((n/2), 2));

		// M������ �迭�� TempC1, TempC2 �����ʹ� ����� �������Ƿ� ���� ����
		for (int i = 0; i < 7; i++) {
			free(M[i]);
		}
		free(TempC1);
		free(TempC2);

		// C �����Ϳ� ����� ��� ��� ���� ������ ���ϰ� �ϱ� ���� ���ҵ��� ��ġ�� �ٲ� ä�� ����Ǿ����Ƿ� �ٽ� ���ҵ��� ��ġ ����
		MatrixRePlace(n, C);
	}
}

// �������� ������ ���� �ϱ����� n = 4�� ��쿡 ���ҵ��� ��ġ ��ȯ, n = 2�� ��쿡�� ��ġ�� ��ȯ �� �ʿ䰡 ����
void MatrixRePlace(int n, int* M) {
	int temp;
	if (n > 2) {
		for (int i = 0; i < n/2; i++) {
			for (int j = 0; j < n/2; j++) {
				temp = *(M + n/2 + j + 2*n*i);
				*(M + n/2 + j + 2*n*i) = *(M + n + j + 2*n*i);
				*(M + n + j + 2*n*i) = temp;
			}
		}
	}
}

// �����͸� �̿��Ͽ� A�� B�� ����Ű�� �� ����� ���� C�� �ּҿ� �ִ� �Լ�
void MatrixSum(int n, int* A, int* B, int* C) {
	for (int i = 0; i < n*n; i++) {
		*(C + i) = *(A + i) + *(B + i);
	}
}

// �����͸� �̿��Ͽ� A�� B�� ����Ű�� �� ����� ���� C�� �ּҿ� �ִ� �Լ�
void MatrixDif(int n, int* A, int* B, int* C) {
	for (int i = 0; i < n*n; i++) {
		*(C + i) = *(A + i) - *(B + i);
	}
}