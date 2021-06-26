#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

// Resources:
//   - https://www.wikiwand.com/en/Binary_heap#/Building_a_heap
//   - https://ocw.mit.edu/courses/electrical-engineering-and-computer-science/6-006-introduction-to-algorithms-fall-2011/lecture-videos/lecture-4-heaps-and-heap-sort/
class Heap {
	public:
		Heap(vector<int> _A);

		void siftDown(int i);
		void heapify();

		void push(int x);
		void pop();

		int top();

		bool empty();

		void print();

	private:
		vector<int> A;
};
