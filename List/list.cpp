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
	pHead = create_list();//创建一个非循环单链表，把它首地址赋给pHead
	sort_list(pHead);
	traverse_list(pHead);
	//insert_list(pHead, 3, 100);
	
	delete_list(pHead, 3, &val);
	traverse_list(pHead);
	printf("链表长度是%d\n", length_list(pHead));
	return 0;
}

PNODE create_list()
{
	int len;//用来存放有效节点的个数
	int val;//临时存放用户输入节点的值
	//分配了一个不存放有效数据的头节点
	PNODE pHead = (PNODE)malloc(sizeof(Node));
	if (pHead==NULL)
	{
		printf("分配失败，程序终止\n");
		exit(-1);
	}
	PNODE pTail = pHead;
	pTail->pNext = NULL;
	printf("请输入你需要生成的链表节点的个数:len = ");
	scanf("%d", &len);
	for (int i = 0; i < len; i++)
	{
		printf("请输入第%d个节点的值:", i + 1);
		scanf("%d", &val);
		PNODE pNew = (PNODE)malloc(sizeof(Node));
		if (pNew == NULL)
		{
			printf("分配失败，程序终止\n");
			exit(-1);
		}
		pNew->data = val;
		pTail->pNext = pNew;//尾节点的指针域指向新节点(新节点挂在尾节点后)
		pNew->pNext = NULL;//新节点的指针域为null
		pTail = pNew;//把新节点地址赋给尾节点的地址(尾节点向后移动一位，即新节点为尾节点)
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
	int i = 0;//i是链表中的位置(类似于数组下标)
	PNODE p = pHead;
	//通过此while循环让p指向pos位置的节点
	while (p!=NULL&&i<pos-1)
	{
		p = p->pNext;
		i++;
	}
	//若该节点的位置(i)大于pos-1或指针为null，则返回false
	if (i > pos - 1 || p == NULL)	return false;
	//申请新节点
	PNODE pNew = (PNODE)malloc(sizeof(Node));
	if (pNew==NULL)
	{
		printf("动态分配内存失败\n");
		exit(-1);
	}
	pNew->data = val;//把插入的值赋给新节点的数据域
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
