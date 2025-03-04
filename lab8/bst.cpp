#include "bst.h"

#include <stack>
#include <queue>
#include <set>
#include <vector>
#include <iostream>
#include <cstdlib>
#include <algorithm>
#include <climits>

int getHeight(Node *root) {
	if (root == nullptr) {
		return 0;
	}
	return 1 + std::max(getHeight(root->left), getHeight(root->right));
}

bool isBalanced(Node *root) {
	if (root == nullptr) {
		return true;
	}

	if(root->left == nullptr && root->right == nullptr) {
		return true;
	}

	if (root->left == nullptr) {
		return getHeight(root->right) == 1;
	}

	if (root->right == nullptr) {
		return getHeight(root->left) == 1;
	}

	return std::abs(getHeight(root->left) - getHeight(root->right)) <= 1 && isBalanced(root->left) && isBalanced(root->right);
	
}
