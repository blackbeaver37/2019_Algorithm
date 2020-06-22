#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <Windows.h>

// 이번 알고리즘에서는 4X4 행렬을 입력값으로 사용 할 것이므로 N = 4 정의
const int N = 4;

void Strassen(int, int*, int*, int*);
void MatrixRePlace(int, int*);
void MatrixSum(int, int*, int*, int*);
void MatrixDif(int, int*, int*, int*);

void main() {
	int* ptA = (int*)malloc(N * N * sizeof(int*));					// 첫번째 행렬을 받을 16개의 공간 (4X4행렬이므로 16개의 int형 공간 사용)
	int* ptB = (int*)malloc(N * N * sizeof(int*));					// 두번째 행렬을 받을 16개의 공간
	int* ptC = (int*)malloc(N * N * sizeof(int*));					// 결과 행렬을 받을 16개의 공간

	// 포인터의 접근을 쉽게 하기위해 4X4행렬을 한줄로 받음
	printf("첫번째 %d X %d 행렬의 값을 입력 하시오.\n", N, N);
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {								// 1행의 원소들은 ptA, ptA+1, ptA+2, ptA+3의 주소에 저장
			printf("A%d%d = ", i + 1, j + 1);						// 2행의 원소들은 그 다음 ptA+4 부터 ptA+7의 주소에 저장
			scanf("%d", ptA + (i*N) + j);							// 나머지 행들도 위와 같은 방법으로 ptA+15까지 16개의 원소를 한줄로 저장
		}															 
	}																
	printf("\n");

	// 입력받은 행렬을 출력
	printf("입력된 첫번째 행렬 : \n");
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			printf("%d ", *(ptA + (i*N) + j));
		}
		printf("\n");												// 원소를 4번 출력 후에는 행이 바뀌기 때문에 개행
	}
	printf("\n");

	// 두번째 행렬 입력
	printf("두번째 %d X %d 행렬의 값을 입력 하시오.\n", N, N);
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			printf("B%d%d = ", i + 1, j + 1);
			scanf("%d", ptB + (i*N) + j);
		}
	}
	printf("\n");

	// 두번째 행렬 출력
	printf("입력된 두번째 행렬 : \n");
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			printf("%d ", *(ptB + (i*N) + j));
		}
		printf("\n");
	}
	printf("\n");

	// 행렬의 길이 N, 계산할 두 행렬의 주소를 가지고 있는 mA, mB, 결과행렬의 값을 저장할 주소를 가지고 있는 mC를 인자 값으로 사용
	Strassen(N, ptA, ptB, ptC);

	// 슈트라센 알고리즘을 이용하여 나온 결과 값 출력
	printf("슈트라센 알고리즘을 이용하여 구한 두 행렬의 곱셈 값 : \n");
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			printf("%d ", *(ptC + (i*N) + j));
		}
		printf("\n");
	}
	printf("\n");

	// 프로그램 종료 시 사용했던 공간 해제
	free(ptA);
	free(ptB);
	free(ptC);
	
	system("pause");
}

