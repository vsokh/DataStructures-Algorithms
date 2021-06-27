#include <vector>
#include <iostream>
#include "../inc/binaryheap.hpp"

int main()
{
	std::cout << "BinaryHeap.\n";
	BinaryHeap h({4,3,1,7,5});
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

	h.push(15);
	h.print();
	return 0;
}
