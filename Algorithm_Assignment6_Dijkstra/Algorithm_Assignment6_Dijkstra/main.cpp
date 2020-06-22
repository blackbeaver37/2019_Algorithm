#include <iostream>
#include <stdlib.h>
#include <Windows.h>
#include <iomanip>

#define BIGNUM 10000		// 값이 채워지지 않을 공간에 초기화할 큰 수

using std::cout;
using std::cin;
using std::endl;
using std::setw;

typedef int index;
typedef int number;

// Edge의 시작노드, 도착노드, 가중치 값을 저장할 구조체 선언
struct Edge
{
	index from;
	index to;
	index weight;
};

typedef Edge* set_of_Edges;

void dijkstra(int, const number*, set_of_Edges&);		// Dijkstra 알고리즘 함수

void main()
{
	// 정점의 개수를 입력받는다.
	int n;
	cout<<"정점의 개수를 입력하시오 : ";
	cin>>n;

	// 가중치를 입력받을 행렬 선언 및 공간 할당
	number* W = new number[(n+1)*(n+1)];

	// W 행렬을 먼저 큰 수로 초기화 한다
	index i, j;
	index count = 1;
	for(i=1; i<=n; i++)
	{
		for(j=1; j<=n; j++)
		{
			W[(n+1)*i + j] = BIGNUM;
		}
	}

	// W 행렬에 가중치를 입력받는다.
	cout<<endl<<"경로의 가중치를 입력하시오. (시작 끝 가중치 형식으로 입력, 없다면 0 0 0 입력) : "<<endl;
	while(count)
	{
		cout<<setw(2)<<count<<"번 가중치를 입력하시오 : ";
		cin>>i;
		cin>>j;
		cin>>W[(n+1)*i + j];
		if( i==0 && j==0 && W[(n+1)*i + j]==0)
			break;
		count++;
	}

	// Dijkstra 알고리즘 후에 얻을 F 선언 및 공간할당
	set_of_Edges F = new Edge[n];

	// Dijkstra 알고리즘 실행
	dijkstra(n, W, F);
	
	// Dijkstra 알고리즘으로 구한 F 출력
	cout<<endl<<"구한 F"<<endl;
	for(int i=1; i<n; i++)
	{
		cout<<setw(2)<<F[i].from<<" -> "<<setw(2)<<F[i].to<<" = "<<setw(2)<<F[i].weight<<endl;
	}
	
	// 사용이 끝난 공간 해제
	delete[] W;
	delete[] F;
	W = NULL;
	F = NULL;

	system("pause");
}

// Dijkstra 알고리즘 함수
void dijkstra(int n, const number* W, set_of_Edges &F)
{
	index i, vnear;
	Edge e;
	index* touch = new index[n+1];
	number* length = new number[n+1];
//	F = NULL;	공간 할당 시에 자동으로 공집합 선언이 됨으로 생략

	// touch 및 length배열 초기화
	for(i=2; i<=n; i++)
	{
		touch[i] = 1;
		length[i] = W[(n+1)*1 + i];
	}

	index count = 1;
	while (count < n)
	{
		// length중 초기화 찾은 후에 min, vnear값 초기화 과정
		int min = BIGNUM;
		for(i=2; i<=n ; i++)
		{
			if(0 <= length[i] && length[i] <= min)
			{
				min = length[i];
				vnear = i;
			}
		}

		// 위 for문에서 찾은 Edge를 F 배열에 넣는다.
		e.from = touch[vnear];
		e.to = vnear;
		e.weight = W[ (n+1)*touch[vnear] + vnear];
		F[count] = e;

		// 추가된 노드를 이용하여 더 짧은 길이 있다면 length, touch값 수정
		for(i=2; i<=n; i++)
		{
			if( (length[vnear] + W[(n+1)*vnear + i]) < length[i] )
			{
				length[i] = length[vnear] + W[(n+1)*vnear + i];
				touch[i] = vnear;
			}
		}
		length[vnear] = -1;		// F배열에 추가 완료한 길은 -1로 초기화
		count++;
	}
}