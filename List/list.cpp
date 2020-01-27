#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>

typedef struct Node
{
	int data;
	struct Node *pNext;
}NODE,*PNODE;

PNODE create_list();
void traverse_list(PNODE pHead);
bool is_empty(PNODE pHead);
int length_list(PNODE pHead);
bool insert_list(PNODE pHead, int pos, int val);
bool delete_list(PNODE pHead, int pos, int *pVal);
void sort_list(PNODE pHead);

int main(void)
{
	PNODE pHead = NULL;
	int val;
	pHead = create_list();//����һ����ѭ�������������׵�ַ����pHead
	sort_list(pHead);
	traverse_list(pHead);
	//insert_list(pHead, 3, 100);
	
	delete_list(pHead, 3, &val);
	traverse_list(pHead);
	printf("��������%d\n", length_list(pHead));
	return 0;
}

PNODE create_list()
{
	int len;//���������Ч�ڵ�ĸ���
	int val;//��ʱ����û�����ڵ��ֵ
	//������һ���������Ч���ݵ�ͷ�ڵ�
	PNODE pHead = (PNODE)malloc(sizeof(Node));
	if (pHead==NULL)
	{
		printf("����ʧ�ܣ�������ֹ\n");
		exit(-1);
	}
	PNODE pTail = pHead;
	pTail->pNext = NULL;
	printf("����������Ҫ���ɵ�����ڵ�ĸ���:len = ");
	scanf("%d", &len);
	for (int i = 0; i < len; i++)
	{
		printf("�������%d���ڵ��ֵ:", i + 1);
		scanf("%d", &val);
		PNODE pNew = (PNODE)malloc(sizeof(Node));
		if (pNew == NULL)
		{
			printf("����ʧ�ܣ�������ֹ\n");
			exit(-1);
		}
		pNew->data = val;
		pTail->pNext = pNew;//β�ڵ��ָ����ָ���½ڵ�(�½ڵ����β�ڵ��)
		pNew->pNext = NULL;//�½ڵ��ָ����Ϊnull
		pTail = pNew;//���½ڵ��ַ����β�ڵ�ĵ�ַ(β�ڵ�����ƶ�һλ�����½ڵ�Ϊβ�ڵ�)
	}
	return pHead;
}

void traverse_list(PNODE pHead)
{
	PNODE p = pHead->pNext;
	
	while (p!=NULL)
	{
		printf("%d ", p->data);
		p = p->pNext;
	}
	printf("\n");
}

bool is_empty(PNODE pHead)
{
	if (pHead->pNext == NULL)
		return true;
	else
		return false;
}

int length_list(PNODE pHead)
{
	PNODE p = pHead->pNext;
	int len = 0;
	while (p != NULL)
	{
		len++;
		p = p->pNext;
	}
	return len;
}

bool insert_list(PNODE pHead, int pos, int val)
{
	int i = 0;//i�������е�λ��(�����������±�)
	PNODE p = pHead;
	//ͨ����whileѭ����pָ��posλ�õĽڵ�
	while (p!=NULL&&i<pos-1)
	{
		p = p->pNext;
		i++;
	}
	//���ýڵ��λ��(i)����pos-1��ָ��Ϊnull���򷵻�false
	if (i > pos - 1 || p == NULL)	return false;
	//�����½ڵ�
	PNODE pNew = (PNODE)malloc(sizeof(Node));
	if (pNew==NULL)
	{
		printf("��̬�����ڴ�ʧ��\n");
		exit(-1);
	}
	pNew->data = val;//�Ѳ����ֵ�����½ڵ��������
	pNew->pNext = p->pNext;
	p->pNext = pNew;
	return true;
}

bool delete_list(PNODE pHead, int pos, int * pVal)
{
	int i = 0;
	PNODE p = pHead;
	while (p->pNext != NULL && i < pos - 1)
	{
		p = p->pNext;
		i++;
	}
	if (i > pos - 1 || p->pNext == NULL)	return false;
	PNODE q = p->pNext;
	*pVal = q->data;
	p->pNext = q->pNext;
	free(q);
	q = NULL;
	return true;
}

void sort_list(PNODE pHead)
{
	PNODE p, q;
	for (p=pHead->pNext;p!=NULL;p=p->pNext)
	{
		for (q = p->pNext; q != NULL; q = q->pNext)
		{
			if (p->data>q->data)
			{
				int temp = p->data;
				p->data = q->data;
				q->data = temp;
			}
		}
	}
}
