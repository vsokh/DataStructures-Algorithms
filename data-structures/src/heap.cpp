#include <iostream>
#include <algorithm>
#include "../inc/heap.hpp"

// Resources:
//   - https://www.wikiwand.com/en/Binary_heap#/Building_a_heap
//   - https://ocw.mit.edu/courses/electrical-engineering-and-computer-science/6-006-introduction-to-algorithms-fall-2011/lecture-videos/lecture-4-heaps-and-heap-sort/
Heap::Heap(std::vector<int> _A) : A(_A)
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
		std::swap(A[i], A[largest]);
		siftDown(largest);
	}
}

void Heap::siftUp(int i)
{
	int parent = i/2;
	if (A[parent] < A[i]) {
		std::swap(A[i], A[parent]);
		siftUp(parent);
	}
}

void Heap::heapify()
{
	for (int i = A.size()/2; i >= 0; --i)
		siftDown(i);
}

void Heap::push(int x)
{
	A.push_back(x);
	siftUp(A.size()-1);
}

void Heap::pop()
{
	if (A.empty()) return;

	std::swap(A[0], A[A.size()-1]);
	A.pop_back();
	siftDown(0);
}

int Heap::top()
{ return A.front(); }

bool Heap::empty()
{ return A.empty(); }

void Heap::print()
{
	for (int i : A)
		std::cout << i << " ";
	std::cout << std::endl;
}

