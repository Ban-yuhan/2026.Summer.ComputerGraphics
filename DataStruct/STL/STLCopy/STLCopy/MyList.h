#pragma once
#include <cstddef>
#include <iostream>

template <typename T>
struct Node
{
    T data;
    Node* prev;
    Node* next;

    Node(const T& val = T()) : data(val), prev(nullptr), next(nullptr) {}
};

template <typename T>
class List
{
private:
    Node<T>* head_; // 더미 헤드 노드 (시작점)
    Node<T>* tail_; // 더미 테일 노드 (끝점)
    size_t size_;

public:
    // ========================================================
    // List 전용 Iterator 클래스
    // ========================================================
    class Iterator
    {
    private:
        Node<T>* node; // 현재 가리키고 있는 노드의 포인터

    public:
        Iterator(Node<T>* n = nullptr) : node(n) {}

        // 1. 역참조 연산자 (*it): 노드가 가진 실제 데이터 접근
        T& operator*()
        {
            return node->data;
        }

        // 2. 멤버 접근 연산자 (it->member)
        T* operator->()
        {
            return &(node->data);
        }

        // 3. 전위 증가 연산자 (++it): 다음 노드로 이동
        Iterator& operator++()
        {
            node = node->next;
            return *this;
        }

        // 후위 증가 연산자 (it++)
        Iterator operator++(int)
        {
            Iterator temp = *this;
            node = node->next;
            return temp;
        }

        // 4. 전위 감소 연산자 (--it): 이전 노드로 이동
        Iterator& operator--()
        {
            node = node->prev;
            return *this;
        }

        // 후위 감소 연산자 (it--)
        Iterator operator--(int)
        {
            Iterator temp = *this;
            node = node->prev;
            return temp;
        }

        // 5. 비교 연산자 (it != list.end())
        bool operator!=(const Iterator& other) const
        {
            return node != other.node;
        }

        bool operator==(const Iterator& other) const
        {
            return node == other.node;
        }

        // List 내부 함수에서 private 변수인 node에 접근할 수 있도록 친구 등록
        friend class List<T>;
    };

    // ========================================================
    // List 생성자 / 소멸자
    // ========================================================
    List()
    {
        // 양쪽 끝을 담당할 더미 노드 생성 후 서로 연결
        head_ = new Node<T>();
        tail_ = new Node<T>();
        head_->next = tail_;
        tail_->prev = head_;
        size_ = 0;
    }

    ~List()
    {
        Clear();
        delete head_;
        delete tail_;
    }

    // --- begin() / end() 함수 ---
    Iterator begin()
    {
        return Iterator(head_->next);
    }

    Iterator end()
    {
        return Iterator(tail_);
    }

    size_t Size() const { return size_; }
    bool Empty() const { return size_ == 0; }

    // ========================================================
    // 데이터 추가 및 삭제 핵심 함수
    // ========================================================

    // 1. Insert (pos 가리키는 위치 바로 '앞'에 삽입)
    Iterator Insert(Iterator pos, const T& val)
    {
        Node<T>* curr = pos.node;
        Node<T>* prev_node = curr->prev;

        // 새 노드 생성 및 포인터 4개 연결
        Node<T>* new_node = new Node<T>(val);

        new_node->prev = prev_node;
        new_node->next = curr;

        prev_node->next = new_node;
        curr->prev = new_node;

        size_++;

        return Iterator(new_node); // 새로 만들어진 노드의 Iterator 반환
    }

    // 2. Erase (pos 가리키는 노드 삭제)
    Iterator Erase(Iterator pos)
    {
        // 더미 테일(end())은 삭제 불가능
        if (pos == end())
        {
            return pos;
        }

        Node<T>* target = pos.node;
        Node<T>* prev_node = target->prev;
        Node<T>* next_node = target->next;

        // 양옆 노드를 서로 직접 연결 (target 노드 우회)
        prev_node->next = next_node;
        next_node->prev = prev_node;

        delete target;
        size_--;

        return Iterator(next_node); // 삭제된 노드의 '다음' 위치 Iterator 반환
    }

    // PushBack, PushFront, PopBack, PopFront는 Insert/Erase를 재활용하면 매우 간단해집니다!
    void PushBack(const T& val)
    {
        Insert(end(), val);
    }

    void PushFront(const T& val)
    {
        Insert(begin(), val);
    }

    void PopBack()
    {
        if (!Empty())
        {
            Iterator last = end();
            --last;
            Erase(last);
        }
    }

    void PopFront()
    {
        if (!Empty())
        {
            Erase(begin());
        }
    }

    // 전체 삭제
    void Clear()
    {
        while (!Empty())
        {
            Erase(begin());
        }
    }
};