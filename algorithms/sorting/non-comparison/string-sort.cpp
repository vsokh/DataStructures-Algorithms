#include <bits/stdc++.h>

using namespace std;

template<typename T>
using KeyGetter = function<int(vector<T> const& A, int i)>;

template<typename T>
void printV(vector<T> const& v) {
	for (auto i : v) cout << i << " ";
	cout << endl;
}

template<typename T>
vector<T> countingSort(
		vector<T> const& A,
		int k,
		KeyGetter<T> key)
{
	vector<vector<T>> L(k + 1);
	for (int i = 0; i < A.size(); ++i) {
		L[key(A, i)].push_back(A[i]);

	vector<T> B;
    for (auto v : L)
		for (auto s : v)
            B.push_back(s);
	return B;
}

KeyGetter<string> stringKey(int k) {
	return [k] (vector<string> const& A, int i) {
		return  A[i][k] - 'A';
	};
}

void stringSort(vector<string>& A) {
	int k = A[0].length();
	for (int i = k-1; i >= 0; --i) {
		A = countingSort<string>(A, 'Z' - 'A', stringKey(i));
	}
}

int main() {
    vector<string> s{"COW","DOG","SEA","RUG","ROW","MOB","BOX","TAB","BAR","EAR","TAR","DIG", "BIG", "TEA", "NOW", "FOX"};
    stringSort(s);
    printV(s);
	return 0;
}

