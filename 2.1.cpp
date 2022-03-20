#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <time.h>
#include <sys/timeb.h>
#include <string.h>
#include <iostream>
using namespace std;
// ���д洢�ṹ����
typedef struct RedType
{
    int key; // ���������йؼ�����
} RedType;
typedef struct SqList
{
    RedType *r; // �洢���е�����Ԫ�أ�0�Ŵ洢��Ԫ����������
    int Length; // ���������еĳ���
} SqList;
// ���ɵĳ���ΪsqListLen�������������
SqList *CreateRandomSqList(int sqListLen)
{
    SqList *sq;
    int i;
    // ����洢�ռ�
    sq = new SqList;
    // �������г���
    sq->Length = sqListLen;
    // ������ÿһ��Ԫ�ط���洢�ռ�
    sq->r = new RedType[sq->Length + 1];
    // �����������
    srand((unsigned)(time(NULL)));
    for (i = 1; i <= sq->Length; i++)
    {
        sq->r[i].key = int(rand());
    }
    // ����������ʼ��ַ
    return sq;
}
int qkpass(SqList *&L, int s, int t) // *R[s..t]��Χ��R[s]Ϊ֧�����һ�˿��ţ�����һ�˿��Ž�����֧��Ԫ�ص��±�
{
    int i, j, key;
    RedType pivot;
    pivot = L->r[s];
    key = L->r[s].key; // ����֧��
    i = s;
    j = t;
    while (i < j)
    { // �Ӻ���ǰɨ��
        while (i < j && L->r[j].key >= key)
        {
            j--;
        }
        // ����ѭ��������R[j+1..t]��Χ�����ڻ����֧��
        L->r[i] = L->r[j]; //��ԭR[j]�ŵ�֧��λ��
        // R[j]��Ϊ�µ�֧��λ��, ��֧��ʵ�ʲ�δ����R[j]
        // ��ǰ����ɨ��
        while (i < j && L->r[i].key <= key)
        {
            i++;
        }
        // ����ѭ��������R[s..i-1]��Χ��С�ڻ����֧��
        L->r[j] = L->r[i]; // ��ԭR[i]�ŵ�֧��λ��
                           // R[i]��Ϊ�µ�֧��λ��, ��֧��ʵ�ʲ�δ����R[i]
    }
    L->r[i] = pivot; // ʵ�ʷ���֧��
    return i;        // ����֧���±�
}
// ���������㷨
void QuickSort(SqList *&L, int s, int t)
{
    int i;
    if (s < t)
    {
        i = qkpass(L, s, t);
        QuickSort(L, s, i - 1);
        QuickSort(L, i + 1, t);
    }
}
// ���������㷨
void InsertSort(SqList* L)
{
	int i,j;
	//�ӵڶ���Ԫ�ؿ�ʼ���������Ԫ�ز��뵽ǰ�����������
	for(i=2;i<=L->Length;i++)
	{
		//�������Ԫ�صĹؼ���С��ǰ�����������
		if(L->r[i].key<L->r[i-1].key)
		{
			//��ֵΪ������
			L->r[0]=L->r[i];
			//Ԫ�غ���
			for(j=i-1;L->r[0].key<L->r[j].key;--j)
			{
				L->r[j+1]=L->r[j];
			}
			//ʵ��Ԫ�ز���
			L->r[j+1]=L->r[0];
		}
	}
	return;
}
int main()
{
    // �����������������
	SqList* L;
	// �����㷨ִ��ǰ��ִ�к��ϵͳʱ��
	struct __timeb64 stime,etime;
	// �����㷨ִ��ʱ����ͺ���
	long int rmtime,rstime;
    char ch[20];
    FILE* fp;
    // �򿪽���洢�ļ�
    fp=fopen("F:\\Code\\CCode\\Arithmetic\\exp\\Curv.csv","w");
    // ѭ�������������ɺ������㷨���ִ���
    for(int i=1000;i<=100000;i=i+1000)
    {
        itoa(i,ch,10);
        strcat(ch,",");
        // ��������ֵת����д���ļ�
        fprintf(fp,ch,sizeof(char),strlen(ch));
    }
    // for(int i=1000;i<=100000;i=i+1000)
    // {
    // 	fprintf(fp,"%d,",i);
	// }
    fprintf(fp,"\n");
    for(int i=1000;i<=100000;i=i+1000)
    {
        L=CreateRandomSqList(i);
        _ftime64(&stime);
        QuickSort(L,1,i);
		_ftime64(&etime);
    	delete [] L->r;
	    delete L;
		rstime=etime.time-stime.time;
	    rmtime=rstime*1000;
	    rmtime+=etime.millitm-stime.millitm;
	    fprintf(fp,"%d,",rmtime);
    }
    fprintf(fp,"\n");
    for(int i=1000;i<=100000;i=i+1000)
    {
        L=CreateRandomSqList(i);
        _ftime64(&stime);
        InsertSort(L);
		_ftime64(&etime);
    	delete [] L->r;
	    delete L;
		rstime=etime.time-stime.time;
	    rmtime=rstime*1000;
	    rmtime+=etime.millitm-stime.millitm;
	    fprintf(fp,"%d,",rmtime);
    }
    fclose(fp);
    return 1;
}
