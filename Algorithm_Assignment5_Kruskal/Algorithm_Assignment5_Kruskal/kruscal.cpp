/*
#include <iostream>
#include <stdlib.h>
#include <Windows.h>

using std::cin;
using std::cout;
using std::endl;

typedef int index; 
typedef index set_pointer; 

struct nodetype
{ 
	index parent;   
	int depth; 
}; 

struct edge
{
	int w;
	int a;
	int b;
};

typedef edge* set_of_edges;
typedef nodetype* universe;
universe U;

void makeset(index);
set_pointer find(index);
void merge(set_pointer, set_pointer);
bool equal(set_pointer, set_pointer); 
void initial(int);
void kruskal(int, int, set_of_edges, set_of_edges&);

void main()
{
	int n;
	cout<<"Node의 갯수를 입력하시오 : ";
	cin>>n;
	cout<<endl;

	int m;
	cout<<"Edge의 총 갯수를 입력하시오 : ";
	cin>>m;
	cout<<endl;

	U = new nodetype[n+1];
}

void makeset(index i)
{ 
	U[i].parent = i;
	U[i].depth = 0; 
} 

set_pointer find(index i)
{   
	index j;
	j = i; 
	while(U[j].parent != j) 
		j=U[j].parent;    
	return j;   
} 

void merge(set_pointer p, set_pointer q)
{ 
	if(U[p].depth == U[q].depth) 
	{ 
		U[p].depth =+1;
		U[q].parent =p;
	} 
	else if(U[p].depth < U[q].depth) 
		U[p].parent =q; 
	else 
		U[q].parent = p; 
}

bool equal(set_pointer p, set_pointer q) 
{ 
	if (p == q) 
		return TRUE;    
	else 
		return FALSE; 
} 

void initial(int n)
{ 
	index i; 
	for(i=1; i<=n; i++) 
		makeset(i);
}

void kruskal(int, int, set_of_edges, set_of_edges&)
{
	index i, j;
	set_pointer p, q;
	edge e;

}

*/