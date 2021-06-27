#pragma once

#include <functional>
#include <vector>

//https://www.wikiwand.com/en/Binary_search_tree
class BinarySearchTree
{
	private:
		using Callback = std::function<void(int)>;

		struct Node
		{
			int val;
			Node *parent, *left, *right;

			// TODO: five-rule ;)
			Node(int _val,
					Node* _parent,
					Node* _left,
					Node* _right);
		};

		Node *root = nullptr;

	public:
		// TODO: five-rule ;)
		~BinarySearchTree();

		void insert(int x);
		void remove(int x);
		bool contains(int x);

		void inorderTraversal(Callback cb);

		void print();

	private:
		Node* findMin(Node* root);
		Node* find(Node* root, int x);
		/* void insert(Node*& n, int x, Node* parent); */
		void insert(Node*& n, int x, Node* parent);
		void remove(Node*& n, int x);
		void inorderTraversal(Node* n, Callback cb);
};

std::vector<int> bstsort(std::vector<int> const& v);
