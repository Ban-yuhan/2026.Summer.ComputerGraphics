#include <stdio.h>
#include <stdlib.h> 
#include <crtdbg.h>


struct SNode {
	int nData;
	SNode* pNext;
};


SNode* CreateNode(SNode* pNode, int data);
SNode* DeleteNodeData(SNode* pStart);
void PrintLinkedList(SNode* pStart);
SNode* DeleteLinkedList(SNode* pStart);


void main()
{
	SNode* pBegin = NULL;
	SNode* pEnd = NULL;

	pEnd = CreateNode(pEnd, 10);

	pBegin = pEnd;

	pEnd = CreateNode(pEnd, 20);
	pEnd = CreateNode(pEnd, 30);
	pEnd = CreateNode(pEnd, 40);
	pEnd = CreateNode(pEnd, 50);

	PrintLinkedList(pBegin);

	pBegin = DeleteNodeData(pBegin);

	PrintLinkedList(pBegin);

	pEnd = CreateNode(pEnd, 80);

	PrintLinkedList(pBegin);

	pBegin = DeleteNodeData(pBegin);

	PrintLinkedList(pBegin);

	printf("pBegin : %d[%d] \n", pBegin->nData,pBegin);

	pBegin = DeleteNodeData(pBegin);

	PrintLinkedList(pBegin);

	printf("pBegin : %d[%d] \n", pBegin->nData, pBegin);


	pBegin = DeleteLinkedList(pBegin);
}


SNode* CreateNode(SNode* pNode, int data)
{
	SNode* pTemp = NULL;

	pTemp = new SNode();
	if (pNode != NULL)
	{
		pNode->pNext = pTemp;
	}
	pTemp->nData = data;


	return  pTemp;
}


SNode* DeleteNodeData(SNode* pStart)
{
	SNode* pDel = NULL;
	SNode* pNode = pStart;

	pDel = pNode;
	pNode = pNode->pNext;

	delete pDel;

	return pNode;
}


void PrintLinkedList(SNode* pStart)
{
	SNode* pNode = pStart;
	printf("data:");
	while (pNode)
	{
		printf("%d", pNode->nData);
		pNode = pNode->pNext;

		if (pNode != NULL)
			printf(",");
	}
	printf("\n");
}


SNode* DeleteLinkedList(SNode* pStart)
{
	SNode* pNode = pStart;
	SNode* pDel = NULL;

	if (pStart != NULL)
	{
		while (pNode->pNext != NULL)
		{
			pDel = pNode;
			pNode = pNode->pNext;
			delete pDel;
		}

		delete pNode;
	}

	return NULL;
}