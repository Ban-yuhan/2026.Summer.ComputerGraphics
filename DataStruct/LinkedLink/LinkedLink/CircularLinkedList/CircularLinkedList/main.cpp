#include<stdio.h>
#include<stdlib.h>
#include<crtdbg.h>

struct SNode
{
	int nData;
	SNode* pNext;
};


SNode* CreateNode(SNode* pStart, SNode* pNode, int data);
void PrintLinkedList(SNode* pStart);


void main()
{
	SNode* pBegin = NULL;
	SNode* pEnd = NULL;

	pEnd = CreateNode(pBegin, pEnd, 10);

	pBegin = pEnd;

	pEnd = CreateNode(pBegin, pEnd, 20);
	pEnd = CreateNode(pBegin, pEnd, 30);
	pEnd = CreateNode(pBegin, pEnd, 40);
	pEnd = CreateNode(pBegin, pEnd, 50);

	PrintLinkedList(pBegin);

}


SNode* CreateNode(SNode* pStart, SNode* pNode, int data)
{
	SNode* pTemp = NULL;
	

	pTemp = new SNode();
	if (pNode != NULL) 
	{
		pNode->pNext = pTemp;
	}
	
	if (pStart == NULL)
	{
		pTemp->pNext = pTemp;
	}
	else
	{
		pTemp->pNext = pStart;
	}
	
	pTemp->nData = data;

	return pTemp;
}


void PrintLinkedList(SNode* pStart) 
{
	SNode* pNode = pStart;
	printf("data : ");
	while (pNode)
	{
		printf("%d", pNode->nData);
		pNode = pNode->pNext;	

		if (pNode != pStart) 
		{
			printf(",");
		}
		else 
		{
			printf(",");

			printf("%d", pNode->nData);
			break;
		}
	}
	
	printf("\n");
}
