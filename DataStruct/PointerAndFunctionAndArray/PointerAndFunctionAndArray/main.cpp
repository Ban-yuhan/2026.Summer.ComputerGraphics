#include <stdio.h>


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


//정수와 실수의 데이터를 선언하고, 선언된 데이터를 각 실수와 정수의 포인터에 저장하여 모든 변수들에서 연산할 수 있는 모든 결과를 출력

//포인터 : 변수의 주소값을 저장하는 변수. 예) int* pData = &nData; -> p : pointer약자. 
//데이터 : 포인터(변수라는 의미를 포함) : pData, 포인터가 가르킬 변수 : nData
//알고리즘 : nData에 값을 넣고, nData의 주소값을 pData에 넣는다.
//			nData, pdata에서 할수있는 연산을 모두 출력.

//변수에서 할 수 있는 연산
// & : 변수의 주소값을 가져오는 연산자
// * : 포인터가 가르키는 변수의 값을 가져오는 연산자
void PointerTestMain() 
{
	int nDataA = 10;
	float fDataB = 8.314f;

	int* pintDataA = &nDataA; 
	float* pfloatDataB = &fDataB;

	printf("nDataA[%d, %p] \n", nDataA, &nDataA);
	printf("pintDataA[%p, %d] \n", pintDataA, *pintDataA);
	printf("fDataB[%f, %p] \n", fDataB, &fDataB);
	printf("pfloatDataB[%p, %f] \n", pfloatDataB, *pfloatDataB);
}


int main() 
{
	OperatorTestMain();
	PointerTestMain();

	return 0;
}
