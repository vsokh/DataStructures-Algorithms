#include <vector>
#include <iostream>

#include "binaryheap.hpp"

int main()
{
	{
		std::cout << "BinaryHeap.\n";
		BinaryHeap<int> h({4,3,1,7,5});
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
	}
	{
		auto printV = [](std::vector<int> const& A) {
			for (int i : A)
				std::cout << i << " ";
			std::cout << std::endl;
		};

		std::cout << "Heapsort.\n";
		std::vector<int> v{4,3,1,7,5};
		std::cout << "Before: "; printV(v);
		heapsort(v);
		std::cout << "After: "; printV(v);
	}
	return 0;
}
