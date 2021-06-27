#include "../inc/BST.hpp"
#include <iostream>

int main()
{
	std::cout << "BinarySearchTree:" << std::endl;
	{
		auto test = [](std::vector<int> v)
		{
			BinarySearchTree<int> bst;
			for (auto i : v)
			{
				std::cout << "insert: " << i << std::endl;
				bst.insert(i);
			}
			bst.print();
			std::cout << std::endl;

			for (auto i : v)
			{
				std::cout << "remove: " << i << std::endl;
				bst.remove(i);
			}
			bst.print();
			std::cout << std::endl;
		};
		test({2,1,3});
		test({1,3,2});
	}

	std::cout << "BSTSort:" << std::endl;
	{
		auto printV = [](std::vector<int> const& A) {
			for (int i : A)
				std::cout << i << " ";
			std::cout << std::endl;
		};
		std::vector<int> v{4,3,1,7,5};
		std::cout << "Before: "; printV(v);
		v = bstsort<int>(v);
		std::cout << "After: "; printV(v);
	}
	return 0;
}
