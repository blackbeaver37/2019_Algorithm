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

size n;				// ������ ���� ������ ����
int* w;				// �� ������ weight�� ������ �迭
int W;				// ��ǥ ��
string* include;	// YES NO ���� ������ ���ڿ� �迭

void sum_of_subsets (index i, int weight, int total);
bool promising (index i, int weight, int total);

void main()
{
	// ������ ������ �Է� �޴´�
	cout<<"������ ���ҵ��� ������ �Է��Ͻÿ� : ";
	cin>>n;
	cout<<endl;

	w = new int[n+1];		// �Է¹��� n�� �̿� ���� �Ҵ�
	w[0] = 0;				// 1�� ~ n�� ���
	int total = 0;

	cout<<"���ĵ� ������ �Է��Ͻÿ�."<<endl;
	for(index i = 1; i<=n; i++)
	{
		cout<<setw(2)<<i<<"��° ���Ҹ� �Է��Ͻÿ� : ";
		cin>>w[i];
		total += w[i];		// �Է¹����鼭 total�� �ʱ�ȭ
	}
	cout<<endl;

	cout<<"������ �� ���� �Է��Ͻÿ� : ";
	cin>>W;
	cout<<endl;

	include = new string[n+1];
	int weight = 0;

	// �˰��� ��� ��½� ���ü��� ���� �߰��� �ڵ� �Դϴ�!
	cout<<setw(14)<<"";
	for(index i=1; i<=n; i++)
		cout<<setw(4)<<w[i];
	cout<<endl;

	// �˰��� ����
	sum_of_subsets(0, weight, total);

	cout<<endl;
	
	// ����� ���� ���� ����
	delete[] w;
	delete[] include;
	w = NULL;
	include = NULL;

	system("pause");
}

// Sum of Subsets �˰��� �Լ�
void sum_of_subsets (index i, int weight, int total)
{
	// �������� �Ǵ�
	if (promising(i, weight, total))
	{
		if (weight == W)
		{
			// ���ϴ� ���� ������ ��
			static int count = 1;
			cout<<setw(2)<<count<<"��° ��� : ";
			for(index j=1; j<=i; j++)
				cout<<setw(4)<<include[j];
			count++;
			cout<<endl;
		}
		else
		{
			// ���������� ���ϴ� ���� �ƴϸ� ��� Ž��
			include[i+1] = "YES";
			sum_of_subsets(i+1, weight + w[i+1], total - w[i+1]);
			include[i+1] = " NO";
			sum_of_subsets(i+1, weight, total - w[i+1]);
		}
	}
}

// �������� �Ǵ��ϴ� �Լ�
bool promising (index i, int weight, int total)
{
	return (weight + total >= W) && (weight == W || weight+w[i+1] <= W) ;
}