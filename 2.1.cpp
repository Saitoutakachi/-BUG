#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <time.h>
#include <sys/timeb.h>
#include <string.h>
#include <iostream>
using namespace std;
// 序列存储结构定义
typedef struct RedType
{
    int key; // 待排序序列关键字项
} RedType;
typedef struct SqList
{
    RedType *r; // 存储所有的数据元素，0号存储单元用作监视哨
    int Length; // 待排序序列的长度
} SqList;
// 生成的长度为sqListLen的随机整数序列
SqList *CreateRandomSqList(int sqListLen)
{
    SqList *sq;
    int i;
    // 分配存储空间
    sq = new SqList;
    // 输入序列长度
    sq->Length = sqListLen;
    // 给序列每一个元素分配存储空间
    sq->r = new RedType[sq->Length + 1];
    // 生成随机序列
    srand((unsigned)(time(NULL)));
    for (i = 1; i <= sq->Length; i++)
    {
        sq->r[i].key = int(rand());
    }
    // 返回序列起始地址
    return sq;
}
int qkpass(SqList *&L, int s, int t) // *R[s..t]范围以R[s]为支点进行一趟快排，返回一趟快排结束后支点元素的下标
{
    int i, j, key;
    RedType pivot;
    pivot = L->r[s];
    key = L->r[s].key; // 保存支点
    i = s;
    j = t;
    while (i < j)
    { // 从后向前扫描
        while (i < j && L->r[j].key >= key)
        {
            j--;
        }
        // 以上循环结束后R[j+1..t]范围均大于或等于支点
        L->r[i] = L->r[j]; //将原R[j]放到支点位置
        // R[j]成为新的支点位置, 但支点实际并未存入R[j]
        // 从前后向扫描
        while (i < j && L->r[i].key <= key)
        {
            i++;
        }
        // 以上循环结束后R[s..i-1]范围均小于或等于支点
        L->r[j] = L->r[i]; // 将原R[i]放到支点位置
                           // R[i]成为新的支点位置, 但支点实际并未存入R[i]
    }
    L->r[i] = pivot; // 实际放入支点
    return i;        // 返回支点下标
}
// 快速排序算法
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
// 插入排序算法
void InsertSort(SqList* L)
{
	int i,j;
	//从第二个元素开始，将后面的元素插入到前面的有序序列
	for(i=2;i<=L->Length;i++)
	{
		//如果后面元素的关键字小于前面的有序序列
		if(L->r[i].key<L->r[i-1].key)
		{
			//赋值为监视哨
			L->r[0]=L->r[i];
			//元素后移
			for(j=i-1;L->r[0].key<L->r[j].key;--j)
			{
				L->r[j+1]=L->r[j];
			}
			//实现元素插入
			L->r[j+1]=L->r[0];
		}
	}
	return;
}
int main()
{
    // 定义待排序的随机序列
	SqList* L;
	// 定义算法执行前和执行后的系统时间
	struct __timeb64 stime,etime;
	// 定义算法执行时间秒和毫秒
	long int rmtime,rstime;
    char ch[20];
    FILE* fp;
    // 打开结果存储文件
    fp=fopen("F:\\Code\\CCode\\Arithmetic\\exp\\Curv.csv","w");
    // 循环调用序列生成和排序算法部分代码
    for(int i=1000;i<=100000;i=i+1000)
    {
        itoa(i,ch,10);
        strcat(ch,",");
        // 将横坐标值转换后写入文件
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
