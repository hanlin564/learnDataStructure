#include <stdio.h>
#include <stdlib.h>

//�ṹ���д����������
//1.���е��׵�ַ
//2.���׵������±�
//3.��β�������±�
typedef struct Queue
{
	int *pBase;
	int front;
	int rear;
}QUEUE;

//������е��׵�ַ
//�Զ��н��г�ʼ��
//����ʼ��һ������ЧԪ��Ԫ�ص�����
void init(QUEUE *pQ);
//�����Ƕ��е��׵�ַ��Ҫ�Ŷӵ�Ԫ��ֵ
//�Ŷӳɹ��򷵻�true,��ѭ�����������򷵻�false
bool en_queue(QUEUE *pQ, int val);
//������е��׵�ַ
//�����������
//˳��Ϊ�Ӷ�������β
void traverse_queue(QUEUE *pQ);
bool full_queue(QUEUE *pQ);
bool empty_queue(QUEUE *pQ);
//��������׵�ַ��һ�������ĵ�ַ
//���ӳɹ��򷵻�true,ͬʱ��ó���Ԫ�ص�ֵ
//���ӵ�һ���Ƕ���Ԫ��
//���򷵻�false
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
	//������һ������Ϊ6������
	//(���鳤�ȿ����������)
	pQ->pBase = (int *)malloc(sizeof(int) * 6);
	//��ʼ����ʱ��Ĭ�϶�β�Ͷ��׶���0
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
		//�����������a
		//a����������׵�ַ
		//a+i��a[i]�����嶼�����i��Ԫ��
		pQ->pBase[pQ->rear] = val;
		//��val��ֵ������β��ǰһ��Ԫ��
		//ѭ�����е��ص�:
		//���һ��Ԫ�����һ��Ԫ������
		//����Ϊ��һ������

		//�����ֵ���������rear����Ӻ����һλ
		//��rear�����һ��λ�ñ㵽0��λ��
		pQ->rear = (pQ->rear + 1) % 6;
		return true;
	}
}

void traverse_queue(QUEUE * pQ)
{
	//����i��Ŷ��׵�λ��
	int i = pQ->front;
	//��whileѭ����������
	while (i!=pQ->rear)
	{
		printf("%d ", pQ->pBase[i]);
		i = (i + 1) % 6;
	}
}

//�ж�ѭ�������Ƿ�Ϊ���ķ����ж�
//1.����һ������length,��¼���еĳ���
//2.��������һ��λ�ÿճ���
//ͨ��ʹ�÷�����
bool full_queue(QUEUE * pQ)
{
	//��ѭ�����е����鵱����β��ӵĻ�
	//��rear�Ӻ�����front���ڵ�ʱ�����Ϊ��
	//���ñ��ʽ(pQ->rear+1)%���鳤��==pQ->front
	//�ж��Ƿ�����
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
	//�����β�Ͷ�����ͬ�����Ϊ��
	if (pQ->front == pQ->rear)
		return false;
	else
		return false;
}

bool out_queue(QUEUE * pQ, int * pVal)
{
	//�������Ϊ���򷵻�false
	if (empty_queue(pQ))
	{
		return false;
	}
	else
	{
		//��val��Ŷ��׵�ֵ
		*pVal = pQ->pBase[pQ->front];
		//���Ӻ�front+1����������β���ܵ�����ͷ
		pQ->front = (pQ->front + 1) % 6;
		return true;
	}
}
