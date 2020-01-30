#include <stdio.h>
#include <stdlib.h>

//结构体中存放三个数据
//1.队列的首地址
//2.队首的数组下标
//3.队尾的数组下标
typedef struct Queue
{
	int *pBase;
	int front;
	int rear;
}QUEUE;

//传入队列的首地址
//对队列进行初始化
//即初始化一个无有效元素元素的数组
void init(QUEUE *pQ);
//参数是队列的首地址和要排队的元素值
//排队成功则返回true,若循环队列已满则返回false
bool en_queue(QUEUE *pQ, int val);
//传入队列的首地址
//遍历输出队列
//顺序为从队首往队尾
void traverse_queue(QUEUE *pQ);
bool full_queue(QUEUE *pQ);
bool empty_queue(QUEUE *pQ);
//传入队列首地址和一个变量的地址
//出队成功则返回true,同时获得出队元素的值
//出队的一定是队首元素
//否则返回false
bool out_queue(QUEUE *pQ, int *pVal);

int main()
{
	QUEUE Q;
	int val;
	init(&Q);
	en_queue(&Q, 1);
	en_queue(&Q, 2);
	en_queue(&Q, 3);
	en_queue(&Q, 4);
	en_queue(&Q, 5);
	en_queue(&Q, 6);
	en_queue(&Q, 7);
	en_queue(&Q, 8);
	traverse_queue(&Q);
	printf("\n");
	out_queue(&Q, &val);
	traverse_queue(&Q);

	return 0;
}

void init(QUEUE * pQ)
{
	//声明了一个长度为6的数组
	//(数组长度可随需求而变)
	pQ->pBase = (int *)malloc(sizeof(int) * 6);
	//初始化的时候默认队尾和队首都是0
	pQ->front = 0;
	pQ->rear = 0;
}

bool en_queue(QUEUE * pQ, int val)
{
	if (full_queue(pQ))
	{
		return false;
	}
	else
	{
		//例如存在数组a
		//a就是数组的首地址
		//a+i和a[i]的意义都代表第i个元素
		pQ->pBase[pQ->rear] = val;
		//把val的值赋给队尾的前一个元素
		//循环队列的特点:
		//最后一个元素与第一个元素相邻
		//可认为是一个环形

		//这个赋值运算可以让rear在入队后递增一位
		//若rear是最后一个位置便到0的位置
		pQ->rear = (pQ->rear + 1) % 6;
		return true;
	}
}

void traverse_queue(QUEUE * pQ)
{
	//先用i存放队首的位置
	int i = pQ->front;
	//用while循环遍历队列
	while (i!=pQ->rear)
	{
		printf("%d ", pQ->pBase[i]);
		i = (i + 1) % 6;
	}
}

//判断循环队列是否为满的方法有二
//1.引入一个变量length,记录队列的长度
//2.让数组中一个位置空出来
//通常使用方法二
bool full_queue(QUEUE * pQ)
{
	//把循环队列的数组当成首尾相接的环
	//当rear从后面与front相邻的时候队列为满
	//可用表达式(pQ->rear+1)%数组长度==pQ->front
	//判断是否相邻
	if ((pQ->rear+1)%6==pQ->front)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool empty_queue(QUEUE * pQ)
{
	//如果队尾和队首相同则队列为空
	if (pQ->front == pQ->rear)
		return false;
	else
		return false;
}

bool out_queue(QUEUE * pQ, int * pVal)
{
	//如果队列为空则返回false
	if (empty_queue(pQ))
	{
		return false;
	}
	else
	{
		//用val存放队首的值
		*pVal = pQ->pBase[pQ->front];
		//出队后front+1，若在数组尾则跑到数组头
		pQ->front = (pQ->front + 1) % 6;
		return true;
	}
}
