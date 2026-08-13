#include <iostream>
#include <vector>
#include <queue>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <functional>
#include <chrono>

// 1. 실행할 작업(Job) 클래스
class JobWorkItem {
public:
    int id;

    JobWorkItem(int id) : id(id) {}

    // 기존 9999 반복문 로직
    void Execute() const {
        for (int i = 0; i < 9999; ++i) {
            if (i % 1000 == 0) {
                // 콘솔 출력이 너무 많으면 속도 측정을 위해 주석 유지
                // std::cout << id << ":JobExecute:" << i << "\n";
            }
        }
    }
};

// 2. 잡 스케줄러 (스레드 풀)
class SimpleJobScheduler
{
    private:
    std::vector<std::thread> workers;            // 일꾼 스레드 목록
    std::queue<std::function<void() >> jobQueue;  // 작업 대기열 (Queue)
    //std::function : 가능한 모든 함수 또는 호출 가능한 객체를 담을 수 있는 식별자. 함수 자체를 변수에 넣어 전달하거나 큐에 보관할 수 있게 만들어줌.
    //-> void를 반환하는 형식의 함수를 queue에 저장할 수 있도록 함

    std::mutex queueMutex;                       // 큐 접근 보호용 뮤텍스
    //mutex : 데이터의 접근 가능 여부를 설정.(데이터 사용 중 스레드에 접근하지 못하도록 조정)

    std::condition_variable cv;                  // 일거리 신호 알림용
    //스레드가 작업이 없을때에도 무한반복하지 않도록 사용하지 않을 때에는 휴식상태로있다가, 신호를 받으면 작동하도록 함.

    bool stop = false;                           // 스케줄러 종료 플래그

    public:
    // 생성자: 스레드 개수 지정 (예: CPU 코어 수)
    SimpleJobScheduler(size_t threads) {
        for (size_t i = 0; i < threads; ++i) {
            // 지정한 개수만큼 스레드를 생성하여 대기 상태로 둠
            workers.emplace_back([this]() //emplace_back : 람다 함수형태의 일감을 스레드가 만들어지자마자 백그라운드에서 계속 실행
                //람다함수 : 
                {
                while (true)
                    {
                        std::function<void()> task; //작업 내 정보가 들어있기 때문에, 작업 종료후 소멸자를 타고 같이 해제되어 메모리자원을 아낄 수 있도록 while문 내에 작성
                        {
                            // 큐에 접근할 때 다른 스레드가 건드리지 못하게 Lock
                            std::unique_lock<std::mutex> lock(this->queueMutex);
                            //std::unique_lock : 자물쇠를 열고 잠그는 관리자(Wrapper)객체
                            //관리자객체 : 자원을(자물쇠,메모리 등)을 갖고 있다가 생성될 때 켜고, 소멸될 때 해제해주는 대리인 객체. Mutex관련해서는 std::unique_lock/lock_guard가 있으며 Mutex의 잠금과 해제 관리
                            // std::unique_lock : 고급 자물쇠 관리자. 원하는 시점에 lock.unlock()과 lock.lock()을 통해 수동으로 잠금 및 해제가 가능.
                            // std::lock_guard : 기본 자물쇠 관리자. 생성될 때 잠그고, 소멸될 때({}를 벗어날 때) 무조건 해제.
                            // 
                            //->해당 스레드가 작업중 다른 스레드가 접근하지 못하도록 queueMutex를 lock으로 변경


                            // 일거리가 들어오거나 stop 신호가 올 때까지 스레드를 재움 (CPU 점유율 0%)
                            //wait()내의 조건이 참일 때 까지 대기
                            //스레드 풀에서 전형적으로 쓰이는 패턴
                            this->cv.wait(lock, [this]()  //wait()는 조건이 참이 되었는지 반복 확인하여야하기 때문에 조건만 넘겨줄 경우 while을 돌려야함. 람다표현식으로 조건이 든 함수 자체를 넘겨주어 wait()가 알아서 반복확인을 할 수 있도록 함
                                {
                                return this->stop || !this->jobQueue.empty(); //스케줄러가 멈추었거나(종료해야할 때) 작업 큐 가 비어있지 않다면(일 해야할 때), 대기를 풀고 깨어남.
                                });
                            

                            // 종료 신호가 왔고 대기열이 비었으면 스레드 종료
                            if (this->stop && this->jobQueue.empty()) {
                            
                                return;
                            }

                            // 큐에서 일거리를 하나 꺼냄
                            task = std::move(this->jobQueue.front()); //std::move() : ()안에 전달된 메모리의 주소값을 새 변수가 가르키도록 하고, 기존에 가르키던 노드는 null로 바꿔 연결을 해제.
                            this->jobQueue.pop(); //null인 front()를 제거
                        } // lock 해제

                    // 일거리 실행 (9999 루프)
                    task();
                    }
                }
            );
        }
    }

