#include <stdio.h>;
#include <stdlib.h>;
#include <crtdbg.h>;

struct SNode
{
	int nData;
	SNode* pNext;
	SNode* pBefore;
};