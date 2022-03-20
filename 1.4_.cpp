#include <iostream>
using namespace std;

#define M 20 //图的最大结点数
#define n 100
// int N; // 目标图的结点数
// int e; // 目标图的有向边数

typedef struct node
{
	int j;			  //弧指向的端点下标
	struct node *nextarc; // 指向下一个弧的指针
} ArcNode;				  // 定义表结点

typedef struct
{
	int i;		   // 弧顶点下标
	char data[20];	   // 顶点的数据
	ArcNode *firstarc; // 指向下一个弧的指针
} HNode;			   // 定义头节点

typedef struct
{
	HNode H[M]; // 头节点形成数组
	int N, e;	// 实际顶点数和弧的数目
} ALGraph;		// 定义有向图的邻接表




void crtGraph(ALGraph &G)
{
	int i, j, k;
	cout << "请输入图的顶点数和弧数:" << endl;
	cin >> G.N >> G.e;
	for (i = 0; i < G.N; i++) // 初始化顶点
	{
		// cout << "请输入该节点序号" << i+1 << "的内容:" << endl;
		// cin >> G.H[i].data;
		G.H[i].i = i;
		G.H[i].firstarc = NULL;
	}
	for (k = 0; k < G.e; k++)// 建立e个表结点
	{
		cout << "请输入条弧的起始点和终止点:";
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
	int *indegree = new int[G.N]; // 创建indegree数组
	int i, count = 0;
	ArcNode *p;
	struct
	{
		int s[n];
		int top;
	} stack; // 建立栈，s数组存储入度为0的点
	for (i = 0; i < G.N; i++)
		indegree[i] = 0; // 初始化indegree数组
	for (i = 0; i < G.N; i++)
		for (p = G.H[i].firstarc; p!=NULL; p = p->nextarc)
			indegree[p->j]++;
			
	for (i = 0, stack.top = -1; i < G.N; i++)
		if(indegree[i]==0)
		{
			stack.top++;
			stack.s[stack.top] = i;
		}// 入栈入度为0的结点
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
