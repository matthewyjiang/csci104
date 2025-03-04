#ifndef BST_H
#define BST_H

#include <vector>

class Node {
public:
	Node(Node *left_, Node *right, int key) {
		this->left_ = left_;
		this->right = right;
		this->key = key;
	};

	Node(int key) {
		this->left_ = nullptr;
		this->right = nullptr;
		this->key = key;
	}

    Node *left_;
    Node *right;
    int key;
};

bool isBalanced(Node *root);

#endif