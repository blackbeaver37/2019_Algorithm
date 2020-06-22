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
	// ��� �� ���� ������ �Է� �޴´�.
	cout<<"����� ������ �Է��Ͻÿ� : ";
	cin>>n;
	cout<<endl<<"���� ������ �Է��Ͻÿ� : ";
	cin>>m;
	cout<<endl;

	// W�迭 �ʱ�ȭ
	W = new bool[(n+1)*(n+1)];
	for(index i = 0; i<(n+1)*(n+1); i++)
		W[i] = false;

	// W�迭�� ���� �Է� �޴´�.
	cout<<"��θ� �Է��Ͻÿ� (��� ��� �������� �Է�, �� �Է� �ϸ� 0 0 �Է�) : "<<endl;
	int count = 1;
	index i,j;
	while(count != 0)
	{
		cout<<setw(2)<<count<<"��° ��θ� �Է��Ͻÿ� : ";
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

	// vcolor �����Ҵ�
	vcolor = new int[n+1];

	// ���ü��� ���� �߰��� �ڵ��Դϴ�!!
	cout<<endl;
	cout<<setw(14)<<"";
	for(index i = 1; i<=n; i++)
		cout<<setw(2)<<i;
	cout<<endl;

	// �˰��� �Լ� ����
	m_coloring(0);
	cout<<endl;

	// ����� ���� ���� ����
	delete[] W;
	delete[] vcolor;
	W = NULL;
	vcolor = NULL;

	system("pause");
}

// Graph Coloring �˰��� �Լ�
void m_coloring (index i)
{
	int color;

	// ���� �����ϴٸ�
	if(promising(i))
	{
		if(i==n)
		{
			// ������ ������ �񱳰� �����ٸ�
			static int count=1;
			cout<<setw(2)<<count<<"��° ��� : ";
			for(index j=1; j<=n; j++)
				cout<<setw(2)<<vcolor[j];
			cout<<endl;
			count++;
		}
		else
		{
			// ���� �񱳰� ������ �ʾҴٸ�
			for(color=1; color<=m; color++)
			{
				vcolor[i+1] = color;
				m_coloring(i+1);
			}
		}
	}
}


// �������� �Ǵ��ϴ� �Լ�
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