// 슈트라센 알고리즘 함수
void Strassen(int n, int* A, int* B, int* C) {
	
	// n = 1 일때는 단순 곱 계산
	if (n <= 1) {
		*C = *A * *B;
	}

	// 예외 처리
	else {
		int* M[7];																				// M은 M1부터 M7까지의 주소값을 가지는 포인터 배열
		for (int i = 0; i < 7; i++) {															// TempA는 M행렬을 구하는 과정에서 A11+A22와 같이 A의 분할된 행렬들의 합 또는 차 계산을 임시적으로 저장하는 주소를 같는 포인터
			M[i] = (int*)malloc((int)pow((n/2), 2) * sizeof(int*));								// TempB도 위에 TempA 포인터와 같은 역할
		}																						// 메모리 할당은 n = 4일때는 나뉜 함수가 2X2, n = 1일때는 나뉜 함수가 1X1이므로 n/2의 제곱 만큼의 공간이 필요
		int* TempA = (int*)malloc((int)pow((n/2), 2) * sizeof(int*));							
		int* TempB = (int*)malloc((int)pow((n/2), 2) * sizeof(int*));
		
		// n = 4인 경우 4개로 나뉜 함수 A11은 A, A+1, A+4, A+5의 주소에 존재
		// 이 때 포인터 접근을 편하게 하기위해서 A11의 원소 값들을 A부터 A+3의 주소에 저장, A12의 원소 값들은 A+4부터 A+7주소에 저장하는 식으로 원소들의 위치를 변경
		MatrixRePlace(n, A);
		MatrixRePlace(n, B);

		// M1 계산
		// A11은 A주소에서 시작, A12는 n=4인 경우에는 A+4주소에서 시작, n=1인 경우에는 A+1에서 시작하므로 아래와 같이 계산
		MatrixSum(n/2, A, A + 3*(int)pow((n / 2), 2), TempA);		// A11 + A22
		MatrixSum(n/2, B, B + 3*(int)pow((n / 2), 2), TempB);		// B11 + B22
		Strassen(n/2, TempA, TempB, M[0]);

		// M2 계산
		MatrixSum(n/2, A + 2*(int)pow((n/2), 2), A + 3*(int)pow((n/2), 2), TempA);
		Strassen(n/2, TempA, B, M[1]);

		// M3 계산
		MatrixDif(n/2, B + 1*(int)pow((n/2), 2), B + 3*(int)pow((n/2), 2), TempB);
		Strassen(n/2, A, TempB, M[2]);

		// M4 계산
		MatrixDif(n/2, B + 2*(int)pow((n/2), 2), B, TempB);
		Strassen(n/2, A + 3*(int)pow((n/2), 2), TempB, M[3]);

		// M5 계산
		MatrixSum(n/2, A, A + 1*(int)pow((n/2), 2), TempA);
		Strassen(n/2, TempA, B + 3*(int)pow((n/2), 2), M[4]);

		// M6 계산
		MatrixDif(n/2, A + 2*(int)pow((n/2), 2), A, TempA);
		MatrixSum(n/2, B, B + 1*(int)pow((n/2), 2), TempB);
		Strassen(n/2, TempA, TempB, M[5]);

		// M7 계산
		MatrixDif(n/2, A + 1*(int)pow((n/2), 2), A + 3*(int)pow((n/2), 2), TempA);
		MatrixSum(n/2, B + 2*(int)pow((n/2), 2), B + 3*(int)pow((n/2), 2), TempB);
		Strassen(n/2, TempA, TempB, M[6]);

		// TempA와 TempB 두 포인터는 사용이 끝났으므로 공간 해제 
		free(TempA);
		free(TempB);

		// M행렬을 이용하여 C행렬(결과행렬) 계산하는 과정에서 M행렬들의 합 또는 차를 임시 저장하기위한 공간 할당
		int* TempC1 = (int*)malloc((int)pow((n/2), 2) * sizeof(int*));
		int* TempC2 = (int*)malloc((int)pow((n/2), 2) * sizeof(int*));

		// C11 계산
		MatrixSum(n/2, M[0], M[3], TempC1);
		MatrixDif(n/2, TempC1, M[4], TempC2);
		MatrixSum(n/2, TempC2, M[6], C);

		// C12 계산
		MatrixSum(n/2, M[2], M[4], C + 1*(int)pow((n/2), 2));

		// C21 계산
		MatrixSum(n/2, M[1], M[3], C + 2*(int)pow((n/2), 2));

		// C22 계산
		MatrixSum(n/2, M[0], M[2], TempC1);
		MatrixDif(n/2, TempC1, M[1], TempC2);
		MatrixSum(n/2, TempC2, M[5], C + 3*(int)pow((n/2), 2));

		// M포인터 배열과 TempC1, TempC2 포인터는 사용이 끝났으므로 공간 해제
		for (int i = 0; i < 7; i++) {
			free(M[i]);
		}
		free(TempC1);
		free(TempC2);

		// C 포인터에 저장된 결과 행렬 역시 접근을 편하게 하기 위해 원소들의 위치가 바뀐 채로 저장되었으므로 다시 원소들의 위치 복구
		MatrixRePlace(n, C);
	}
}

// 포인터의 접근을 쉽게 하기위해 n = 4일 경우에 원소들의 위치 변환, n = 2일 경우에는 위치를 변환 할 필요가 없음
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

// 포인터를 이용하여 A와 B가 가르키는 두 행렬의 합을 C의 주소에 넣는 함수
void MatrixSum(int n, int* A, int* B, int* C) {
	for (int i = 0; i < n*n; i++) {
		*(C + i) = *(A + i) + *(B + i);
	}
}

// 포인터를 이용하여 A와 B가 가르키는 두 행렬의 차를 C의 주소에 넣는 함수
void MatrixDif(int n, int* A, int* B, int* C) {
	for (int i = 0; i < n*n; i++) {
		*(C + i) = *(A + i) - *(B + i);
	}
}