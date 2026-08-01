#include <stdio.h>

void InsertSort()
{
	int arrData[] = { 8,1,7,4,2,3,9,5,6 };

	//-------------------------------
	//배열을 정렬되도록 로직을 짜기
	
	/*for (int i = 1; i < 9; i++)
	{
		int key = arrData[i];
		int j = i - 1;
		while (j >= 0 && arrData[j] > key)
		{
			arrData[j + 1] = arrData[j];
			j--;
		}
		arrData[j + 1] = key;
	}*/

	for (int i = 0; i < sizeof(arrData) / sizeof(arrData[0]); i++) 
	{
		int DataA = arrData[i];
		int j = i;

		
		while (j > 0 && arrData[j] < arrData[j - 1])
		{
			arrData[j] = arrData[j - 1];
			arrData[j - 1] = DataA;
			j--;
		}
	}

	//-------------------------------

	//다음출력에서 1~9까지 순서대로 정렬되도록 만들기
	printf("Data:");
	for (int i = 0; i < 9; i++)
		printf("%d,", arrData[i]);
	printf("\n");
}

void main()
{
	InsertSort();
}