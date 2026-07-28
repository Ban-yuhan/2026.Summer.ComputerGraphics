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
SNode* FindeNodeData(SNode* pStart, int data);
SNode* InsertNodeData(SNode* pStart, int data, int insert);
void DeleteNodeData(SNode* pStart, int del);
SNode* DeleteLinkedList(SNode* pStart);


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

	SNode* pFind = FindeNodeData(pBegin, 50);
	if (pFind != NULL)
		printf("Find:%d\n", pFind->nData);

	pEnd = InsertNodeData(pBegin, 20, 60);//노드 삽입

	PrintLinkedList(pBegin);

	DeleteNodeData(pBegin, 60);//노드 삭제

	PrintLinkedList(pBegin);

	pBegin = DeleteLinkedList(pBegin); //모든노드삭제 - 이 함수를 호출하지않을시 메모리가 누수됨.
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


SNode* FindeNodeData(SNode* pStart, int data)
{
	SNode* pNode = pStart;
	
	while (pNode->nData != data)
	{
		pNode = pNode->pNext;
	}

	return pNode;
}


SNode* InsertNodeData(SNode* pStart, int data, int insert)
{
	SNode* pNode = NULL;
	SNode* pInsert = NULL;

	pNode = FindeNodeData(pStart, data);

	pInsert = new SNode();
	pInsert->nData = insert;
	pInsert->pNext = pNode->pNext;
	pNode->pNext = pInsert;

	SNode* pEnd = pInsert;
	while (pEnd->pNext != pStart)
	{
		pEnd = pEnd->pNext;
	}

	return pEnd;
}


void DeleteNodeData(SNode* pStart, int del)
{
	SNode* pNode = pStart;
	SNode* pPre = NULL;

	if (pNode->pNext != pStart) 
	{
		while (pNode->nData != del)
		{
			pPre = pNode;
			pNode = pNode->pNext;
		}
	}

	pPre->pNext = pNode->pNext;

	delete pNode;
}


SNode* DeleteLinkedList(SNode* pStart)
{
	SNode* pNode = pStart;
	SNode* pDel = NULL;

	if (pStart != NULL) 
	{
		while (pNode->pNext != pStart) 
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

		printf(",");
		
		if (pNode == pStart)
		{
			printf("%d", pNode->nData);
			break;
		}
	}
	
	printf("\n");
}
