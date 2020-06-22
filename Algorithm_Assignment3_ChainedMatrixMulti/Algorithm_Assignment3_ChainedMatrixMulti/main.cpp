#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include <math.h>

int minmult(int, const int*, int*);				// �ּ� ���� Ƚ���� ��ȯ���ִ� �˰��� �Լ�
void order(int, int, int, const int*);			// ������ ������ ������ִ� �Լ�
void printMatrix(const int*, int);				// �ּҰ����� ����� ����ϴ� �Լ�

void main() {
	
	// ����� �� �Է�
	int n;
	printf("���Ϸ��� ��� �������� ����� ���� �Է��Ͻÿ� : ");
	scanf("%d", &n);

	// ���� �Ҵ�
	int* d = (int*)malloc((n+1) * sizeof(int));		// 1������� �� �� + ��� ����� �� �� �̹Ƿ� n+1�� ����
	int* P = (int*)malloc(n*n * sizeof(int));		// n*n�� ����

	// P = 0 �ʱ�ȭ
	for (int i = 0; i < n*n; i++) {
		*(P+i) = 0;
	}

	// d�� �� �Է�
	for (int i = 0; i < n; i++) {
		if (i == 0) {
			printf("\n%d�� ����� ���� ������ �Է��Ͻÿ� : ", i+1);
			scanf("%d", d+i);
		}
		printf("\n%d�� ����� ���� ������ �Է��Ͻÿ� : ", i+1);
		scanf("%d", d+i+1);
	}

	// minmult�Լ� ����
	printf("\n�� ��� ���� �� ���Ƚ���� �ּڰ��� : %d�� �̴�.\n", minmult(n, d, P));

	// �˰��� ���� ������ P��� ���
	printf("\nP = \n");
	printMatrix(P, n);

	// order�Լ� �����Ͽ� �������� ���
	printf("\n ����� ���ϴ� ������ ���� : ");
	order(1, n, n, P);
	printf("\n");

	// ���� ����
	free(d);
	free(P);

	system("pause");
}

// �ּ� ���� ���� ��ȯ�ϴ� �˰��� �Լ�
int minmult(int n, const int* d, int* P) {
	int* M = (int*)malloc(n*n*sizeof(int));		// M��� n*n���� ���� �Ҵ�

	// �밢�� �κ��� 0���� �ʱ�ȭ
	for (int i = 0; i < n; i++)
		*(M + n*i + i) = 0;

	// �밢�� ���� �� �κ� ���� ���ϸ� �ּڰ� ����
	for (int diag = 1; diag <= n-1; diag++) {
		int j;
		for (int i = 0; i < n - diag; i++) {
			j = i + diag;
			*(M + n*i + j) = INT_MAX;			// ���� �񱳵��� ���� �κе��� ū ������ �ʱ�ȭ �ص�
			int temp;
			for (int k = i; k <= j - 1; k++) {
				temp = *(M + n*i + k) + *(M + n*(k+1) + j) + *(d + i) * *(d + k+1) * *(d + j+1);
				if (temp < *(M + n*i + j)) {
					*(M + n*i + j) = temp;		// ���� ���� ���� �� �۴ٸ� M��Ŀ� ���� 
					*(P + n*i + j) = k+1;		// �׸��� P��Ŀ� ��ġ ����
				}
			}
		}
	}
	int ret = *(M + n - 1);
	free(M);		// ���� ����
	return ret;		// M[1][n] ������ ��ȯ
}

// ������ ������ ������ִ� �Լ�
void order(int i, int j, int n, const int* P) {
	int k;
	if (i == j)
		printf("A%d", i);					// �� �ε����� �������� ���̻� ���� ���� �����Ƿ� ���
	// ����Լ� �� P��� �̿��Ͽ� i == j �� �ɶ����� ������ �����κ����� �����鼭 ���� ���
	else {
		k = *(P + n*(i - 1) + (j - 1));		
		printf("(");						
		order(i, k, n, P);
		order(k + 1, j, n, P);
		printf(")");
	}
}

// �ּҰ����� ����� ����ϴ� �Լ�
void printMatrix(const int* M, int n) {
	for (int i = 0; i<n; i++) {
		for (int j = 0; j<n; j++) {
			printf("%3d ", *(M + n*i + j));
		}
		printf("\n");
	}
}