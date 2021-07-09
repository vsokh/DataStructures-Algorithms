#include <iostream>
#include <vector>
using namespace std;

const int UP		= -1;
const int LEFT		= -2;
const int UPLEFT	= -3;

std::string construct(std::vector<std::vector<int>> const& b, std::string X, int i, int j)
{
	if (i == 0 || j == 0)
		return "";

	std::string s = "";
	if (b[i][j] == UPLEFT)
	{
		s = construct(b, X, i-1, j-1);
		s += X[i-1];
	}
	else if (b[i][j] == UP)
		s = construct(b, X, i-1, j);
	else
		s = construct(b, X, i, j-1);
	return s;
}

void debug(
		std::vector<std::vector<int>> const& c,
		std::vector<std::vector<int>> const& b,
		int m, int n)
{
	cout << "UP = " << UP << ", LEFT = " << LEFT << ", UPLEFT = " << UPLEFT << endl;
	for (int i = 0; i <= m; ++i) {
		cout << i << ": ";
		for (int j = 0; j <= n; ++j) {
			cout << b[i][j]  << " ";
		}
		cout << endl;
	}
	for (int i = 0; i <= m; ++i) {
		cout << i << ": ";
		for (int j = 0; j <= n; ++j) {
			cout << c[i][j]  << " ";
		}
		cout << endl;
	}
}

std::string longestCommonSubsequence(std::string X, std::string Y)
{
	int m = X.length();
	int n = Y.length();

	std::vector<std::vector<int>> c(m+1, std::vector<int>(n+1));
	std::vector<std::vector<int>> b(m+1, std::vector<int>(n+1));

	for (int i = 1; i <= m; ++i) {
		for (int j = 1; j <= n; ++j) {
			if (X[i-1] == Y[j-1]) {
				c[i][j] = c[i-1][j-1]+1;
				b[i][j] = UPLEFT;
			}
			else if (c[i-1][j] >= c[i][j-1]) {
				c[i][j] = c[i-1][j];
				b[i][j] = UP;
			}
			else {
				c[i][j] = c[i][j-1];
				b[i][j] = LEFT;
			}
		}
	}
	debug(c, b, m, n);
	return construct(b, X, m, n);
}

int main()
{
	std::string X = "ABCBDAB";
	std::string Y = "BDCABA";
	std::cout << longestCommonSubsequence(X, Y) << std::endl;
	return 0;
}
