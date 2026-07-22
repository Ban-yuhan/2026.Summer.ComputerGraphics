#include <stdio.h>
#include <string.h>

//선언 : 있는것을 알리는 것
//정의 : 실제로 구현하는것
//초기화 : 선언과 동시에 값을 넣는 것
//함수 : 특정 작업을 수행하는 코드블록.
//식별자 : 무엇인가 구별하기 위해 정해진 것. 변수나 함수의 이름

//전방성언
//함수의 선언
void PointerTestMain();
void ArrayPointerTestMain();
void SwapTestMain();	
void ArrayMain();

//데이터 값을 전위연산자와 후위연산자의 차이를 이해하기 위해 프로그램을 작성하여라.

//전위연산자 : 값이 먼저 증가하고 대입(=복사).
//후위연산자 : 값을 먼저 대입(=복사)하고 나서 값을 증가.

//-> 전위 연산으로 변수의 값을 저장하고, 후위 연산을 해서 값을 각 변수(2개 필요)에 대입하여 연산결과가 어떻게 달라지는지 관찰하고,
//코드에 보이지 않는 순서를 찾아내어 이해

//데이터(변수) : nDataA, nDataB 2개의 변수 필요
// n : number의 약자. 보통 C++을 배운사람들은 저런식으로 변수의 타입을 구분하기 쉽게 변수명 작성.

//알고리즘 : nDataA에 값을 넣고, 후위연산하여 nDataB에 대입하고, nDataA의 값을 전위 연산하고, nDataB에 대입. -> 모든 연산을 하는 과정 및 순서를 알고리즘이라 함.(중간에 생략하였지만, 출력까지 포함하는 순서가 알고리즘)
//변수의 값이 변경되고나면 모든 변수의 값을 출력하여 결과 확인. -> 출력까지가 알고리즘에 포함.(제대로 된 결과가 나타나는지까지 확인)
void OperatorTestMain() 
{
	printf("\n\n [OperatorTestMain] \n\n");

	int nDataA = 10;
	int nDataB = nDataA;

	printf("대입 후 결과 \n nDataA : %d, nDataB : %d\n\n", nDataA, nDataB);

	nDataB = nDataA++; //후위연산 : 값을 먼저 대입, 이후 증가

	printf("++후위연산 후 결과 \n nDataA : %d, nDataB : %d\n\n", nDataA, nDataB); // 값 출력

	nDataB = --nDataA; //전위연산 : 값이 먼저 증가, 이후 대입.

	printf("--전위연산 후 결과 \n nDataA : %d, nDataB :%d\n\n", nDataA, nDataB);
}


int main() 
{
	//함수의 호출 : 함수를 부른다(실제로는 함수로 간다는 개념에 가까움)
	//OperatorTestMain();
	//PointerTestMain();
	//SwapTestMain();
	//ArrayPointerTestMain();
	ArrayMain();

	return 0;
}



void SwapVal(int nDataA, int nDataB)
{
	printf("\nSwapVal DataA[%p] : %d <-> DataB[%p] : %d\n", &nDataA, nDataA, &nDataB, nDataB);

	int ntemp = nDataA;
	nDataA = nDataB;
	nDataB = ntemp;
}
void SwapPointer(int* pA, int* pB)
{
	printf("\nSwapPointer DataA [%p] :%d <-> DataB [%p] : %d\n", &pA, pA, &pB, pB);
	int temp = *pA;
	*pA = *pB;
	*pB = temp;
}
void SwapRef(int& a, int& b) //참조자 : 원본을 전달받음.
{
	printf("\nSwapRef DataA [%p] : %d <-> DataB [%p] : %d\n", &a, a, &b, b);
	int temp = a;
	a = b;
	b = temp;
}

//두 변수를 변경하는 함수를 사용할 때, 각 함수에서 값/포인터/참조를 전달하여 계산이 어떻게되는 지 검증하는 프로그램을 만들어라
//데이터 : nDataA, nDataB 2개의 변수 필요
//알고리즘 : nDataA, nDataB에 값을 넣고, 각 함수를 호출하여 각함수에서 값/포인터/참조를 전달하여 계산이 어떻게 되는지 검증.
//각 함수에서 매개변수의 주소값과 값을 출력하여, 전달된 변수의 정보를 출력하여 확인하고, 각 스왑이 끝나고 테스트함수에서 스왑된 변수의 값을 출력.
void SwapTestMain() 
{
	int nDataA = 10;
	int nDataB = 20;
	
	printf("Original nDataA[%p]%d, nDataB[%p]%d", &nDataA, nDataA, &nDataB, nDataB);

	SwapVal(nDataA, nDataB);
	printf("\n\nSwapValue DataA[%p] : %d <-> DataB [%[] : %d\n", &nDataA, nDataA, &nDataB, nDataB);
	
	SwapPointer(&nDataA, &nDataB);
	
	SwapRef(nDataA, nDataB);
}


