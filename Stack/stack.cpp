#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>

typedef struct Node
{
	int data;
	struct Node *pNext;
}NODE,*PNODE;

typedef struct Stack
{
	PNODE pTop;
	PNODE pBottom;
}STACK,*PSTACK;

/*
��ջ�ĵ�ַ���ݸ�init����(��ʱջ��ʵ�ʴ���)
init����ʵ����������һ�������ͷ�ڵ�
ʹpTop��pBottom��ָͬ��ͷ�ڵ�
��ʱջ��û�д����Ч����
*/
void init(PSTACK pS);
/*
��ջ��ѹ��ָ��ֵ
push��������һ��ջ�ĵ�ַ��һ����ѹ��ջ��ֵ��Ϊ����
*/
void push(PSTACK pS, int val);
//����ջ:��ջ����ջ��
void traverse(PSTACK pS);
bool pop(PSTACK pS, int *pVal);
bool empty(PSTACK pS);
void clear(PSTACK pS);

int main()
{
	STACK S;
	int val;
	init(&S);
	push(&S,1);
	push(&S,2);
	push(&S, 3);
	push(&S, 4);
	push(&S, 5);
	push(&S, 6);
	pop(&S, &val);
	traverse(&S);
	clear(&S);
	traverse(&S);

	return 0;
}

void init(PSTACK pS)
{
	//����һ��ͷ�ڵ���ڴ棬ʹpTopָ��ͷ�ڵ��ڴ���׵�ַ
	pS->pTop = (PNODE)malloc(sizeof(NODE));
	if (pS->pTop == NULL)
	{
		printf("��̬�ڴ����ʧ��\n");
		exit(-1);
	}
	else
	{
		//����ֻ��ͷ�ڵ㣬��ջ��ջ����ջβ��ָͬ��ͷ�ڵ�
		pS->pBottom = pS->pTop;
		//��ջ��ָ��Ϊnull
		//��̬ջ��ջ����Ӧ����ͷ
		//ջ�׶�Ӧ����β
		//ע��:ջ�е�����ͷ�ڵ�ָ��������β��һ����������ݵĽڵ�(ջ��)
		//�����е�ͷ�ڵ�ָ���������׽ڵ�ǰ�Ľڵ�
		//һ��������ĩ�ˣ�һ����������ǰ��
		pS->pTop->pNext = NULL;
		//?:����ò�ƿ�����ջ��ָ��Ϊnull������
		//pS->pBottom->pNext = NULL;
	}
	return;
}

void push(PSTACK pS, int val)
{
	PNODE pNew = (PNODE)malloc(sizeof(NODE));
	//ѹ��ֵ��ŵ��½ڵ���������
	pNew->data = val;
	//�½ڵ��ָ��������ջ���ĵ�ַ
	pNew->pNext = pS->pTop;
	//ջ��ָ��ָ���½ڵ�
	//ÿ��ѹջ������ջ��ָ���½ڵ�
	pS->pTop = pNew;
	return;
}

void traverse(PSTACK pS)
{
	//ָ��p���ջ����ַ
	PNODE p = pS->pTop;
	//��whileѭ�����ջ�е�ֵ(�Զ�����)
	while (p!=pS->pBottom)
	{
		printf("%d ", p->data);
		p = p->pNext;
	}
	printf("\n");
	return;
}

bool pop(PSTACK pS, int * pVal)
{
	if (empty(pS))
		return false;
	else
	{
		//��ָ��r��ʱ���ջ����ַ
		PNODE r = pS->pTop;
		//ͨ��ָ�����޸�val��ֵ���������Ի�õ���ֵ
		*pVal = r->data;
		//ջ��ָ��ָ���������һ��λ��
		pS->pTop = r->pNext;
		//free�����ͷŵ���ָ��rָ����ڴ�
		//r=null�Ǳ�������ָ��
		free(r);
		r = NULL;
		return true;
	}

}

bool empty(PSTACK pS)
{
	//���ջ��ָ�����ջ��ָ�룬��ջΪ��
	//(ֻ��ͷ�ڵ�)
	if (pS->pBottom == pS->pTop)
		return true;
	else
		return false;
}

void clear(PSTACK pS)
{
	if (empty(pS))
	{
		return;
	}
	else
	{
		//pָ��ջ����qָ������ĵڶ����ڵ�
		PNODE p = pS->pTop;
		PNODE q = p->pNext;
		while (p!=pS->pBottom)//��ջ��Ϊ��ջʱ
		{
			//qָ��ջ������һ��Ԫ��
			q = p->pNext;
			//�ͷ�ǰһ���ڵ�
			free(p);
			//pָ��ǰ�ĵ�һ���ڵ�
			//��p����ָ��ջ��
			p = q;
		}
		//ѭ��ִ����Ϻ�ջΪ��,ʹջ��ָ���ջ��ָ��ͬΪͷ�ڵ�
		pS->pTop = pS->pBottom;
	}
}
