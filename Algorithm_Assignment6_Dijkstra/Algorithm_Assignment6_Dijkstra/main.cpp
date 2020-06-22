#include <iostream>
#include <stdlib.h>
#include <Windows.h>
#include <iomanip>

#define BIGNUM 10000		// ���� ä������ ���� ������ �ʱ�ȭ�� ū ��

using std::cout;
using std::cin;
using std::endl;
using std::setw;

typedef int index;
typedef int number;

// Edge�� ���۳��, �������, ����ġ ���� ������ ����ü ����
struct Edge
{
	index from;
	index to;
	index weight;
};

typedef Edge* set_of_Edges;

void dijkstra(int, const number*, set_of_Edges&);		// Dijkstra �˰��� �Լ�

void main()
{
	// ������ ������ �Է¹޴´�.
	int n;
	cout<<"������ ������ �Է��Ͻÿ� : ";
	cin>>n;

	// ����ġ�� �Է¹��� ��� ���� �� ���� �Ҵ�
	number* W = new number[(n+1)*(n+1)];

	// W ����� ���� ū ���� �ʱ�ȭ �Ѵ�
	index i, j;
	index count = 1;
	for(i=1; i<=n; i++)
	{
		for(j=1; j<=n; j++)
		{
			W[(n+1)*i + j] = BIGNUM;
		}
	}

	// W ��Ŀ� ����ġ�� �Է¹޴´�.
	cout<<endl<<"����� ����ġ�� �Է��Ͻÿ�. (���� �� ����ġ �������� �Է�, ���ٸ� 0 0 0 �Է�) : "<<endl;
	while(count)
	{
		cout<<setw(2)<<count<<"�� ����ġ�� �Է��Ͻÿ� : ";
		cin>>i;
		cin>>j;
		cin>>W[(n+1)*i + j];
		if( i==0 && j==0 && W[(n+1)*i + j]==0)
			break;
		count++;
	}

	// Dijkstra �˰��� �Ŀ� ���� F ���� �� �����Ҵ�
	set_of_Edges F = new Edge[n];

	// Dijkstra �˰��� ����
	dijkstra(n, W, F);
	
	// Dijkstra �˰������� ���� F ���
	cout<<endl<<"���� F"<<endl;
	for(int i=1; i<n; i++)
	{
		cout<<setw(2)<<F[i].from<<" -> "<<setw(2)<<F[i].to<<" = "<<setw(2)<<F[i].weight<<endl;
	}
	
	// ����� ���� ���� ����
	delete[] W;
	delete[] F;
	W = NULL;
	F = NULL;

	system("pause");
}

// Dijkstra �˰��� �Լ�
void dijkstra(int n, const number* W, set_of_Edges &F)
{
	index i, vnear;
	Edge e;
	index* touch = new index[n+1];
	number* length = new number[n+1];
//	F = NULL;	���� �Ҵ� �ÿ� �ڵ����� ������ ������ ������ ����

	// touch �� length�迭 �ʱ�ȭ
	for(i=2; i<=n; i++)
	{
		touch[i] = 1;
		length[i] = W[(n+1)*1 + i];
	}

	index count = 1;
	while (count < n)
	{
		// length�� �ʱ�ȭ ã�� �Ŀ� min, vnear�� �ʱ�ȭ ����
		int min = BIGNUM;
		for(i=2; i<=n ; i++)
		{
			if(0 <= length[i] && length[i] <= min)
			{
				min = length[i];
				vnear = i;
			}
		}

		// �� for������ ã�� Edge�� F �迭�� �ִ´�.
		e.from = touch[vnear];
		e.to = vnear;
		e.weight = W[ (n+1)*touch[vnear] + vnear];
		F[count] = e;

		// �߰��� ��带 �̿��Ͽ� �� ª�� ���� �ִٸ� length, touch�� ����
		for(i=2; i<=n; i++)
		{
			if( (length[vnear] + W[(n+1)*vnear + i]) < length[i] )
			{
				length[i] = length[vnear] + W[(n+1)*vnear + i];
				touch[i] = vnear;
			}
		}
		length[vnear] = -1;		// F�迭�� �߰� �Ϸ��� ���� -1�� �ʱ�ȭ
		count++;
	}
}