//정수와 실수의 데이터를 선언하고, 선언된 데이터를 각 실수와 정수의 포인터에 저장하여 모든 변수들에서 연산할 수 있는 모든 결과를 출력

//포인터 : 변수의 주소값을 저장하는 변수. 예) int* pData = &nData; -> p : pointer약자. 
//데이터 : 변수의 주소값을 저장하는 변수. 예) int* pData = &nData; , float* pDataFloat = &fData;
//알고리즘 : nData에 값을 넣고, nData의 주소값을 pData에 넣는다.
//			nData, pdata에서 할수있는 연산을 모두 출력.

//변수에서 할 수 있는 연산
// & : 변수의 주소값을 가져오는 연산자
// * : 포인터가 가르키는 변수의 값을 가져오는 연산자

void PointerTestMain()
{
	printf("\n\n [PointerTestMain] \n\n");

	int nData = 10;
	float fData = 8.314f;

	int* pintData = &nData;
	float* pfloatData = &fData;

	printf("nData[%d, %d] \n", nData, &nData); //10, 주솟값
	printf("pintData[%p, %d] \n", pintData, *pintData);
	printf("fData[%f, %d] \n", fData, &fData);
	printf("pfloatData[%p, %f] \n", pfloatData, *pfloatData);
}


//배열이 포인터를 이용하여 작동되는 방법을 검증하는 프로그램 만들기
// 변수 : 배열, 포인터 arrData[3], int* pData
// 
// 알고리즘:
//배열 선언. 크기3개
//배열의 초기화 100, 80, 90
//배열의 주소값을 저장하는 포인터를 만든다.
//배열의 주소값에 포인터를 넣는다.
//배열의 주소값과 데이터를 출력.
//벼열의 주소값을 저장한 포인터에서 배열을 n번으로 더하여 주소값과 데이터를 출력.
//배열의 주소값을 저장한 포인터에 3번만큼 1씩 증가하며 주소값과 데이터를 저장.
void ArrayPointerTestMain()
{
	const int nSize = 3; //const(상수) : 변수의 값을 변경할 수 없게 만듦
	//배열의 크기를 지정할 떄 컴파일러는 크기를 알아야 할당이 가능하기 때문에, 상수만 사용 가능.
	//배열 : 연속으로 변수를 할당하여, 주소값을 통해 바로 인덱스로 접근 가능하도록 만들어진 변수.
	//포인터연산 : 포인터의 값을 증가시키는 연산. 변수의 크기만큼 주소값이 증가. +n을 하면 변수의 크기 *n개가 됨.
	int arrData[nSize];
	
	for(int i =0; i <3; i++)
	{
		arrData[i] = 100 - (i*10);
	}

	printf("arrData : ");

	for (size_t i = 0; i < 3; i++)
	{
		printf("[%d/%d]%d,", i, &arrData[i], arrData[i]);
	}

	printf("\n");

	int* pData = arrData;

	printf("pData+i : ");

	for(size_t i = 0; i < 3; i++)
	{
		printf("[%d/%d]%d,", i, pData + i, *(arrData + i));
	}

	printf("\n");

	printf("pData++ : ");

	for(size_t i = 0; i < 3; i++)
	{
		printf("[%d/%d]%d,", i, pData, *pData);
		pData++;
	}
}


void ArrayMain()
{
	const int nSize = 3;
	int arrScores[nSize];
	int arrSize = sizeof(arrScores) / sizeof(arrScores[0]);
	for (int i = 0; i < nSize; i++)
		arrScores[i] = 100 - i * 10;
	printf("arrScore[%d] : %d \n", &arrScores, arrScores);
	for (int i = 0; i < nSize; i++)
		printf("[%d/%d]%d,", (arrScores + i), i, *(arrScores + i));
	printf("\n");

	int* pScores = arrScores;
	printf("1. PtrScores[%d] : %d \n", pScores, *pScores);
	for (int i = 0; i < nSize; i++)
	{
		printf("[%d/%d]%d,", pScores, i, *pScores);
		pScores++;
	}
	printf("\n");
	int arrCopyArray[nSize];
	for (int i = 0; i < nSize; i++)
		arrCopyArray[nSize];
	memcpy(arrCopyArray, arrScores, nSize);
}