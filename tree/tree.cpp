#include <stack>
#include <algorithm>
#include "tree.h"

/*
 * 二叉树的遍历
 * 前序：中 左 右
 * 中序：左 中 右
 * 后序：左 右 中
 */
/* 前序 递归 */
vector<int> PreOrderRecursion(TreeNode* root)
{
	vector<int> res;
	if(root == nullptr){
		return res;
	}
	res.push_back(root->val);
	if(root->left != nullptr) {
		vector<int> leftres = PreOrderRecursion(root->left);
		res.insert(res.end(), leftres.begin(), leftres.end());
	}
	if(root->right != nullptr) {
		vector<int> rightres = PreOrderRecursion(root->right);
		res.insert(res.end(), rightres.begin(), rightres.end());
	}
	
	return res;
}

/* 中序 递归 */
vector<int> InOrderRecursion(TreeNode* root)
{
	vector<int> res;
	if(root == nullptr){
		return res;
	}
	if(root->left != nullptr) {
		vector<int> leftres = InOrderRecursion(root->left);
		res.insert(res.end(), leftres.begin(), leftres.end());
	}
	res.push_back(root->val);
	if(root->right != nullptr) {
		vector<int> rightres = InOrderRecursion(root->right);
		res.insert(res.end(), rightres.begin(), rightres.end());
	}
	
	return res;
}

/* 后序 递归 */
vector<int> PostOrderRecursion(TreeNode* root)
{
	vector<int> res;
	if(root == nullptr){
		return res;
	}
	if(root->left != nullptr) {
		vector<int> leftres = PostOrderRecursion(root->left);
		res.insert(res.end(), leftres.begin(), leftres.end());
	}
	if(root->right != nullptr) {
		vector<int> rightres = PostOrderRecursion(root->right);
		res.insert(res.end(), rightres.begin(), rightres.end());
	}
	res.push_back(root->val);
	
	return res;
}

/* 前序 非递归 1
 * 
 * 利用stack先进后出的特点：
 * 前序是 中 左 右。
 * 所以，先输出父节点，然后将右孩子 左孩子依次压入stack。 
 * 下次取出的顺序就是先左，后右了。
 */
vector<int> PreOrder1(TreeNode* root)
{
	vector<int> res;
	if(root == nullptr) {
		return res;	
	}
	std::stack<TreeNode*> st;
	st.push(root);
	while(!st.empty()){
		TreeNode* tmp = st.top();
		st.pop();
		res.push_back(tmp->val);
		if(tmp->right){
			st.push(tmp->right);
		}
		if(tmp->left){
			st.push(tmp->left);
		}
	}
	return res;
}

/*
 * 就按中 左 右的顺序来的。
 * 当前节点不为空，就把当前节点压栈，再处理其左节点，一直把左子树处理完。
 * 左孩子为空了，就把栈顶的（左孩子的父节点）弹出，
 * 就是 中和左都处理了，再把右孩子压进去。
 *
 */
vector<int> PreOrder2(TreeNode* root)
{
	vector<int> res;
	std::stack<TreeNode*> st;
	while(root || !st.empty()) {
		if(root){
			res.push_back(root->val);
			st.push(root);
			root = root->left;
		}else{
			root = st.top();
			st.pop();
			root = root->right;
		}

	}
	return res;
}


vector<int> InOrder(TreeNode* root)
{
	vector<int> res;
	std::stack<TreeNode*> st;
	while(root || !st.empty()){
		if(root){
			st.push(root);
			root = root->left;
		}else{
			root = st.top();
			res.push_back(root->val);
			st.pop();
			root = root->right;
		}
	}
	return res;
}

/*
 * pre指向上一次输出的节点。
 * 先把所有的左节点压入栈，
 * 处理完左子树，
 * 再把右子树，通过pre来判断右节点是不是已经处理了。
 * 要是右节点也被处理了，就把栈顶的处理后，弹出。
 * 继续向上处理。
 */
vector<int> PostOrder1(TreeNode* root)
{
	vector<int> res;
	TreeNode* pre = nullptr;
	std::stack<TreeNode*> st;

	while(root || !st.empty()){
		while(root && root != pre){
			st.push(root);
			root = root->left;
		}
		if(st.empty())
			break;
		root = st.top();
		if(root->right && root->right != pre){
			root = root->right;
		} else {
			st.pop();
			res.push_back(root->val);
			pre = root;
		}

	}

	return res;
}

/*
 * 前序：中 左 右
 * 后序：左 右 中，就是 中 右 左的逆序，所以可以参考前序的方法 
 */
vector<int> PostOrder2(TreeNode* root)
{
	vector<int> res;
	std::stack<TreeNode*> st;
	if(root) {
		st.push(root);
	}
	while(!st.empty()){
		root = st.top();
		res.push_back(root->val);
		st.pop();
		if(root->left) st.push(root->left);
		if(root->right) st.push(root->right);
	}

	reverse(res.begin(), res.end());

	return res;
}



/*
 * 构建二叉树：（需要个节点元素值不一样）
 *	已知前序遍历和中序遍历序列，可以唯一确定一棵二叉树。
 *	已知后序遍历和中序遍历序列，可以唯一确定一棵二叉树。
 *	需要注意的是，已知前序和后序遍历，是不能确定一棵二叉树的。
 */
TreeNode* CreateTreeNodeByPreInOrder(vector<int> pre, vector<int> in)
{
	if(pre.size() != in.size()){
		cout<<"it is a bad tree 1\n";
		return NULL;
	}
	
	TreeNode* root = new TreeNode(pre[0]);
	auto it = find(in.begin(), in.end(), pre[0]);
	if(it == in.end()){
		cout<<"it is a bad tree 2\n";
		return NULL;
	}
	if(it != in.begin()) {
		vector<int> leftin(in.begin(), it);
		vector<int> leftpre(pre.begin()+1, pre.begin()+1+leftin.size());
		root->left = CreateTreeNodeByPreInOrder(leftpre, leftin);
	}
	if(it != in.end()-1){
		vector<int> rightin(it + 1, in.end());
		vector<int> rightpre(pre.end()-rightin.size(), pre.end());
		root->right = CreateTreeNodeByPreInOrder(rightpre, rightin);
	}

	return root;
}

void printVector(vector<int>& nums)
{
    for(auto a:nums){
        cout<<a<<" ";
    }
    cout<<endl;
}

int main()
{
	vector<int> pre{1,2,3};
	vector<int> in{1,3,2};

	TreeNode* root = CreateTreeNodeByPreInOrder(pre, in);
	vector<int> res = PreOrderRecursion(root);
	cout<<"PreOrderRecursion: ";
	printVector(res);

	res = InOrderRecursion(root);
	cout<<"InOrderRecursion: ";
	printVector(res);

	res = PostOrderRecursion(root);
	cout<<"PostOrderRecursion: ";
	printVector(res);

	res = PreOrder1(root);
	cout<<"PreOrder1: ";
	printVector(res);

	res = PreOrder2(root);
	cout<<"PreOrder2: ";
	printVector(res);

	res = InOrder(root);
	cout<<"InOrder: ";
	printVector(res);

	res = PostOrder1(root);
	cout<<"PostOrder1: ";
	printVector(res);

	res = PostOrder2(root);
	cout<<"PostOrder2: ";
	printVector(res);

	return 0;
}



