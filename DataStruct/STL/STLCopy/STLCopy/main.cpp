#include <cstddef>
#include <utility>
#include <initializer_list>
#include <stdexcept>
#include <new>


//요소추가, 인덱스 접근 및 수정/삭제, 요소삭제,
namespace MySTL 
{
	template<typename T> // T : Type의 첫글자에서 따옴. 들어오는 변수의 타입이 어떤 타입인지 나중에 정해질 것이라는 의미

	class Vector 
	{
		private T* data; //특정 타입의 메모리를 가르킬 포인터
		private capacity; //할당된 메모리 크기
		private size_t size; //저장된 데이터 개수

		public void PushBack(const T& val)
		{
			if (size == capacity)
			{
				size_t new_capacity = (capacity == 0) ? 2 : capacity * 2;

			}
		}
	};
}