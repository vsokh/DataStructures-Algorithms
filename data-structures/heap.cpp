#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

// Resources:
//   - https://www.wikiwand.com/en/Binary_heap#/Building_a_heap
//   - https://ocw.mit.edu/courses/electrical-engineering-and-computer-science/6-006-introduction-to-algorithms-fall-2011/lecture-videos/lecture-4-heaps-and-heap-sort/
class Heap {
	public:
		Heap(vector<int> _A) : A(_A)
		{ heapify(); }

		void siftDown(int i) {
			int left	= 2*i+1;
			int right	= 2*i+2;
			int largest = i;

			if (left < A.size() && A[left] > A[largest])
				largest = left;

			if (right < A.size() && A[right] > A[largest])
				largest = right;

			if (largest != i) {
				swap(A[i], A[largest]);
				siftDown(largest);
			}
		}

		void heapify() {
			for (int i = A.size()/2; i >= 0; --i)
				siftDown(i);
		}

		void push(int x)
		{ A.push_back(x); heapify(); }

		bool empty()
		{ return A.empty(); }

		int top()
		{ return A.front(); }

		void print()
		{ for (int i : A) { cout << i << " "; } cout << endl; }

		void pop() {
			if (A.empty()) return;

			swap(A[0], A[A.size()-1]);
			A.pop_back();
			heapify();
		}

	private:
		vector<int> A;
};

// Resources:
//   - https://www.wikiwand.com/en/Heapsort
void heapsort(vector<int>& A) {
	Heap h(A);
	int end = A.size();
	while (!h.empty()) {
		A[--end] = h.top(); h.pop();
	}
}

int main() {
	{
		cout << "Heap." << endl;
		Heap h({4,3,1,7,5});
		h.print();

		h.pop();
		h.print();

		h.push(8);
		h.print();

		h.push(1);
		h.print();

		h.push(9);
		h.print();

		h.pop();
		h.print();
	}

	auto printV = [](vector<int> const& A) {
		for (int i : A) cout << i << " ";
		cout << endl;
	};

	{
		cout << "Heapsort." << endl;
		vector<int> v{4,3,1,7,5};
		cout << "Before: "; printV(v);
		heapsort(v);
		cout << "After: "; printV(v);
	}
	return 0;
}
