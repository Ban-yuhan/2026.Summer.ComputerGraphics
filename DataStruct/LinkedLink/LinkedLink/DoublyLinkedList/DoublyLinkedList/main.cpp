#include <stdio.h>;
#include <stdlib.h>;
#include <crtdbg.h>;

struct SNode
{
	int nData;
	SNode* pNext;
	SNode* pBefore;
};


SNode* CreateNode(SNode* pNode, int data);
SNode* FindNodeData(SNode* pStart, int data);
void DeleteNodeData(SNode* pEnd, int del);
void PrintLinkedList(SNode* Start);
void PrintLinkedListReverse(SNode* pEnd);
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

	PrintLinkedListReverse(pEnd);

	SNode* pFind = FindNodeData(pBegin, 40);
	printf("FInd : %d \n", pFind->nData);

	DeleteNodeData(pEnd,30);

	PrintLinkedList(pBegin);

	PrintLinkedListReverse(pEnd);

	DeleteLinkedList(pBegin);
}


SNode* CreateNode(SNode* pNode, int data)
{
	SNode* pTemp = NULL;

	pTemp = new SNode();

	if (pNode != NULL)
	{
		pNode->pNext = pTemp;
		pTemp->pBefore = pNode;
	}
	pTemp->nData = data;

	return pTemp;
}


SNode* FindNodeData(SNode* pStart, int data)
{
	SNode* pNode = pStart;

	while (pNode->nData != data)
	{
		pNode = pNode->pNext;
	}

	return pNode;
}


void DeleteNodeData(SNode* pEnd, int del)
{
	SNode* pNext = NULL;
	SNode* pNode = pEnd;

	if (pNode->pBefore != NULL)
	{
		while (pNode->nData != del)
		{
			pNext = pNode;
			pNode = pNode->pBefore;
		}
	}

	pNext->pBefore = pNode->pBefore;
	pNode->pBefore->pNext = pNext;

	delete pNode;
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


void PrintLinkedList(SNode* pStart) 
{
	SNode* pNode = pStart;
	printf("data : ");
	while (pNode) 
	{
		printf("%d", pNode->nData);
		pNode = pNode->pNext;

		if (pNode != NULL)
		{
			printf(",");
		}
	}
	printf("\n");
}


void PrintLinkedListReverse(SNode* pEnd)
{
	SNode* pNode = pEnd;
	printf("data(R) : ");
	while (pNode)
	{
		printf("%d", pNode->nData);
		pNode = pNode->pBefore;

		if (pNode != NULL)
		{
			printf(",");
		}
	}
	printf("\n");
}

