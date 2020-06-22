#include <iostream>
#include <Windows.h>
#include <stdlib.h>
#include <iomanip>
#include <string>

using std::cout;
using std::cin;
using std::endl;
using std::setw;
using std::string;

typedef int index;
typedef int size;

size n;				// 원소의 개수 저장할 변수
int* w;				// 각 원소의 weight를 저장할 배열
int W;				// 목표 합
string* include;	// YES NO 값을 저장할 문자열 배열

void sum_of_subsets (index i, int weight, int total);
bool promising (index i, int weight, int total);

void main()
{
	// 원소의 개수를 입력 받는다
	cout<<"집합의 원소들의 개수를 입력하시오 : ";
	cin>>n;
	cout<<endl;

	w = new int[n+1];		// 입력받은 n값 이용 공간 할당
	w[0] = 0;				// 1번 ~ n번 사용
	int total = 0;

	cout<<"정렬된 집합을 입력하시오."<<endl;
	for(index i = 1; i<=n; i++)
	{
		cout<<setw(2)<<i<<"번째 원소를 입력하시오 : ";
		cin>>w[i];
		total += w[i];		// 입력받으면서 total값 초기화
	}
	cout<<endl;

	cout<<"기준이 될 합을 입력하시오 : ";
	cin>>W;
	cout<<endl;

	include = new string[n+1];
	int weight = 0;

	// 알고리즘 결과 출력시 가시성을 위해 추가한 코드 입니다!
	cout<<setw(14)<<"";
	for(index i=1; i<=n; i++)
		cout<<setw(4)<<w[i];
	cout<<endl;

	// 알고리즘 실행
	sum_of_subsets(0, weight, total);

	cout<<endl;
	
	// 사용이 끝난 공간 해제
	delete[] w;
	delete[] include;
	w = NULL;
	include = NULL;

	system("pause");
}

// Sum of Subsets 알고리즘 함수
void sum_of_subsets (index i, int weight, int total)
{
	// 유망한지 판단
	if (promising(i, weight, total))
	{
		if (weight == W)
		{
			// 원하는 답이 나왔을 때
			static int count = 1;
			cout<<setw(2)<<count<<"번째 방법 : ";
			for(index j=1; j<=i; j++)
				cout<<setw(4)<<include[j];
			count++;
			cout<<endl;
		}
		else
		{
			// 유망하지만 원하는 답이 아니면 계속 탐색
			include[i+1] = "YES";
			sum_of_subsets(i+1, weight + w[i+1], total - w[i+1]);
			include[i+1] = " NO";
			sum_of_subsets(i+1, weight, total - w[i+1]);
		}
	}
}

// 유망한지 판단하는 함수
bool promising (index i, int weight, int total)
{
	return (weight + total >= W) && (weight == W || weight+w[i+1] <= W) ;
}