#include <vector>
#include "../data-structures/heap.hpp"

// Resources:
//   - https://www.wikiwand.com/en/Heapsort
void heapsort(vector<int>& A)
{
	Heap h(A);
	int end = A.size();
	while (!h.empty()) {
		A[--end] = h.top(); h.pop();
	}
}

int main()
{
	auto printV = [](vector<int> const& A) {
		for (int i : A) cout << i << " ";
		cout << endl;
	};

	cout << "Heapsort." << endl;
	vector<int> v{4,3,1,7,5};
	cout << "Before: "; printV(v);
	heapsort(v);
	cout << "After: "; printV(v);
	return 0;
}
