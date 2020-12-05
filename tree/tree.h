#ifndef __TREE_H__
#define __TREE_H__

#include <iostream>
#include <vector>
using namespace std;

class TreeNode{
public:
	TreeNode* left;
	TreeNode* right;
	int val;
	TreeNode():left(NULL),right(NULL),val(0){}
	TreeNode(int n):left(NULL),right(NULL),val(n){}
	TreeNode(TreeNode* lc, TreeNode* rc, int n):left(lc),right(rc),val(n){}
};

/*
 * 由前序和中序，创建二叉树
 */
TreeNode* CreateTreeNodeByPreInOrder(vector<int> pre, vector<int> in);
void printVector(vector<int>& nums);

//1. 前中后序(递归)
vector<int> PreOrderRecursion(TreeNode* root);
vector<int> InOrderRecursion(TreeNode* root);
vector<int> PostOrderRecursion(TreeNode* root);
//2. 前中后序(非递归)
vector<int> PreOrder1(TreeNode* root);
vector<int> PreOrder2(TreeNode* root);
vector<int> InOrder(TreeNode* root);
vector<int> PostOrder1(TreeNode* root);
vector<int> PostOrder2(TreeNode* root);

#endif
