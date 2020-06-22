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
	// ������ ������ �Է¹޴´�.
	cout<<"������ ������ �Է��Ͻÿ� : ";
	cin>>n;
	cout<<endl;

	// ���� �� �ǰ� �����Ҵ� �� �ʱ�ȭ
	W = new bool[(n+1)*(n+1)];
	for(index i=0; i<(n+1)*(n+1); i++)
		W[i] = false;

	// ���� �� �ǰ� �����Ҵ� �� �ʱ�ȭ
	vindex = new index[n];
	vindex[0] = 1;

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

	// Hamiltonian �˰��� �Լ� ����
	hamiltonian(0);
	cout<<endl;

	// ���� ����
	delete[] W;
	delete[] vindex;
	W = NULL;
	vindex = NULL;

	system("pause");
}

// Hmiltonian �˰��� �Լ�
void hamiltonian(index i)
{
	index j;

	// �������� �Ǵ�
	if(promising(i))
	{
		// ���� ��θ� �� ���Ҵٸ�
		if(i == n-1)
		{
			static int count = 1;
			cout<<endl<<setw(2)<<count<<"�� ��� : ";
			for(j=0; j<n; j++)
				cout<<setw(2)<<vindex[j];
			cout<<endl;
			count++;
		}
		// ���� ��ΰ� �����ִٸ�
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

// �������� �Ǵ��ϴ� �Լ�
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