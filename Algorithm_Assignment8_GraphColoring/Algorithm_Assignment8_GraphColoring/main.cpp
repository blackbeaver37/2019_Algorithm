#include <iostream>
#include <iomanip>
#include <Windows.h>

using std::cout;
using std::cin;
using std::endl;
using std::setw;

typedef int index;
typedef int size;

void m_coloring (index i);
bool promising (index i);

size n;
int m;
bool *W;
int *vcolor;


void main()
{
	// 노드 및 색의 개수를 입력 받는다.
	cout<<"노드의 개수를 입력하시오 : ";
	cin>>n;
	cout<<endl<<"색의 개수를 입력하시오 : ";
	cin>>m;
	cout<<endl;

	// W배열 초기화
	W = new bool[(n+1)*(n+1)];
	for(index i = 0; i<(n+1)*(n+1); i++)
		W[i] = false;

	// W배열의 값을 입력 받는다.
	cout<<"경로를 입력하시오 (노드 노드 형식으로 입력, 다 입력 하면 0 0 입력) : "<<endl;
	int count = 1;
	index i,j;
	while(count != 0)
	{
		cout<<setw(2)<<count<<"번째 경로를 입력하시오 : ";
		cin>>i>>j;
		if(i==0)
		{
			count = 0;
			continue;
		}
		W[(n+1)*i + j] = true;
		W[(n+1)*j + i] = true;
		count++;
	}

	// vcolor 공간할당
	vcolor = new int[n+1];

	// 가시성을 위해 추가한 코드입니다!!
	cout<<endl;
	cout<<setw(14)<<"";
	for(index i = 1; i<=n; i++)
		cout<<setw(2)<<i;
	cout<<endl;

	// 알고리즘 함수 실행
	m_coloring(0);
	cout<<endl;

	// 사용이 끝난 공간 해제
	delete[] W;
	delete[] vcolor;
	W = NULL;
	vcolor = NULL;

	system("pause");
}

// Graph Coloring 알고리즘 함수
void m_coloring (index i)
{
	int color;

	// 만약 유망하다면
	if(promising(i))
	{
		if(i==n)
		{
			// 마지막 노드까지 비교가 끝났다면
			static int count=1;
			cout<<setw(2)<<count<<"번째 결과 : ";
			for(index j=1; j<=n; j++)
				cout<<setw(2)<<vcolor[j];
			cout<<endl;
			count++;
		}
		else
		{
			// 아직 비교가 끝나지 않았다면
			for(color=1; color<=m; color++)
			{
				vcolor[i+1] = color;
				m_coloring(i+1);
			}
		}
	}
}


// 유망한지 판단하는 함수
bool promising(index i)
{
	index j;
	bool swtch;

	swtch = true;
	j = 1;
	while(j<i && swtch)
	{
		if(W[(n+1)*i + j] && vcolor[i] == vcolor[j])
			swtch = false;
		j++;
	}
	return swtch;
}