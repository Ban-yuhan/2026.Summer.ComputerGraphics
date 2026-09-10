#pragma once
#include "MyVector.h" 

template <typename T>
class Stack
{
private:
    Vector<T> container_; // 노드를 다루는 대신 Vector를 내부에 포함하여 위임

public:
    Stack() = default;
    ~Stack() = default;

    // 1. Push (스택의 맨 위에 데이터 추가)
    void Push(const T& val)
    {
        container_.PushBack(val); // Vector의 PushBack 활용 (O(1))
    }

    // 2. Pop (스택의 맨 위 데이터 제거)
    void Pop()
    {
        container_.PopBack(); // Vector의 PopBack 활용 (O(1))
    }

    // 3. Top (스택 맨 위의 데이터 참조)
    T& Top()
    {
        return container_[container_.Size() - 1]; // 마지막 원소 접근
    }

    const T& Top() const
    {
        return container_[container_.Size() - 1];
    }

    // 4. 부가 기능
    bool Empty() const { return container_.Empty(); }
    size_t Size() const { return container_.Size(); }
};