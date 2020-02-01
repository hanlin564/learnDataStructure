#include <stdio.h>
#include <stdlib.h>

struct BTNode
{
	int data;
	struct BTNode *pLchild;
	struct BTNode *pRchild;
};

struct BTNode *CreateBTree();

void PreTraverseBTree(BTNode *pT);
void InTraverseBTree(BTNode *pT);
void PostTraverseBTree(BTNode *pT);

int main()
{
	struct BTNode *pT = CreateBTree();
	//PreTraverseBTree(pT);
	//InTraverseBTree(pT);
	PostTraverseBTree(pT);

	return 0;
}

BTNode * CreateBTree()
{
	BTNode *pA = (BTNode *)malloc(sizeof(BTNode));
	BTNode *pB = (BTNode *)malloc(sizeof(BTNode));
	BTNode *pC = (BTNode *)malloc(sizeof(BTNode));
	BTNode *pD = (BTNode *)malloc(sizeof(BTNode));
	BTNode *pE = (BTNode *)malloc(sizeof(BTNode));

	pA->data = 'A';
	pB->data = 'B';
	pC->data = 'C';
	pD->data = 'D';
	pE->data = 'E';

	pA->pLchild = pB;
	pA->pRchild = pC;
	pB->pLchild = pB->pRchild = NULL;
	pC->pLchild = pD;
	pC->pRchild = NULL;
	pD->pLchild = NULL;
	pD->pRchild = pE;
	pE->pLchild = pE->pRchild = NULL;

	return pA;
}

void PreTraverseBTree(BTNode * pT)
{
	if (pT!=NULL)
	{
		printf("%c\n", pT->data);
		PreTraverseBTree(pT->pLchild);
		PreTraverseBTree(pT->pRchild);
	}
}

void InTraverseBTree(BTNode * pT)
{
	if (pT != NULL)
	{
		InTraverseBTree(pT->pLchild);
		printf("%c\n", pT->data);
		InTraverseBTree(pT->pRchild);
	}
}

void PostTraverseBTree(BTNode * pT)
{
	if (pT != NULL)
	{
		PostTraverseBTree(pT->pLchild);
		PostTraverseBTree(pT->pRchild);
		printf("%c\n", pT->data);
	}

}
