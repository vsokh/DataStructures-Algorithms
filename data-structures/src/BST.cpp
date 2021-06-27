#include "../inc/BST.hpp"
#include <iostream>

BinarySearchTree::Node::Node(int _val,
		Node* _parent = nullptr,
		Node* _left = nullptr,
		Node* _right = nullptr)
	: val(_val) , parent(_parent) , left(_left) , right(_right)
{}

BinarySearchTree::~BinarySearchTree()
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

void BinarySearchTree::insert(int x)
{ insert(root, x, nullptr); }

void BinarySearchTree::remove(int x)
{ remove(root, x); }

bool BinarySearchTree::contains(int x)
{ return find(root, x) != nullptr; }

void BinarySearchTree::inorderTraversal(Callback cb)
{ inorderTraversal(root, cb); }

void BinarySearchTree::print()
{
	auto print = [](int x)
	{ std::cout << x << " "; };

	inorderTraversal(print);
}

BinarySearchTree::Node*
BinarySearchTree::findMin(Node* root)
{
	Node *n = root;
	while (n->left != nullptr)
		n = n->left;
	return n;
}

BinarySearchTree::Node*
BinarySearchTree::find(Node* root, int x)
{
	Node *n = root;
	while (n != nullptr && n->val != x)
	{
		if (x < n->val)
			n = n->left;
		else
			n = n->right;
	}
	return n;
}

void BinarySearchTree::insert(Node*& n, int x, Node* parent)
{
	if (n != nullptr && x == n->val)
		return;
	if (n == nullptr)
		n = new Node(x, parent);
	else if (x < n->val)
		insert(n->left, x, n);
	else
		insert(n->right, x, n);
}

void BinarySearchTree::remove(Node*& n, int x)
{
	// TODO: refactor
	if (n == nullptr)
		return;
	if (x < n->val) {
		remove(n->left, x);
		return ;
	}
	if (x > n->val) {
		remove(n->right, x);
		return ;
	}

	if (n->right != nullptr && n->left != nullptr)
	{
		Node* successor = findMin(n->right);
		std::swap(n->val, successor->val);
		remove(successor, x);
		return;
	}
	else if (n->left != nullptr)
	{
		std::swap(n->val, n->left->val);
		remove(n->left, x);
		return;
	}
	else if (n->right != nullptr)
	{
		std::swap(n->val, n->right->val);
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

void BinarySearchTree::inorderTraversal(Node* n, Callback cb)
{
	if (n == nullptr) return;

	inorderTraversal(n->left, cb);
	cb(n->val);
	inorderTraversal(n->right, cb);
}

std::vector<int> bstsort(std::vector<int> const& v)
{
	BinarySearchTree bst;
	for (auto i : v)
		bst.insert(i);

	std::vector<int> result;

	auto addToResult = [&result](int x)
	{ result.push_back(x); };

	bst.inorderTraversal(addToResult);

	return result;
}

