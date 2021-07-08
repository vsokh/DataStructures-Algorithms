#include <iostream>

int naiveStringMatcher(std::string T, std::string P)
{
	int n = T.length();
	int m = P.length();
	for (int i = 0; i < n - m + 1; ++i)
	{
		if (T.substr(i, m) == P)
			return i;
	}
	return -1;
}

int main()
{
	{
		std::string T = "acaabc";
		std::string P = "aab";
		int shift = naiveStringMatcher(T, P);
		if (shift!=-1)
			std::cout << "Pattern occurs with shift " << shift << std::endl;
		else
			std::cout << "No such shift was found" << std::endl;
	}
	{
		std::string T = "acaabc";
		std::string P = "aca";
		int shift = naiveStringMatcher(T, P);
		if (shift!=-1)
			std::cout << "Pattern occurs with shift " << shift << std::endl;
		else
			std::cout << "No such shift was found" << std::endl;
	}
	{
		std::string T = "acaabc";
		std::string P = "a";
		int shift = naiveStringMatcher(T, P);
		if (shift!=-1)
			std::cout << "Pattern occurs with shift " << shift << std::endl;
		else
			std::cout << "No such shift was found" << std::endl;
	}
	{
		std::string T = "acaabc";
		std::string P = "";
		int shift = naiveStringMatcher(T, P);
		if (shift!=-1)
			std::cout << "Pattern occurs with shift " << shift << std::endl;
		else
			std::cout << "No such shift was found" << std::endl;
	}
	{
		std::string T = "acaabc";
		std::string P = "c";
		int shift = naiveStringMatcher(T, P);
		if (shift!=-1)
			std::cout << "Pattern occurs with shift " << shift << std::endl;
		else
			std::cout << "No such shift was found" << std::endl;
	}
	{
		std::string T = "acaabc";
		std::string P = "d";
		int shift = naiveStringMatcher(T, P);
		if (shift!=-1)
			std::cout << "Pattern occurs with shift " << shift << std::endl;
		else
			std::cout << "No such shift was found" << std::endl;
	}
	return 0;
}

