#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>

void floyd2(int, const int*, int*, int*);						// Floyd2 �˰��� �Լ�
void path(int, int, const int*, int);							// ��θ� ����ϴ� �Լ�
void printMatrix(const int*, int);								// �ּҰ��� �̿��Ͽ� ��� ����ϴ� �Լ�

const int INF = 1000000000;										// ��ΰ� ���� ��� ���� ������ ū �� ����

void main() {

	// Vertex�� ���� �޴´�.
	int n;														
	printf("Vertex�� ������ �Է��ϼ��� : ");
	scanf("%d", &n);

	// ���� Vertex�� �� �ǰ��Ͽ� ���� �Ҵ�
	int* W = (int*)malloc(n*n * sizeof(int*));					// W 5x5 ������
	int* D = (int*)malloc(n*n * sizeof(int*));					// D 5x5 �ִܰ���� �������
	int* P = (int*)malloc(n*n * sizeof(int*));					// P 5x5 �ִܰ�����

	// �� Vertex������ ����ġ ���� �Է¹���
	printf("�� ����� ����ġ ���� �Է��Ͻÿ� (��, ��ΰ� ���� ��쿡�� 0 �Է�) : \n");
	for (int i=0; i<n; i++) {
		for (int j=0; j<n; j++) {
			if (i != j) {
				printf("%d-->%d ����� ����ġ : ", i+1, j+1);
				scanf("%d", W + (n*i + j));
				if (*(W + (n*i + j)) == 0)
					*(W + (n*i + j)) = INF;
			}
			else {
				*(W + (n*i + j)) = 0;
				continue;
			}
		}
	}

	// ���� ����ġ ���� �̿��� ������ ���
	printf("\n");
	printf("�Էµ� ��� ��� W = \n");
	printMatrix(W, n);

	// Floyd2�˰��� ����
	floyd2(n, W, D, P);

	// �˰����� ������� �ִܰ�� ���� ������ ��� ���
	printf("\n");
	printf("�ִܰ���� ������� D\n");
	printMatrix(D, n);

	// �ִܰ�� ���� ���� ��θ� �˷��ִ� ��� ��� 
	printf("\n");
	printf("�ִܰ����� P\n");
	printMatrix(P, n);

	// ����� ���� ���� ����
	free(W);
	free(D);

	int iPath;								// ��� Ž���� ���, �ߴ����� ���ϴ� ��

printPath :

	// path�Լ��� �̿��� ��� ���
	int indexA, indexB;
	printf("\n��� Ž�� : ");
	scanf("%d %d", &indexA, &indexB);
	printf("\n��ġ�� ��� : %d", indexA);
	path(indexA - 1, indexB - 1, P, n);
	printf(" -> %d\n", indexB);

	printf("\n��θ� �� ����Ͻðڽ��ϱ�?(yes == 1 / no == 0) : ");
	scanf("%d", &iPath);
	if (iPath)
		goto printPath;					// ��θ� �ѹ��� ��� �Ѵٰ� �Ͽ��ٸ� printPath�� �̵�, �ݺ�
	
	// ����� ���� ���� ����
	free(P);

	system("pause");
}

// Floyd �˰��� �Լ�
void floyd2(int n, const int* W, int* D, int* P) {

	for (int i=0; i<n*n; i++) {
		*(D+i) = *(W+i);						// D = W���� �ʱ�ȭ
		*(P+i) = 0;								// P = 0���� �ʱ�ȭ
	}

	for (int k=0; k<n; k++) {
		for (int i=0; i<n; i++) {
			for (int j=0; j<n; j++) {
				if (*(D + n*i + k) + *(D + n*k + j) < *(D + n*i + j)) {		// D[i][k] + D[k][j] �� D[i][j]�� ��
					*(P + n*i + j) = k + 1;									// i->j���� i->k->j�� �� ����ġ�� ���ٸ� ��ο� �߰��ϰ� �� ����
					*(D + n*i + j) = *(D + n*i + k) + *(D + n*k + j);
				}
			}
		}
	}
}

// ��θ� ����ϴ� �Լ�
void path(int i, int j, const int* P, int n){
	if (*(P + n*i + j) != 0) {					// �߰��� ���ľ� �ϴ� ��ΰ� �ִٸ�
		path(i, *(P + n*i + j)-1, P, n);		// �� ��� ���� ��ΰ� �� ���� ���� �ֱ⶧���� ��͹� ���
		printf(" -> %d", *(P + n*i + j));		// ��� ���
		path(*(P + n*i + j)-1, j, P, n);		// �� ��� ���Ŀ� ��ΰ� �� ���� ���� �ֱ⶧���� ��͹� ���
	}
}

// �ּҰ����� ����� ����ϴ� �Լ�
void printMatrix(const int* M, int n) {
	for (int i = 0; i<n; i++) {
		for (int j = 0; j<n; j++) {
			if (*(M + n*i + j) == INF)
				printf("  X ");
			else {
				printf("%3d ", *(M + n*i + j));
			}
		}
		printf("\n");
	}
}