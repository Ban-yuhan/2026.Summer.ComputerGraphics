#pragma once
#include "MyList.h" 

template <typename T>
class Queue
{
private:
    List<T> list_; // 노드 관리는 이미 완성된 List에 전부 위임!

public:
    Queue() = default;
    ~Queue() = default;

    // 1. Enqueue (큐의 맨 뒤에 데이터 추가)
    void Push(const T& val)
    {
        list_.PushBack(val); // List의 PushBack 재활용
    }

    // 2. Dequeue (큐의 맨 앞 데이터 삭제)
    void Pop()
    {
        list_.PopFront(); // List의 PopFront 재활용
    }

    // 3. 맨 앞의 데이터 확인 (삭제 안 함)
    T& Front()
    {
        return *list_.begin(); // List의 첫 번째 원소 반환
    }

    // 4. 부가 기능들
    bool Empty() const { return list_.Empty(); }
    size_t Size() const { return list_.Size(); }
};