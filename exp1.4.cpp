#include<stdio.h>
#include<stdlib.h>

#define m 100
#define n 6
#define e 8

typedef struct node1 {
	int info;
	int adjvertex;//这个域就是本节点在数组中的位置
	struct node1 *nextarc;
} glinklnode;//这个是在后面邻接的节点

typedef struct node2 {
	int vertexinfo;
	glinklnode *firstarc;
} glinkhnode;

//创建邻接链表
void createAdjlist(glinkhnode g[]) {
	int i,j,k;
	glinklnode *p;
	for(i=0; i<n; i++) {
		g[i].vertexinfo=i;
		g[i].firstarc=0;
	}//初始化每个节点在数组中的位置
	for(k=0; k<e; k++) {
		scanf("%d%d",&i,&j);//输入两个关联节点
		p=(glinklnode *)malloc(sizeof(glinklnode));
		p->adjvertex=j;
		p->nextarc=g[i].firstarc;//使用的插入方式建立，后来的更接近根节点
		g[i].firstarc=p;//第一个邻接点是p

	}
}

//拓扑排序函数
void toposort(glinkhnode g[]) {
	int i,v,w,sum=0, indegree[n];
	struct {
		int s[n];
		int top;
	} stack;//建立一个栈，栈中的s数组用来存入度为0的节点
	glinklnode *p;
	for (i=0; i<n; i++) indegree[i]=0;//初始化indegree数组，完全可以使用memset
	for (i=0; i<n; i++)
		for(p=g[i].firstarc; p!=0; p=p->nextarc)
			indegree[p->adjvertex]++;
	for(i=0,stack.top= -1; i<n; i++) if(indegree[i]==0) {
			stack.top++;
			stack.s[stack.top]=i;
		}//入栈入度为0的节点
	while(stack.top!= -1) {
		printf("%d\t",stack.s[stack.top]);
		sum=sum+1;
		v=stack.s[stack.top];
		stack.top=stack.top-1;
		p=g[v].firstarc;
		while (p!=0) {
			w=p->adjvertex;
			indegree[w]=indegree[w]-1;//入度值需要-1
			if (indegree[w]==0) {//如果它的入度等于0，就将这个节点也入栈
				stack.top=stack.top+1;
				stack.s[stack.top]=w;
			}
			p=p->nextarc;
		}
	}
	if(sum<n) printf("The AOV network has a cycle\n");//如果最后输出的节点个数少于总结点数，说明图中有回路
}

int main() {
	glinkhnode g[m];
	createAdjlist(g);
	toposort(g);
	return 0;
}
