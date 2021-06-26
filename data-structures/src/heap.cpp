#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

// Resources:
//   - https://www.wikiwand.com/en/Binary_heap#/Building_a_heap
//   - https://ocw.mit.edu/courses/electrical-engineering-and-computer-science/6-006-introduction-to-algorithms-fall-2011/lecture-videos/lecture-4-heaps-and-heap-sort/
Heap::Heap(vector<int> _A) : A(_A)
{ heapify(); }

void Heap::siftDown(int i)
{
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

void Heap::heapify()
{
	for (int i = A.size()/2; i >= 0; --i)
		siftDown(i);
}

void Heap::push(int x)
{ A.push_back(x); heapify(); }

bool Heap::empty()
{ return A.empty(); }

int Heap::top()
{ return A.front(); }

void Heap::print()
{ for (int i : A) { cout << i << " "; } cout << endl; }

void Heap::pop()
{
	if (A.empty()) return;

	swap(A[0], A[A.size()-1]);
	A.pop_back();
	heapify();
}