    // 작업 등록 (Enqueue)
    void EnqueueJob(const JobWorkItem& job) {
        {
            std::unique_lock<std::mutex> lock(queueMutex);

            // lambda로 작업 감싸서 큐에 삽입
            jobQueue.emplace([job]() { job.Execute(); });
        }
        cv.notify_one(); // 자고 있는 일꾼 스레드 하나를 깨움
    }

    // 소멸자: 등록된 모든 작업이 끝날 때까지 기다린 후 스레드 정리
    ~SimpleJobScheduler() {
        {
            std::unique_lock<std::mutex> lock(queueMutex);
            stop = true;
        }
        cv.notify_all(); // 모든 스레드를 깨워서 종료하도록 함

        // 모든 일꾼 스레드가 끝날 때까지 대기 (Join)
        for (std::thread& worker : workers) { //범위기반 for문. :오른쪽 컨테이너에서 요소를 꺼네 왼쪽에 담아줌. 모든 요소를 돌 때 까지 반복.
            //thread객체는 복사가 불가능한 객체이기에 참조연산자 사용.
            if (worker.joinable()) {
                worker.join();
            }
        }
    }
};

int main() {
    int nFullCount = 4000;  // 총 작업 개수

    // CPU 코어 수만큼 스레드 생성 (하드웨어 동시성 활용)
    unsigned int maxConcurrency = std::thread::hardware_concurrency();
	//std::thread::hardward_concurrency() : 프로그램을 실행시킨 컴퓨터의 CPU가 동시에 처리할 수 있는 스레드(또는 코어) 수를 반환하는 함수 (concurrency : 동시성)

	//concurrency가 0이면(반환에 실패하면) 기본값 4로 설정
    if (maxConcurrency == 0)
    {
        maxConcurrency = 4;
    }

	//std 내에 많은 수많은 이름이 포함되어있어 이름충돌이 발생할 수 있으므로 지시어로 사용하지않고 명시적으로 사용(std::cout, std::endl)
    std::cout << "[C++ 스케줄러 시작] 총 작업: " << nFullCount
        << "개/동시 실행 스레드 : " << maxConcurrency << "개\n";

    auto startTime = std::chrono::high_resolution_clock::now();
	//auto : C++11에서 도입된 키워드. 컴파일러가 우측의 내용을 보고 변수의 타입을 자동으로 추론하도록 하는 기능.
	//위를 사용하지 않으면 std::chrono::high_resolution_clock::time_point startTime = std::chrono::high_resolution_clock::now(); 와 같이 작성해야함.
	//std::chrono : 시스템 시간과 관련된 기능을 제공하는 C++ 표준 라이브러리의 네임스페이스
	// high_resolution_clock : 컴퓨터에서 가장 높은 정밀도의 시계를 제공하는 클래스. 시간 측정에 사용.
	// high_resolution_clock::now() : 현재 시스템 시각을 측정하여 반환.
    //-> 작업 시작시간을 측정하여 startTime에 저장해놓음. 이후 작업종료시간을 측정해 작업에 걸린 시간을 계산하는데 사용

    {
        // 1. 스케줄러 생성 (중괄호 안에서 스케줄러 동작)
        SimpleJobScheduler scheduler(maxConcurrency);

        // 2. 4,000개 작업 큐에 투입
        for (int i = 0; i < nFullCount; ++i) {
            scheduler.EnqueueJob(JobWorkItem(i));
        }

        // 중괄호 '}'를 벗어나면서 scheduler의 소멸자(~SimpleJobScheduler)가 호출됨.
        // 소멸자 안에서 4,000개 작업이 모두 완료될 때까지 join()으로 기다림.
    }

    auto endTime = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime).count();

    std::cout << "[모든 작업 완료] 총 소요 시간: " << duration << "ms\n";

    return 0;
}