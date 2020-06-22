#include <iostream>
#include <stdlib.h>
#include <Windows.h>

using std::cin;
using std::cout;
using std::endl;

// edge의 정보를 저장할 구조체
struct edge
{
	int w;		// 가중치 저장
	int a;		// 출발 노드 저장
	int b;		// 도착 노드 저장
};

typedef int index;
typedef index set_pointer;
typedef edge* set_of_edges;

// node의 정보를 저장할 구조체
struct nodetype
{
	index parent;
	int depth;
};

nodetype* U;	// 입력 받은 전체 node를 저장할 배열

void kruskal(int, int, set_of_edges, set_of_edges);	// Kruskal알고리즘 함수
int cmpW(const void*, const void*);					// qsort에서 사용될 비교함수
void makeset(index);								// 부분집합을 만드는 함수
set_pointer find(index);							// index가 포함된 집합의 주소를 반환하는 함수
void merge(set_pointer p, set_pointer q);			// 두 집합 p와 q를 합병하는 함수
bool equal(set_pointer, set_pointer);				// 두 집합 p와 q가 같은 집합을 가르키는지를 반환하는 함수
void initial(int);									// int개의 서로소 부분집합을 초기화 하는 함수

void main()
{
	// 입력받을 node의 개수를 입력받는다.
	int n;
	cout<<"Node의 개수를 입력하시오 : ";
	cin>>n;
	cout<<endl;

	// 이어서 입력받을 egde의 총 개수를 입력받는다.
	int m;
	cout<<"Edge의 총 개수를 입력하시오 : ";
	cin>>m;
	cout<<endl;

	// 입력받은 수에 따라 각각의 배열 초기화 (참고로, 배열의 0번은 사용하지 않고 1~n번을 사용한다.)
	U = new nodetype[n+1];
	set_of_edges E = new edge[m+1];
	set_of_edges F = new edge[n];

	// 빈 공간 없이 가중치들을 입력받는다.
	int mcount = 1;				// 입력받은 가중치를 카운트할 변수
	bool exitILoop = false;		// for문 제어변수
	cout<<"가중치를 입력하시오.(없으면 0 입력)"<<endl;
	while(mcount<m+1)
	{
		for(int i=1; i<=n; i++)
		{
			for(int j=i+1; j<=n; j++)
			{
				cout<<i<<"->"<<j<<" : ";
				cin>>E[mcount].w;
				if(E[mcount].w == 0)
					continue;
				else
				{
					E[mcount].a = i;
					E[mcount].b = j;
					mcount++;
				}

				// 가중치가 모두 입력이 완료되었으면 Loop 탈출
				if(mcount == m+1)
				{
					exitILoop = true;
					break;
				}
			}
			if(exitILoop)
				break;
		}

		// 만약 루프는 끝났는데 가중치가 모두 입력되지 않았으면 메시지 출력후 프로그램 종료
		if(mcount<m+1)
		{
			cout<<endl<<"입력한 수가 맞지 않습니다."<<endl;
			Sleep(2000);
			exit(0);
		}
	}

	// 입력받은 가중치 값들 출력
	cout<<endl<<"입력받은 모든 가중치 값 : "<<endl;
	for(int i=1; i<m+1; i++)
	{
		cout<<E[i].a<<" -> "<<E[i].b<<" = "<<E[i].w<<endl;
	}

	// Kruskal알고리즘 실행
	kruskal(n, m, E, F);

	cout<<endl<<"Kruskal알고리즘으로 얻은 최소비용신장트리 : "<<endl;
	for(int i=1; i<n; i++)
	{
		cout<<F[i].a<<" -> "<<F[i].b<<" = "<<F[i].w<<endl;
	}

//cout<<endl<<"U : "<<endl;
//for(int i=1; i<=n; i++)
//{
//	cout<<i<<"번의 parent = "<<U[i].parent<<", depth = "<<U[i].depth<<endl;
//}


	// 사용이 끝난 공간 해제 및 초기화
	delete[] U;
	delete[] E;
	delete[] F;
	U = NULL;
	E = NULL;
	F = NULL;

	system("pause");
}

// Kruskal알고리즘 함수
void kruskal(int n, int m, set_of_edges E, set_of_edges F)
{
	index i,j;
	set_pointer p,q;
	edge e;

	qsort(E, m+1, sizeof(edge), cmpW);	// QuickSort 사용
//cout<<endl<<"==================quicksort 완료=================="<<endl;
//for(int i=1; i<m+1; i++)
//{
//	cout<<E[i].a<<" -> "<<E[i].b<<" = "<<E[i].w<<endl;
//}
	// F = 0, 공간 할당과정에서 자동으로 공집합으로 초기화 되므로 생략
	initial(n);

	// 최소비용신장트리 찾는 과정
	index ecount = 1;		// E집합의 원소를 카운트 할 변수
	index fcount = 1;		// F집합의 원소를 카운트 할 변수
//cout<<endl<<"==================While문 시작=================="<<endl;
	while(ecount < m+1)
	{
//cout<<"ecount = "<<ecount<<", fcount = "<<fcount<<endl;
		e = E[ecount];
		i = e.a;
		j = e.b;
		p = find(i);
		q = find(j);
//cout<<"e = E["<<ecount<<"], w = "<<e.w<<", i = "<<i<<", j = "<<j<<", p = find[i] = "<<p<<", q = find[j] = "<<q<<endl;
		if(!equal(p,q))
		{
//cout<<"if문 진입 (p != q)"<<endl;
			merge(p,q);
			F[fcount] = e;
//cout<<"merge(p,q) 실행, F[fcount] = e, w = "<<e.w<<", i = "<<i<<", j = "<<j<<endl;
			if(++fcount == n)
				break;
		}
//cout<<endl;
		ecount++;
//cout<<endl<<"==================While문 완료=================="<<endl;
	}
}

// qsort에서 사용될 비교함수
int cmpW(const void* a, const void* b)
{
	edge* w1 = (edge*)a;
	edge* w2 = (edge*)b;

	if(w1->w < w2->w)
		return -1;
	if(w1->w > w2->w)
		return 1;
	return 0;
}

// 부분집합을 만드는 함수
void makeset(index i)
{ 
	U[i].parent = i;
	U[i].depth = 0; 
//cout<<endl<<"==================makeset "<<i<<"번 완료=================="<<endl;
//cout<<"U["<<i<<"].parent = "<<U[i].parent<<", U["<<i<<"].depth = "<<U[i].depth<<endl;
} 

// index가 포함된 집합의 주소를 반환하는 함수
set_pointer find(index i)
{   
	index j;
	j = i; 
	while(U[j].parent != j) 
		j=U[j].parent;    
	return j;   
} 

// 두 집합 p와 q를 합병하는 함수
void merge(set_pointer p, set_pointer q)
{ 
	if(U[p].depth == U[q].depth) 
	{ 
		U[p].depth =+ 1;
		U[q].parent = p;
	} 
	else if(U[p].depth < U[q].depth) 
		U[p].parent = q; 
	else 
		U[q].parent = p; 
}

// 두 집합 p와 q가 같은 집합을 가르키는지를 반환하는 함수
bool equal(set_pointer p, set_pointer q) 
{ 
	if (p == q) 
		return TRUE;    
	else 
		return FALSE; 
} 

// int개의 서로소 부분집합을 초기화 하는 함수
void initial(int n) 
{ 
//cout<<endl<<"==================Initial 시작=================="<<endl;
	index i; 
	for(i=1; i<=n; i++) 
		makeset(i);
//cout<<endl<<"==================Initial 완료=================="<<endl;
}
