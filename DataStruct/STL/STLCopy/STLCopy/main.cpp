#include <iostream>

#include "MyList.h"
#include "MyVector.h"
#include "MyQueue.h"
#include "MyStack.h"


void testVector();
void testList();
void testQueue();
void testStack();


int main()
{
    //testVector();
    //testList();
    //testQueue();
    testStack();

}

void testVector()
{
    Vector<int> v1;
    v1.PushBack(10);
    v1.PushBack(20);

    // 1. 복사 생성자 테스트
    Vector<int> v2 = v1;

    // 2. 대입 연산자 테스트
    Vector<int> v3;
    v3 = v1;

    // v1의 데이터를 수정해도 v2, v3에 영향이 없어야 제대로 된 깊은 복사임
    v1[0] = 999;

    std::cout << "v1[0]: " << v1[0] << std::endl; // 999
    std::cout << "v2[0]: " << v2[0] << std::endl; // 10 (v1의 수정에 영향을 받지 않음)
    std::cout << "v3[0]: " << v3[0] << std::endl; // 10

    return;
}

void testList() 
{
    List<int> myList;

    // 1. 원소 추가 (10, 20, 30)
    myList.PushBack(10);
    myList.PushBack(20);
    myList.PushBack(30);

    std::cout << "초기 리스트: ";
    for (auto it = myList.begin(); it != myList.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << "\n"; // 출력: 10 20 30

    // 2. Iterator 탐색 후 20 앞에 15 삽입 (Insert)
    for (auto it = myList.begin(); it != myList.end(); ++it) {
        if (*it == 20) {
            myList.Insert(it, 15);
            break;
        }
    }

    std::cout << "20 앞에 15 삽입 후: ";
    for (auto it = myList.begin(); it != myList.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << "\n"; // 출력: 10 15 20 30

    // 3. 특정 조건 원소 삭제 (Erase)
    // erase 함수가 '다음 위치'의 Iterator를 반환하므로 순회 중 삭제 시 it = myList.erase(it) 구문을 사용합니다.
    for (auto it = myList.begin(); it != myList.end(); ) {
        if (*it == 15) {
            it = myList.Erase(it); // 15 삭제 후 다음 노드(20)를 반환받음
        }
        else {
            ++it;
        }
    }

    std::cout << "15 삭제 후: ";
    for (auto it = myList.begin(); it != myList.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << "\n"; // 출력: 10 20 30

    return;
}

void testQueue() 
{
    Queue<int> q;

    // 데이터 삽입 (Enqueue)
    q.Push(10);
    q.Push(20);
    q.Push(30);

    // 맨 앞 데이터 확인
    std::cout << "Front 데이터: " << q.Front() << std::endl; // 10

    // 데이터 삭제 (Dequeue)
    q.Pop(); // 10 삭제

    std::cout << "Pop 후 Front 데이터: " << q.Front() << std::endl; // 20

    // 큐가 빌 때까지 순차 출력
    std::cout << "큐 전체 출력: ";
    while (!q.Empty())
    {
        std::cout << q.Front() << " ";
        q.Pop();
    }
    // 출력 결과: 20 30

    return;
}

void testStack()
{
    Stack<int> s;

    // 데이터 Push (10, 20, 30, 40, 50)
    s.Push(10);
    s.Push(20);
    s.Push(30);
    s.Push(40);
    s.Push(50);

    std::cout << "현재 Top 데이터: " << s.Top() << std::endl; // 50

    // Pop 테스트
    s.Pop(); // 50 제거
    std::cout << "Pop 후 Top 데이터: " << s.Top() << std::endl; // 40

    // 스택이 빌 때까지 LIFO 순서대로 출력
    std::cout << "스택 전체 출력 (LIFO): ";
    while (!s.Empty())
    {
        std::cout << s.Top() << " ";
        s.Pop();
    }
    // 출력 결과: 40 30 20 10

    return;
}