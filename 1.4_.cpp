#include <iostream>
using namespace std;

#define M 20 //ͼ���������
#define n 100
// int N; // Ŀ��ͼ�Ľ����
// int e; // Ŀ��ͼ���������

typedef struct node
{
	int j;			  //��ָ��Ķ˵��±�
	struct node *nextarc; // ָ����һ������ָ��
} ArcNode;				  // �������

typedef struct
{
	int i;		   // �������±�
	char data[20];	   // ���������
	ArcNode *firstarc; // ָ����һ������ָ��
} HNode;			   // ����ͷ�ڵ�

typedef struct
{
	HNode H[M]; // ͷ�ڵ��γ�����
	int N, e;	// ʵ�ʶ������ͻ�����Ŀ
} ALGraph;		// ��������ͼ���ڽӱ�




void crtGraph(ALGraph &G)
{
	int i, j, k;
	cout << "������ͼ�Ķ������ͻ���:" << endl;
	cin >> G.N >> G.e;
	for (i = 0; i < G.N; i++) // ��ʼ������
	{
		// cout << "������ýڵ����" << i+1 << "������:" << endl;
		// cin >> G.H[i].data;
		G.H[i].i = i;
		G.H[i].firstarc = NULL;
	}
	for (k = 0; k < G.e; k++)// ����e������
	{
		cout << "��������������ʼ�����ֹ��:";
		cin >> i >> j;
		ArcNode *p, *pr, *q = new ArcNode;
		q->j = j;
		q->nextarc = NULL;
		pr = NULL;
		p = G.H[i].firstarc;
		while (p && p->j < j)
		{
			pr = p;
			p = p->nextarc;
		}
		if (pr == NULL)
		{
			q->nextarc = p;
			G.H[i].firstarc = q;
		}
		else
		{
			pr->nextarc = q;
			q->nextarc = p;
		}
	}
}

bool TopologicalSort(ALGraph G)
{
	int *indegree = new int[G.N]; // ����indegree����
	int i, count = 0;
	ArcNode *p;
	struct
	{
		int s[n];
		int top;
	} stack; // ����ջ��s����洢���Ϊ0�ĵ�
	for (i = 0; i < G.N; i++)
		indegree[i] = 0; // ��ʼ��indegree����
	for (i = 0; i < G.N; i++)
		for (p = G.H[i].firstarc; p!=NULL; p = p->nextarc)
			indegree[p->j]++;
			
	for (i = 0, stack.top = -1; i < G.N; i++)
		if(indegree[i]==0)
		{
			stack.top++;
			stack.s[stack.top] = i;
		}// ��ջ���Ϊ0�Ľ��
	while(stack.top!=-1)
	{
			cout << stack.s[stack.top] << endl;
			count++;
	}
}

int main()
{
	ALGraph G;
	crtGraph(G);
	return 1;
}
