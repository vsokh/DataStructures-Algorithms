#pragma once

#include <functional>
#include <vector>
#include <iostream>

//https://www.wikiwand.com/en/Binary_search_tree

template<typename T, typename Comp = std::less<T>>
class BinarySearchTree
{
	private:
		using Callback = std::function<void(T)>;

		struct Node
		{
			T key;
			Node *parent, *left, *right;

			Node(T const& _key = T(), Node* _parent = nullptr)
				: key(_key), parent(_parent) , left(nullptr) , right(nullptr) {}
		} *root = nullptr;

	public:
		// TODO: five-rule
		~BinarySearchTree()
		{
			std::function<void(Node*& n)> clear =
				[&](Node*& n)
				{
					if (n == nullptr)
						return;

					clear(n->left);
					clear(n->right);
					delete n; n = nullptr;
				};
			clear(root);
		}

		void insert(T x)
		{ insert(root, x, nullptr); }

		void remove(T x)
		{ remove(root, x); }

		bool contains(T x)
		{ return find(root, x) != nullptr; }

		void inorderTraversal(Callback cb)
		{ inorderTraversal(root, cb); }

		void print()
		{
			auto _print = [](T x)
			{ std::cout << x << " "; };

			inorderTraversal(_print);
		}

	private:
		Node* findMin(Node* root)
		{
			Node *n = root;
			while (n->left != nullptr)
				n = n->left;
			return n;
		}
		Node* find(Node* root, T x)
		{
			Node *n = root;
			while (n != nullptr && n->key != x)
			{
				if (x < n->key)
					n = n->left;
				else
					n = n->right;
			}
			return n;
		}
		void insert(Node*& n, T x, Node* parent)
		{
			if (n != nullptr && x == n->key)
				return;
			if (n == nullptr)
				n = new Node(x, parent);
			else if (x < n->key)
				insert(n->left, x, n);
			else
				insert(n->right, x, n);
		}
		void remove(Node*& n, T x)
		{
			// TODO: refactor
			if (n == nullptr)
				return;
			if (x < n->key) {
				remove(n->left, x);
				return ;
			}
			if (x > n->key) {
				remove(n->right, x);
				return ;
			}

			if (n->right != nullptr && n->left != nullptr)
			{
				Node* successor = findMin(n->right);
				std::swap(n->key, successor->key);
				remove(successor, x);
				return;
			}
			else if (n->left != nullptr)
			{
				std::swap(n->key, n->left->key);
				remove(n->left, x);
				return;
			}
			else if (n->right != nullptr)
			{
				std::swap(n->key, n->right->key);
				remove(n->right, x);
				return;
			}
			if (n->parent) {
				if (n->parent->left == n)
					n->parent->left = nullptr;
				else
					n->parent->right = nullptr;
			}
			delete n; n = nullptr;
		}
		void inorderTraversal(Node* n, Callback cb)
		{
			if (n == nullptr) return;

			inorderTraversal(n->left, cb);
			cb(n->key);
			inorderTraversal(n->right, cb);
		}
};

template<typename T>
std::vector<T> bstsort(std::vector<T> const& v)
{
	BinarySearchTree<T> bst;
	for (auto i : v)
		bst.insert(i);

	std::vector<T> result;

	auto addToResult = [&result](T x)
	{ result.push_back(x); };

	bst.inorderTraversal(addToResult);

	return result;
}

