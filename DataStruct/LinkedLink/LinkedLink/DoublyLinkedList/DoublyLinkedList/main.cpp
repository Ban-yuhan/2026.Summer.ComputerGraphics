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
void PrintLinkedList(SNode* Start);


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

	SNode* pFind = FindNodeData(pBegin, 40);
	printf("FInd : %d \n", pFind->nData);


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

