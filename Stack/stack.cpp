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
把栈的地址传递给init函数(此时栈不实际存在)
init函数实际上声明了一个链表的头节点
使pTop和pBottom共同指向头节点
此时栈中没有存放有效数据
*/
void init(PSTACK pS);
/*
向栈顶压入指定值
push函数接受一个栈的地址和一个将压入栈的值作为参数
*/
void push(PSTACK pS, int val);
//遍历栈:从栈顶向栈底
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
	//申请一个头节点的内存，使pTop指向头节点内存的首地址
	pS->pTop = (PNODE)malloc(sizeof(NODE));
	if (pS->pTop == NULL)
	{
		printf("动态内存分配失败\n");
		exit(-1);
	}
	else
	{
		//由于只有头节点，该栈的栈顶和栈尾共同指向头节点
		pS->pBottom = pS->pTop;
		//让栈顶指针为null
		//动态栈的栈顶对应链表头
		//栈底对应链表尾
		//注意:栈中的链表头节点指的是链表尾的一个不存放数据的节点(栈底)
		//链表中的头节点指的是链表首节点前的节点
		//一个在链表末端，一个在链表最前端
		pS->pTop->pNext = NULL;
		//?:这里貌似可以用栈底指针为null来代替
		//pS->pBottom->pNext = NULL;
	}
	return;
}

void push(PSTACK pS, int val)
{
	PNODE pNew = (PNODE)malloc(sizeof(NODE));
	//压入值存放到新节点数据域中
	pNew->data = val;
	//新节点的指针域存放老栈顶的地址
	pNew->pNext = pS->pTop;
	//栈顶指针指向新节点
	//每次压栈都会让栈顶指向新节点
	pS->pTop = pNew;
	return;
}

void traverse(PSTACK pS)
{
	//指针p存放栈顶地址
	PNODE p = pS->pTop;
	//用while循环输出栈中的值(自顶向下)
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
		//用指针r临时存放栈顶地址
		PNODE r = pS->pTop;
		//通过指针来修改val的值，这样可以获得弹出值
		*pVal = r->data;
		//栈顶指针指向链表的下一个位置
		pS->pTop = r->pNext;
		//free函数释放的是指针r指向的内存
		//r=null是避免游离指针
		free(r);
		r = NULL;
		return true;
	}

}

bool empty(PSTACK pS)
{
	//如果栈顶指针等于栈底指针，则栈为空
	//(只有头节点)
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
		//p指向栈顶，q指向链表的第二个节点
		PNODE p = pS->pTop;
		PNODE q = p->pNext;
		while (p!=pS->pBottom)//当栈不为空栈时
		{
			//q指向栈顶的下一个元素
			q = p->pNext;
			//释放前一个节点
			free(p);
			//p指向当前的第一个节点
			//即p重新指向栈顶
			p = q;
		}
		//循环执行完毕后栈为空,使栈顶指针和栈底指针同为头节点
		pS->pTop = pS->pBottom;
	}
}
