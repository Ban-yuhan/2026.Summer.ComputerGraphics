#include <iostream>
#include <vector>
#include <algorithm>

// GC가 관리할 최소 단위의 객체 클래스
class Object {
public:
    bool marked = false;     // GC 마킹 여부
    Object* first = nullptr;  // 다른 객체를 참조할 수 있는 포인터 1
    Object* second = nullptr; // 다른 객체를 참조할 수 있는 포인터 2

    virtual ~Object() {
        std::cout << "객체 메모리 해제(소멸): " << this << std::endl;
    }
};

// 가비지 컬렉터 클래스
class GarbageCollector {
private:
    std::vector<Object*> heap;  // 생성된 모든 객체를 추적하는 힙(Heap) 공간
    std::vector<Object*> roots; // 프로그램에서 직접 접근 가능한 루트 객체들

public:
    ~GarbageCollector() {
        // GC가 소멸할 때 남은 메모리 모두 정리
        for (Object* obj : heap) {
            delete obj;
        }
    }

    // 1. 새 객체 할당 (malloc/new 역할)
    Object* createObject() {
        Object* obj = new Object();
        heap.push_back(obj);
        std::cout << "객체 생성: " << obj << std::endl;
        return obj;
    }

    // 2. 루트(Root) 등록 및 해제
    void addRoot(Object* obj) {
        roots.push_back(obj);
    }

    void removeRoot(Object* obj) {
        roots.erase(std::remove(roots.begin(), roots.end(), obj), roots.end());
    }

    // 3. Mark Phase: 루트에서 연결된 모든 객체를 DFS(깊이 우선 탐색)로 표시
    void mark(Object* obj) {
        if (obj == nullptr || obj->marked) return;

        obj->marked = true;
        mark(obj->first);  // 자식/참조 객체들도 재귀적으로 마킹
        mark(obj->second);
    }

    void markAll() {
        // 모든 루트 객체부터 탐색 시작
        for (Object* root : roots) {
            mark(root);
        }
    }

    // 4. Sweep Phase: 마킹되지 않은 객체들(가비지) 메모리 해제
    void sweep() {
        auto it = heap.begin();
        while (it != heap.end()) {
            Object* obj = *it;

            if (!obj->marked) {
                // 루트로부터 도달 불가능한 객체 발견! -> 메모리 해제
                it = heap.erase(it);
                delete obj;
            }
            else {
                // 살아남은 객체는 다음 GC를 위해 마킹 플래그 초기화
                obj->marked = false;
                ++it;
            }
        }
    }

    // 5. GC 실행 메서드
    void collect() {
        std::cout << "\n=== [GC 실행 시작] ===" << std::endl;
        markAll();
        sweep();
        std::cout << "=== [GC 실행 완료] ===\n" << std::endl;
    }
}; // 클래스 정의 종료 (반드시 중괄호 '}' 뒤에 세미콜론)

// main 함수는 클래스 외부에 작성해야 합니다.
int main() {
    GarbageCollector gc;

    // 객체 3개 생성
    Object* objA = gc.createObject();
    Object* objB = gc.createObject();
    Object* objC = gc.createObject();

    // 관계 설정: objA -> objB -> objC
    objA->first = objB;
    objB->first = objC;

    // A를 루트 객체로 등록 (프로그램이 A를 직접 가리키고 있음)
    gc.addRoot(objA);

    std::cout << "\n-- 1차 GC 실행 (A, B, C 모두 연결되어 있으므로 아무것도 해제 안 됨) --" << std::endl;
    gc.collect();

    // B와 C 사이의 연결을 끊음 (objC는 이제 아무도 도달할 수 없는 가비지가 됨)
    objB->first = nullptr;

    std::cout << "-- 2차 GC 실행 (연결이 끊긴 C 객체 자동 수거) --" << std::endl;
    gc.collect();

    // 루트에서 A 등록 해제 (A, B 모두 도달 불가능한 가비지가 됨)
    gc.removeRoot(objA);

    std::cout << "-- 3차 GC 실행 (A, B 객체 모두 자동 수거) --" << std::endl;
    gc.collect();

    return 0;
}