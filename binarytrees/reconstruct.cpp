#include <iostream>
#include "BNode.h"

/* Reconstructs a binary tree given a pre-order and in-order */

BNode * reconstruct(const std::vector<int> pre, const std::vector<int> in) {
	BNode *root = new BNode(pre[0]);
	if (pre.size() == 1) {
		return root;
	} else if (pre.size() == 2) {
		if (pre[1] == in[0]) {
			root->left = new BNode(in[0]);
		} else if (pre[1] == in[1]) {
			root->right = new BNode(in[1]);
		}
		return root;
	}
	int in_pos = 0;
	for (int i = 0; i < in.size(); ++i)
		if (pre[0] == in[i]) in_pos = i; break;

	root->left = std::vector<int> in_left(&in[0], &in[in_pos - 1]);
	root->right = std::vector<int> in_right(&in[in_pos + 1], &in[in.size()]);
	return root;
}

int main() {}