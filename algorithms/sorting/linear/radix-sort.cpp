#include <bits/stdc++.h>

using namespace std;
using KeyGetter = std::function<int(vector<int> const& A, int i)>;

void printV(vector<int> const& v);

vector<int> countingSort(
		vector<int> const& A,
		int k,
		KeyGetter key);

vector<int> countingSortWithLists(
		vector<int> const& A,
		int k,
		KeyGetter key);

int log_a_to_base_b(int a, int b) {
	return log(a) / log(b);
}

KeyGetter radixKey(int m, int n) {
	return [m,n](vector<int> const& A, int i) {
		return (A[i]%m)/n;
	};
}

void radixSort(vector<int>& A, int r) {
	int k = *max_element(A.begin(), A.end());
	int d = log_a_to_base_b(k, r)+1;

	int m = r, n = 1;
	for (int i = 0; i < d; ++i) {
		//TODO: get rid of the assignment
		/* A = countingSortWithLists(A, r, radixKey(m, n)); */
		A = countingSort(A, r, radixKey(m, n));
		m *= r; n *= r;
	}
}

#ifdef radix_sort
int main() {
	cout << "Radix sort." << endl;
	{
		cout << "Base: 2."<<endl;

		vector<int> A{0, 1, 0, 0, 1};
		cout << "Before: "; printV(A);

		radixSort(A, 2);
		cout << "After: "; printV(A);

		cout << endl;
	}
	{
		cout << "Base: 10."<<endl;

		vector<int> A{9, 179, 139, 38, 10, 5, 36};
		cout << "Before: "; printV(A);

		radixSort(A, 10);
		cout << "After: "; printV(A);

		cout << endl;
	}
	return 0;
}
#endif

