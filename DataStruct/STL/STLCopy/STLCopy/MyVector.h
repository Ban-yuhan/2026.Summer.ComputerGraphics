#pragma once

#include <cstddef> // size_t 사용

template <typename T>
class Vector
{
private:
    T* data;           // 데이터를 저장할 동적 배열 포인터
    size_t capacity;   // 할당된 메모리 크기
    size_t size;       // 현재 저장된 데이터 개수

    void reallocate(size_t new_capacity)
    {
        // 1. 새 크기만큼 메모리 할당
        T* new_data = new T[new_capacity];

        // 2. 기존 데이터 복사
        for (size_t i = 0; i < size; ++i)
        {
            new_data[i] = data[i];
        }

        // 3. 기존 메모리 해제
        delete[] data;

        // 4. 새 주소 및 용량 갱신
        data = new_data;
        capacity = new_capacity;
    }

public:
    // 생성자
    Vector() : data(nullptr), capacity(0), size(0) {}

    // 소멸자
    ~Vector()
    {
        delete[] data;
    }

    // 1. 일반 객체용: 값 읽기 및 수정 가능 (v[0] = 100;)
    T& operator[](size_t index)
    {
        return data[index];
    }

    // 2. const 객체용: 값 읽기만 가능
    const T& operator[](size_t index) const
    {
        return data[index];
    }

    // 푸시백
    void PushBack(const T& val)
    {
        if (size == capacity)
        {
            size_t new_capacity = (capacity == 0) ? 2 : capacity * 2;
            reallocate(new_capacity);
        }

        data[size] = val;
        size++;
    }

    // 맨 뒤 원소 삭제
    void PopBack()
    {
        if (size > 0)
        {
            size--;
            // (참고) T가 클래스 타입인 경우 소멸자를 명시적으로 호출해주는 것이 원칙이지만,
            // 기본 자료구조 학습 단계에서는 size-- 만으로도 충분히 동작합니다.
        }
    }

    // 전체 원소 삭제
    void Clear()
    {
        size = 0;
    }

    // 배열이 비어있는지 확인하는 함수
    bool Empty() const
    {
        return size == 0;
    }

    // 현재 원소 개수 반환
    size_t Size() const
    {
        return size;
    }

    // 지정한 index 위치에 값 삽입
    void Insert(size_t index, const T& val)
    {
        if (index > size) return; // 범위 초과 예외 처리

        // 공간이 부족하면 메모리 확장
        if (size == capacity)
        {
            size_t new_capacity = (capacity == 0) ? 2 : capacity * 2;
            reallocate(new_capacity);
        }

        // index 위치부터 데이터를 오른쪽으로 한 칸씩 이동
        for (size_t i = size; i > index; --i)
        {
            data[i] = data[i - 1];
        }

        data[index] = val;
        size++;
    }

    // 지정한 index 위치의 값 삭제
    void Erase(size_t index)
    {
        if (index >= size) return; // 범위 초과 예외 처리

        // index + 1 위치부터 데이터를 왼쪽으로 한 칸씩 이동
        for (size_t i = index; i < size - 1; ++i)
        {
            data[i] = data[i + 1];
        }

        size--;
    }

    //복사 생성자 (Copy Constructor)
    // 예: Vector<int> v2 = v1; 또는 Vector<int> v2(v1);
    Vector(const Vector& other)
        : data(nullptr), capacity(0), size(0)
    {
        if (other.capacity > 0)
        {
            // 1) 상대방의 capacity만큼 새 메모리 할당
            capacity = other.capacity;
            size = other.size;
            data = new T[capacity];

            // 2) 데이터 복사
            for (size_t i = 0; i < size; ++i)
            {
                data[i] = other.data[i];
            }
        }
    }

    //대입 연산자 (Copy Assignment Operator)
    // 예: v2 = v1; (이미 생성된 v2에 v1을 대입할 때)
    Vector& operator=(const Vector& other)
    {
        // 1) 자기 자신을 대입하는 경우 (v1 = v1;) 예외 처리
        if (this == &other)
        {
            return *this;
        }

        // 2) 기존에 가진 메모리가 있다면 해제
        delete[] data;

        // 3) 초기화 후 상대방 정보 복사
        capacity = other.capacity;
        size = other.size;

        if (capacity > 0)
        {
            data = new T[capacity];
            for (size_t i = 0; i < size; ++i)
            {
                data[i] = other.data[i];
            }
        }
        else
        {
            data = nullptr;
        }

        return *this; // 연속 대입 (v3 = v2 = v1)을 가능하게 하기 위해 자신을 참조로 반환
    }
};
