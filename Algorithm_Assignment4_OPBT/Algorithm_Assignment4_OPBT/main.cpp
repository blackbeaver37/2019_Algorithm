#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include <float.h>

void optserchtree(int, const float*, float, int*);
void printMatrix(const int*, int);

void main() {

	// 키의 갯수 입력
	int n;
	printf("키의 개수를 입력하시오 : ");
	scanf("%d", &n);

	// 각각의 확률값 입력
	float* p = (float*)malloc(n*sizeof(float));
	float f1, f2;
	for (int i=0; i<n; i++) {
		printf("%d번째 키의 확률을 입력하시오(a/b) : ", i+1);
		scanf("%f/%f", &f1, &f2);
		*(p+i) = f1 / f2;
	}
	
	// 최소 검색평균값을 저장할 변수 선언
	float minavg = 0;
	
	// 최소 검색평균값을 가질때 루트의 키넘버를 저장할 행렬 선언
	int* R = (int*)malloc((n+2)*(n+2)*sizeof(int));

	// OBST 알고리즘 실행
	optserchtree(n, p, minavg, R);

	// R행렬 출력
	printf("\nR = \n");
	printMatrix(R, n+2);

	// 공간 해제
	free(R);
	free(p);

	system("pause");
}

// OBPS 알고리즘 함수
void optserchtree(int n, const float* p, float minavg, int* R) {
	
	// minavg를 구하기 위한 A 행렬 선언
	float* A = (float*)malloc((n+2)*(n+2)*sizeof(float));

	// 대각선 = 0 초기화, x=y 인 부분 초기화
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
			*(A + (n+2)*i + j) = FLT_MAX;				// 최솟값을 비교할 것이기 때문에 아직 비교되지 않은 곳은 float형 최대값으로 초기화
			for (int k=i; k<=j; k++) {

				// 수식 내 시그마 계산을 위한 temp 및 for문
				float temp = 0;
				for (int m=i; m<=j; m++) {
					temp += *(p + (m-1));
				}

				// 비교 실행 및 더 작은값 발견 시 값 바꿈
				if (*(A + (n+2)*i + j) > *(A + (n+2)*i + (k-1)) + *(A + (n+2)*(k+1) + j) + temp ) {
					*(A + (n+2)*i + j) = *(A + (n+2)*i + (k-1)) + *(A + (n+2)*(k+1) + j) + temp;
					*(R + (n+2)*i + j) = k;
				}
			}

			// minavg = A[1][n]
			minavg = *(A + (n+2) + n);
		}
	}

	// 공간 해제
	free(A);

	// 구해진 minavg값 출력
	printf("\nminavg = %.4f\n", minavg);
}

// 주소값으로 행렬을 출력하는 함수
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