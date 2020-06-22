#include <iostream>
#include <iomanip>
#include <windows.h>

using std::cout;
using std::cin;
using std::endl;
using std::setw;

typedef int index;
typedef int size;

void hamiltonian(index i);
bool promising(index i);

size n;
bool* W;
index* vindex;

void main()
{
	// 정점의 개수를 입력받는다.
	cout<<"정점의 개수를 입력하시오 : ";
	cin>>n;
	cout<<endl;

	// 정점 수 의거 공간할당 및 초기화
	W = new bool[(n+1)*(n+1)];
	for(index i=0; i<(n+1)*(n+1); i++)
		W[i] = false;

	// 정점 수 의거 공간할당 및 초기화
	vindex = new index[n];
	vindex[0] = 1;

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

	// Hamiltonian 알고리즘 함수 실행
	hamiltonian(0);
	cout<<endl;

	// 공간 해제
	delete[] W;
	delete[] vindex;
	W = NULL;
	vindex = NULL;

	system("pause");
}

// Hmiltonian 알고리즘 함수
void hamiltonian(index i)
{
	index j;

	// 유망한지 판단
	if(promising(i))
	{
		// 만약 경로를 다 돌았다면
		if(i == n-1)
		{
			static int count = 1;
			cout<<endl<<setw(2)<<count<<"번 경로 : ";
			for(j=0; j<n; j++)
				cout<<setw(2)<<vindex[j];
			cout<<endl;
			count++;
		}
		// 아직 경로가 남아있다면
		else
		{
			for(j=2; j<=n; j++)
			{
				vindex[i+1] = j;
				hamiltonian(i+1);
			}
		}
	}
}

// 유망한지 판단하는 함수
bool promising(index i)
{
	index j;
	bool swtch;
	if(i == n-1 &&! W[(n+1)*vindex[n-1] + vindex[0]])
	{
		swtch = false;
	}
	else if(i>0 &&! W[(n+1)*vindex[i-1] + vindex[i]])
	{
		swtch = false;
	}
	else
	{
		swtch = true;
		j = 1;
		while(j<i && swtch)
		{
			if(vindex[i] == vindex[j])
				swtch = false;
			j++;
		}
	}
	return swtch;
}