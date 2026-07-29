#include <stdio.h>
#include <stdlib.h> 
#include <crtdbg.h>


struct SNode {
	int nData;
	SNode* pNext;
};


SNode* Push(SNode* pNode, int data);
SNode* Pop(SNode* pEnd);
void PrintStack(SNode* pStart);
SNode* DeleteStack(SNode* pStart);


void main()
{
	SNode* pBegin = NULL;
	SNode* pEnd = NULL;

	pEnd = Push(pEnd, 10);

	pBegin = pEnd;

	pEnd = Push(pEnd, 20);
	pEnd = Push(pEnd, 30);
	pEnd = Push(pEnd, 40);
	pEnd = Push(pEnd, 50);

	PrintStack(pBegin);

	pEnd = Pop(pBegin);

	PrintStack(pBegin);

	pEnd = Push(pEnd, 80);

	PrintStack(pBegin);

	pEnd = Pop(pBegin);

	PrintStack(pBegin);

	printf("pEnd : %d[%d] \n", pEnd->nData, pEnd);

	pEnd = Pop(pBegin);

	PrintStack(pBegin);

	printf("pEnd : %d[%d] \n", pEnd->nData, pEnd);


	pBegin = DeleteStack(pBegin);
}


SNode* Push(SNode* pNode, int data)
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


SNode* Pop(SNode* pStart)
{
	SNode* pPre = NULL;
	SNode* pNode = pStart;

	while (pNode->pNext != NULL)
	{
		pPre = pNode;
		pNode = pNode->pNext;
	}

	delete pNode;
	pPre->pNext = NULL;

	return pPre;
}


void PrintStack(SNode* pStart)
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


SNode* DeleteStack(SNode* pStart)
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