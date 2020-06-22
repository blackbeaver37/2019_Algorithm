#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include <math.h>

int minmult(int, const int*, int*);				// 최소 곱셈 횟수를 반환해주는 알고리즘 함수
void order(int, int, int, const int*);			// 최적의 순서를 출력해주는 함수
void printMatrix(const int*, int);				// 주소값으로 행렬을 출력하는 함수

void main() {
	
	// 행렬의 수 입력
	int n;
	printf("구하려는 행렬 곱셈에서 행렬의 수를 입력하시오 : ");
	scanf("%d", &n);

	// 공간 할당
	int* d = (int*)malloc((n+1) * sizeof(int));		// 1번행렬의 행 수 + 모든 행렬의 열 수 이므로 n+1개 공간
	int* P = (int*)malloc(n*n * sizeof(int));		// n*n개 공간

	// P = 0 초기화
	for (int i = 0; i < n*n; i++) {
		*(P+i) = 0;
	}

	// d의 값 입력
	for (int i = 0; i < n; i++) {
		if (i == 0) {
			printf("\n%d번 행렬의 행의 갯수를 입력하시오 : ", i+1);
			scanf("%d", d+i);
		}
		printf("\n%d번 행렬의 열의 갯수를 입력하시오 : ", i+1);
		scanf("%d", d+i+1);
	}

	// minmult함수 실행
	printf("\n위 행렬 곱셈 시 계산횟수의 최솟값은 : %d번 이다.\n", minmult(n, d, P));

	// 알고리즘에 의해 구해진 P행렬 출력
	printf("\nP = \n");
	printMatrix(P, n);

	// order함수 실행하여 곱셈순서 출력
	printf("\n 행렬을 곱하는 최적의 순서 : ");
	order(1, n, n, P);
	printf("\n");

	// 공간 해제
	free(d);
	free(P);

	system("pause");
}

// 최소 곱셈 수를 반환하는 알고리즘 함수
int minmult(int n, const int* d, int* P) {
	int* M = (int*)malloc(n*n*sizeof(int));		// M행렬 n*n개의 공간 할당

	// 대각선 부분은 0으로 초기화
	for (int i = 0; i < n; i++)
		*(M + n*i + i) = 0;

	// 대각선 기준 윗 부분 값들 비교하며 최솟값 저장
	for (int diag = 1; diag <= n-1; diag++) {
		int j;
		for (int i = 0; i < n - diag; i++) {
			j = i + diag;
			*(M + n*i + j) = INT_MAX;			// 아직 비교되지 않은 부분들은 큰 값으로 초기화 해둠
			int temp;
			for (int k = i; k <= j - 1; k++) {
				temp = *(M + n*i + k) + *(M + n*(k+1) + j) + *(d + i) * *(d + k+1) * *(d + j+1);
				if (temp < *(M + n*i + j)) {
					*(M + n*i + j) = temp;		// 만약 지금 값이 더 작다면 M행렬에 저장 
					*(P + n*i + j) = k+1;		// 그리고 P행렬에 위치 저장
				}
			}
		}
	}
	int ret = *(M + n - 1);
	free(M);		// 공간 해제
	return ret;		// M[1][n] 최종값 반환
}

// 최적의 순서를 출력해주는 함수
void order(int i, int j, int n, const int* P) {
	int k;
	if (i == j)
		printf("A%d", i);					// 두 인덱스가 같아지면 더이상 비교할 곳이 없으므로 출력
	// 재귀함수 및 P행렬 이용하여 i == j 가 될때까지 최적의 곱셈부분으로 나누면서 순서 출력
	else {
		k = *(P + n*(i - 1) + (j - 1));		
		printf("(");						
		order(i, k, n, P);
		order(k + 1, j, n, P);
		printf(")");
	}
}

// 주소값으로 행렬을 출력하는 함수
void printMatrix(const int* M, int n) {
	for (int i = 0; i<n; i++) {
		for (int j = 0; j<n; j++) {
			printf("%3d ", *(M + n*i + j));
		}
		printf("\n");
	}
}