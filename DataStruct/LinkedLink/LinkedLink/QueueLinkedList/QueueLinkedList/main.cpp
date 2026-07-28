#include <stdio.h>
#include <stdlib.h> 
#include <crtdbg.h>


struct SNode {
	int nData;
	SNode* pNext;
};


SNode* Enqueue(SNode* pNode, int data);
SNode* Dequeue(SNode* pStart);
void PrintQueue(SNode* pStart);
SNode* DeleteQueue(SNode* pStart);


void main()
{
	SNode* pBegin = NULL;
	SNode* pEnd = NULL;

	pEnd = Enqueue(pEnd, 10);

	pBegin = pEnd;

	pEnd = Enqueue(pEnd, 20);
	pEnd = Enqueue(pEnd, 30);
	pEnd = Enqueue(pEnd, 40);
	pEnd = Enqueue(pEnd, 50);

	PrintQueue(pBegin);

	pBegin = Dequeue(pBegin);

	PrintQueue(pBegin);

	pEnd = Enqueue(pEnd, 80);

	PrintQueue(pBegin);

	pBegin = Dequeue(pBegin);

	PrintQueue(pBegin);

	printf("pBegin : %d[%d] \n", pBegin->nData,pBegin);

	pBegin = Dequeue(pBegin);

	PrintQueue(pBegin);

	printf("pBegin : %d[%d] \n", pBegin->nData, pBegin);


	pBegin = DeleteQueue(pBegin);
}


SNode* Enqueue(SNode* pNode, int data)
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


SNode* Dequeue(SNode* pStart)
{
	SNode* pDel = NULL;
	SNode* pNode = pStart;

	pDel = pNode;
	pNode = pNode->pNext;

	delete pDel;

	return pNode;
}


void PrintQueue(SNode* pStart)
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


SNode* DeleteQueue(SNode* pStart)
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