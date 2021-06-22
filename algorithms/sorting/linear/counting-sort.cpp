#include <bits/stdc++.h>

using namespace std;
using KeyGetter = std::function<int(vector<int> const& A, int i)>;

void printV(vector<int> const& v) {
	for (auto i : v) cout << i << " ";
	cout << endl;
}

int defaultKey(vector<int> const& A, int i) {
	return A[i];
}

vector<int> countingSortWithLists(
		vector<int> const& A,
		int k,
		KeyGetter key = defaultKey)
{
	vector<vector<int>> L(k + 1);
	for (int i = 0; i < A.size(); ++i)
		L[key(A,i)].push_back(A[i]);

	vector<int> B;
	for (int i = 0; i < k + 1; ++i)
		for (auto j : L[i])
			B.push_back(j);
	return B;
}

vector<int> countingSort(
		vector<int> const& A,
		int k,
		KeyGetter key = defaultKey)
{
	vector<int> C(k+1);
	for (int j = 0; j<=A.size()-1; ++j)
		++C[key(A,j)];

	for (int i = 0; i<=k; ++i)
		C[i] = C[i]+C[i-1];

	vector<int> B(A.size());
	for (int j = A.size()-1; j >= 0; --j) {
		B[C[key(A, j)]-1] = A[j];
		--C[key(A, j)];
	}
	return B;
}

#ifdef count_sort
int main() {
	cout << "Counting sort." << endl;
	{
		cout << "CLRS version." << endl;

		vector<int> A = {2, 5, 3, 0, 2, 3, 0, 3};
		cout << "Before: "; printV(A);

		int const K = *max_element(A.begin(), A.end());
		cout << "K: " << K <<endl;

		vector<int> B = countingSort(A, K);
		cout << "After: "; printV(B);

		cout << endl;
	}
	{
		cout << "MIT version(with lists)." << endl;

		vector<int> A = {2, 5, 3, 0, 2, 3, 0, 3};
		cout << "Before: "; printV(A);

		int const K = *max_element(A.begin(), A.end());
		cout << "K: " << K <<endl;

		vector<int> B = countingSortWithLists(A, K);
		cout << "After: "; printV(B);

		cout << endl;
	}
	return 0;
}
#endif
