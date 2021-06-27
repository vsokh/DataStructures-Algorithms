#include "../../../data-structures/inc/binaryheap.hpp"
#include <vector>
#include <iostream>

// Resources:
//   - https://www.wikiwand.com/en/Heapsort
void heapsort(std::vector<int>& A)
{
	BinaryHeap h(A);
	int end = A.size();
	while (!h.empty()) {
		A[--end] = h.top(); h.pop();
	}
}

int main()
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
	return 0;
}
