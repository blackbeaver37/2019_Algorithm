#include <iostream>
#include <stdlib.h>
#include <Windows.h>

using std::cin;
using std::cout;
using std::endl;

// edge�� ������ ������ ����ü
struct edge
{
	int w;		// ����ġ ����
	int a;		// ��� ��� ����
	int b;		// ���� ��� ����
};

typedef int index;
typedef index set_pointer;
typedef edge* set_of_edges;

// node�� ������ ������ ����ü
struct nodetype
{
	index parent;
	int depth;
};

nodetype* U;	// �Է� ���� ��ü node�� ������ �迭

void kruskal(int, int, set_of_edges, set_of_edges);	// Kruskal�˰��� �Լ�
int cmpW(const void*, const void*);					// qsort���� ���� ���Լ�
void makeset(index);								// �κ������� ����� �Լ�
set_pointer find(index);							// index�� ���Ե� ������ �ּҸ� ��ȯ�ϴ� �Լ�
void merge(set_pointer p, set_pointer q);			// �� ���� p�� q�� �պ��ϴ� �Լ�
bool equal(set_pointer, set_pointer);				// �� ���� p�� q�� ���� ������ ����Ű������ ��ȯ�ϴ� �Լ�
void initial(int);									// int���� ���μ� �κ������� �ʱ�ȭ �ϴ� �Լ�

void main()
{
	// �Է¹��� node�� ������ �Է¹޴´�.
	int n;
	cout<<"Node�� ������ �Է��Ͻÿ� : ";
	cin>>n;
	cout<<endl;

	// �̾ �Է¹��� egde�� �� ������ �Է¹޴´�.
	int m;
	cout<<"Edge�� �� ������ �Է��Ͻÿ� : ";
	cin>>m;
	cout<<endl;

	// �Է¹��� ���� ���� ������ �迭 �ʱ�ȭ (�����, �迭�� 0���� ������� �ʰ� 1~n���� ����Ѵ�.)
	U = new nodetype[n+1];
	set_of_edges E = new edge[m+1];
	set_of_edges F = new edge[n];

	// �� ���� ���� ����ġ���� �Է¹޴´�.
	int mcount = 1;				// �Է¹��� ����ġ�� ī��Ʈ�� ����
	bool exitILoop = false;		// for�� �����
	cout<<"����ġ�� �Է��Ͻÿ�.(������ 0 �Է�)"<<endl;
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

				// ����ġ�� ��� �Է��� �Ϸ�Ǿ����� Loop Ż��
				if(mcount == m+1)
				{
					exitILoop = true;
					break;
				}
			}
			if(exitILoop)
				break;
		}

		// ���� ������ �����µ� ����ġ�� ��� �Էµ��� �ʾ����� �޽��� ����� ���α׷� ����
		if(mcount<m+1)
		{
			cout<<endl<<"�Է��� ���� ���� �ʽ��ϴ�."<<endl;
			Sleep(2000);
			exit(0);
		}
	}

	// �Է¹��� ����ġ ���� ���
	cout<<endl<<"�Է¹��� ��� ����ġ �� : "<<endl;
	for(int i=1; i<m+1; i++)
	{
		cout<<E[i].a<<" -> "<<E[i].b<<" = "<<E[i].w<<endl;
	}

	// Kruskal�˰��� ����
	kruskal(n, m, E, F);

	cout<<endl<<"Kruskal�˰������� ���� �ּҺ�����Ʈ�� : "<<endl;
	for(int i=1; i<n; i++)
	{
		cout<<F[i].a<<" -> "<<F[i].b<<" = "<<F[i].w<<endl;
	}

//cout<<endl<<"U : "<<endl;
//for(int i=1; i<=n; i++)
//{
//	cout<<i<<"���� parent = "<<U[i].parent<<", depth = "<<U[i].depth<<endl;
//}


	// ����� ���� ���� ���� �� �ʱ�ȭ
	delete[] U;
	delete[] E;
	delete[] F;
	U = NULL;
	E = NULL;
	F = NULL;

	system("pause");
}

// Kruskal�˰��� �Լ�
void kruskal(int n, int m, set_of_edges E, set_of_edges F)
{
	index i,j;
	set_pointer p,q;
	edge e;

	qsort(E, m+1, sizeof(edge), cmpW);	// QuickSort ���
//cout<<endl<<"==================quicksort �Ϸ�=================="<<endl;
//for(int i=1; i<m+1; i++)
//{
//	cout<<E[i].a<<" -> "<<E[i].b<<" = "<<E[i].w<<endl;
//}
	// F = 0, ���� �Ҵ�������� �ڵ����� ���������� �ʱ�ȭ �ǹǷ� ����
	initial(n);

	// �ּҺ�����Ʈ�� ã�� ����
	index ecount = 1;		// E������ ���Ҹ� ī��Ʈ �� ����
	index fcount = 1;		// F������ ���Ҹ� ī��Ʈ �� ����
//cout<<endl<<"==================While�� ����=================="<<endl;
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
//cout<<"if�� ���� (p != q)"<<endl;
			merge(p,q);
			F[fcount] = e;
//cout<<"merge(p,q) ����, F[fcount] = e, w = "<<e.w<<", i = "<<i<<", j = "<<j<<endl;
			if(++fcount == n)
				break;
		}
//cout<<endl;
		ecount++;
//cout<<endl<<"==================While�� �Ϸ�=================="<<endl;
	}
}

// qsort���� ���� ���Լ�
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

// �κ������� ����� �Լ�
void makeset(index i)
{ 
	U[i].parent = i;
	U[i].depth = 0; 
//cout<<endl<<"==================makeset "<<i<<"�� �Ϸ�=================="<<endl;
//cout<<"U["<<i<<"].parent = "<<U[i].parent<<", U["<<i<<"].depth = "<<U[i].depth<<endl;
} 

// index�� ���Ե� ������ �ּҸ� ��ȯ�ϴ� �Լ�
set_pointer find(index i)
{   
	index j;
	j = i; 
	while(U[j].parent != j) 
		j=U[j].parent;    
	return j;   
} 

// �� ���� p�� q�� �պ��ϴ� �Լ�
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

// �� ���� p�� q�� ���� ������ ����Ű������ ��ȯ�ϴ� �Լ�
bool equal(set_pointer p, set_pointer q) 
{ 
	if (p == q) 
		return TRUE;    
	else 
		return FALSE; 
} 

// int���� ���μ� �κ������� �ʱ�ȭ �ϴ� �Լ�
void initial(int n) 
{ 
//cout<<endl<<"==================Initial ����=================="<<endl;
	index i; 
	for(i=1; i<=n; i++) 
		makeset(i);
//cout<<endl<<"==================Initial �Ϸ�=================="<<endl;
}
