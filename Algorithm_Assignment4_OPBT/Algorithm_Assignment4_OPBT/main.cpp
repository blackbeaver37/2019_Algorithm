#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include <float.h>

void optserchtree(int, const float*, float, int*);
void printMatrix(const int*, int);

void main() {

	// Ű�� ���� �Է�
	int n;
	printf("Ű�� ������ �Է��Ͻÿ� : ");
	scanf("%d", &n);

	// ������ Ȯ���� �Է�
	float* p = (float*)malloc(n*sizeof(float));
	float f1, f2;
	for (int i=0; i<n; i++) {
		printf("%d��° Ű�� Ȯ���� �Է��Ͻÿ�(a/b) : ", i+1);
		scanf("%f/%f", &f1, &f2);
		*(p+i) = f1 / f2;
	}
	
	// �ּ� �˻���հ��� ������ ���� ����
	float minavg = 0;
	
	// �ּ� �˻���հ��� ������ ��Ʈ�� Ű�ѹ��� ������ ��� ����
	int* R = (int*)malloc((n+2)*(n+2)*sizeof(int));

	// OBST �˰��� ����
	optserchtree(n, p, minavg, R);

	// R��� ���
	printf("\nR = \n");
	printMatrix(R, n+2);

	// ���� ����
	free(R);
	free(p);

	system("pause");
}

// OBPS �˰��� �Լ�
void optserchtree(int n, const float* p, float minavg, int* R) {
	
	// minavg�� ���ϱ� ���� A ��� ����
	float* A = (float*)malloc((n+2)*(n+2)*sizeof(float));

	// �밢�� = 0 �ʱ�ȭ, x=y �� �κ� �ʱ�ȭ
	for (int i=1; i<=n; i++) {
		*(A + (n+2)*i + (i-1)) = 0;
		*(A + (n+2)*i + i) = *(p + (i-1));
		*(R + (n+2)*i + i) = i;
		*(R + (n+2)*i + (i-1)) = 0;
	}
	*(A + (n+2)*(n+1) + n) = 0;
	*(R + (n+2)*(n+1) + n) = 0;

	for (int diag = 1; diag <= n-1; diag++) {
		for (int j, i=1; i<=n-diag; i++) {
			j = i + diag;
			*(A + (n+2)*i + j) = FLT_MAX;				// �ּڰ��� ���� ���̱� ������ ���� �񱳵��� ���� ���� float�� �ִ밪���� �ʱ�ȭ
			for (int k=i; k<=j; k++) {

				// ���� �� �ñ׸� ����� ���� temp �� for��
				float temp = 0;
				for (int m=i; m<=j; m++) {
					temp += *(p + (m-1));
				}

				// �� ���� �� �� ������ �߰� �� �� �ٲ�
				if (*(A + (n+2)*i + j) > *(A + (n+2)*i + (k-1)) + *(A + (n+2)*(k+1) + j) + temp ) {
					*(A + (n+2)*i + j) = *(A + (n+2)*i + (k-1)) + *(A + (n+2)*(k+1) + j) + temp;
					*(R + (n+2)*i + j) = k;
				}
			}

			// minavg = A[1][n]
			minavg = *(A + (n+2) + n);
		}
	}

	// ���� ����
	free(A);

	// ������ minavg�� ���
	printf("\nminavg = %.4f\n", minavg);
}

// �ּҰ����� ����� ����ϴ� �Լ�
void printMatrix(const int* M, int n) {
	for (int i = 1; i<n; i++) {
		for (int j = 0; j<n-1; j++) {
			if (*(M + n*i + j) < 0) {
				printf("  X ");
				continue;
			}
			printf("%3d ", *(M + n*i + j));
		}
		printf("\n");
	}
}