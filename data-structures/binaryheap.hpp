#pragma once
#include <vector>
#include <functional>

// Resources:
//   - https://www.wikiwand.com/en/Binary_heap#/Building_a_heap
//   - https://ocw.mit.edu/courses/electrical-engineering-and-computer-science/6-006-introduction-to-algorithms-fall-2011/lecture-videos/lecture-4-heaps-and-heap-sort/

template<typename T, typename Comp = std::less<T>>
class BinaryHeap {
	private:
		Comp comp;
		std::vector<T> A;

	public:
		BinaryHeap(std::vector<T> _A) : A(_A) { heapify(); }

		void push(T const& x)
		{
			A.push_back(x);
			siftUp(A.size()-1);
		}

		void pop()
		{
			if (A.empty()) return;

			std::swap(A[0], A[A.size()-1]);
			A.pop_back();
			siftDown(0);
		}

		int top()
		{ return A.front(); }

		bool empty()
		{ return A.empty(); }

		void print()
		{
			for (T const& i : A)
				std::cout << i << " ";
			std::cout << std::endl;
		}

	private:
		void siftDown(int i)
		{
			int left	= 2*i+1;
			int right	= 2*i+2;
			int largest = i;

			if (left < A.size() && comp(A[largest], A[left]))
				largest = left;

			if (right < A.size() && comp(A[largest], A[right]))
				largest = right;

			if (largest != i) {
				std::swap(A[i], A[largest]);
				siftDown(largest);
			}
		}
		void siftUp(int i)
		{
			int parent = i/2;
			if (comp(A[parent], A[i])) {
				std::swap(A[i], A[parent]);
				siftUp(parent);
			}
		}
		void heapify()
		{
			for (int i = A.size()/2; i >= 0; --i)
				siftDown(i);
		}

};

template<typename T>
void heapsort(std::vector<T>& A)
{
	BinaryHeap<T> h(A);
	int end = A.size();
	while (!h.empty()) {
		A[--end] = h.top(); h.pop();
	}
}

