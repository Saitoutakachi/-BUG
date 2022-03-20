#include<stdio.h>
#include<stdlib.h>

#define m 100
#define n 6
#define e 8

typedef struct node1 {
	int info;
	int adjvertex;//�������Ǳ��ڵ��������е�λ��
	struct node1 *nextarc;
} glinklnode;//������ں����ڽӵĽڵ�

typedef struct node2 {
	int vertexinfo;
	glinklnode *firstarc;
} glinkhnode;

//�����ڽ�����
void createAdjlist(glinkhnode g[]) {
	int i,j,k;
	glinklnode *p;
	for(i=0; i<n; i++) {
		g[i].vertexinfo=i;
		g[i].firstarc=0;
	}//��ʼ��ÿ���ڵ��������е�λ��
	for(k=0; k<e; k++) {
		scanf("%d%d",&i,&j);//�������������ڵ�
		p=(glinklnode *)malloc(sizeof(glinklnode));
		p->adjvertex=j;
		p->nextarc=g[i].firstarc;//ʹ�õĲ��뷽ʽ�����������ĸ��ӽ����ڵ�
		g[i].firstarc=p;//��һ���ڽӵ���p

	}
}

//����������
void toposort(glinkhnode g[]) {
	int i,v,w,sum=0, indegree[n];
	struct {
		int s[n];
		int top;
	} stack;//����һ��ջ��ջ�е�s�������������Ϊ0�Ľڵ�
	glinklnode *p;
	for (i=0; i<n; i++) indegree[i]=0;//��ʼ��indegree���飬��ȫ����ʹ��memset
	for (i=0; i<n; i++)
		for(p=g[i].firstarc; p!=0; p=p->nextarc)
			indegree[p->adjvertex]++;
	for(i=0,stack.top= -1; i<n; i++) if(indegree[i]==0) {
			stack.top++;
			stack.s[stack.top]=i;
		}//��ջ���Ϊ0�Ľڵ�
	while(stack.top!= -1) {
		printf("%d\t",stack.s[stack.top]);
		sum=sum+1;
		v=stack.s[stack.top];
		stack.top=stack.top-1;
		p=g[v].firstarc;
		while (p!=0) {
			w=p->adjvertex;
			indegree[w]=indegree[w]-1;//���ֵ��Ҫ-1
			if (indegree[w]==0) {//���������ȵ���0���ͽ�����ڵ�Ҳ��ջ
				stack.top=stack.top+1;
				stack.s[stack.top]=w;
			}
			p=p->nextarc;
		}
	}
	if(sum<n) printf("The AOV network has a cycle\n");//����������Ľڵ���������ܽ������˵��ͼ���л�·
}

int main() {
	glinkhnode g[m];
	createAdjlist(g);
	toposort(g);
	return 0;
}
