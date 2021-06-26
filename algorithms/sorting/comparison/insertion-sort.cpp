#include <vector>

using namespace std;

void printV(vector<int> const& v) {
	for (auto i : v) cout << i << " ";
	cout << endl;
}

void insertionSort(vector<int> &A) {
	int key, i;
	for (int j = 1; j < A.size(); ++j) {
		key = A[j];
		i = j - 1;
		while (i >= 0 && key < A[i]) {
			A[i + 1] = A[i];
			i = i - 1;
		}
		A[i + 1] = key;
	}
}

int main() {
	cout << "Insertion sort." << endl;
	vector<int> A = {5, 2, 4, 6, 1, 3};
	cout << "Before: "; printV(A);

	insertionSort(A);
	cout << "After: "; printV(A);
	return 0;
}
