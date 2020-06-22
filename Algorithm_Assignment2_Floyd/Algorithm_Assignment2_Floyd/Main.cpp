#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>

void floyd2(int, const int*, int*, int*);						// Floyd2 알고리즘 함수
void path(int, int, const int*, int);							// 경로를 출력하는 함수
void printMatrix(const int*, int);								// 주소값을 이용하여 행렬 출력하는 함수

const int INF = 1000000000;										// 경로가 없는 경우 넣을 값으로 큰 수 설정

void main() {

	// Vertex의 수를 받는다.
	int n;														
	printf("Vertex의 갯수를 입력하세요 : ");
	scanf("%d", &n);

	// 받은 Vertex의 수 의거하여 공간 할당
	int* W = (int*)malloc(n*n * sizeof(int*));					// W 5x5 경로행렬
	int* D = (int*)malloc(n*n * sizeof(int*));					// D 5x5 최단경로의 길이행렬
	int* P = (int*)malloc(n*n * sizeof(int*));					// P 5x5 최단경로행렬

	// 각 Vertex사이의 가중치 값을 입력받음
	printf("각 경로의 가중치 값을 입력하시오 (단, 경로가 없을 경우에는 0 입력) : \n");
	for (int i=0; i<n; i++) {
		for (int j=0; j<n; j++) {
			if (i != j) {
				printf("%d-->%d 경로의 가중치 : ", i+1, j+1);
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

	// 받은 가중치 값을 이용한 경로행렬 출력
	printf("\n");
	printf("입력된 경로 행렬 W = \n");
	printMatrix(W, n);

	// Floyd2알고리즘 실행
	floyd2(n, W, D, P);

	// 알고리즘의 결과물로 최단경로 값을 가지는 행렬 출력
	printf("\n");
	printf("최단경로의 길이행렬 D\n");
	printMatrix(D, n);

	// 최단경로 값을 위한 경로를 알려주는 행렬 출력 
	printf("\n");
	printf("최단경로행렬 P\n");
	printMatrix(P, n);

	// 사용이 끝난 공간 해제
	free(W);
	free(D);

	int iPath;								// 경로 탐색을 계속, 중단할지 정하는 값

printPath :

	// path함수를 이용한 경로 출력
	int indexA, indexB;
	printf("\n경로 탐색 : ");
	scanf("%d %d", &indexA, &indexB);
	printf("\n거치는 경로 : %d", indexA);
	path(indexA - 1, indexB - 1, P, n);
	printf(" -> %d\n", indexB);

	printf("\n경로를 더 출력하시겠습니까?(yes == 1 / no == 0) : ");
	scanf("%d", &iPath);
	if (iPath)
		goto printPath;					// 경로를 한번더 출력 한다고 하였다면 printPath로 이동, 반복
	
	// 사용이 끝난 공간 해제
	free(P);

	system("pause");
}

// Floyd 알고리즘 함수
void floyd2(int n, const int* W, int* D, int* P) {

	for (int i=0; i<n*n; i++) {
		*(D+i) = *(W+i);						// D = W으로 초기화
		*(P+i) = 0;								// P = 0으로 초기화
	}

	for (int k=0; k<n; k++) {
		for (int i=0; i<n; i++) {
			for (int j=0; j<n; j++) {
				if (*(D + n*i + k) + *(D + n*k + j) < *(D + n*i + j)) {		// D[i][k] + D[k][j] 와 D[i][j]를 비교
					*(P + n*i + j) = k + 1;									// i->j보다 i->k->j가 더 가중치가 적다면 경로에 추가하고 값 변경
					*(D + n*i + j) = *(D + n*i + k) + *(D + n*k + j);
				}
			}
		}
	}
}

// 경로를 출력하는 함수
void path(int i, int j, const int* P, int n){
	if (*(P + n*i + j) != 0) {					// 중간에 거쳐야 하는 경로가 있다면
		path(i, *(P + n*i + j)-1, P, n);		// 그 경로 전에 경로가 더 있을 수도 있기때문에 재귀문 사용
		printf(" -> %d", *(P + n*i + j));		// 경로 출력
		path(*(P + n*i + j)-1, j, P, n);		// 그 경로 이후에 경로가 더 있을 수도 있기때문에 재귀문 사용
	}
}

// 주소값으로 행렬을 출력하는 함수
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