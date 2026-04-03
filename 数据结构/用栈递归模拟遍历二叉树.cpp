#include<iostream>
#include<vector>
#include<stack>
using namespace std;
struct TreeNode
{
	int val;
	TreeNode* left;
	TreeNode* right;
	TreeNode(int val):val(val), left(nullptr),right(nullptr) {};
};
class solution
{
private:
	stack<TreeNode*>stk;
	//左侧树枝一撸到底
	void pushlefttree(TreeNode* p)
	{
		while (p != nullptr)
		{
			//前序遍历位置
			stk.push(p);
			p = p->left;
		}
	}
public:
	vector<int>traverse(TreeNode* root)
	{
		TreeNode* visited = new TreeNode(-1);

		pushlefttree(root);

		while (!stk.empty())
		{
			TreeNode* p = stk.top();
			if ((p->left == nullptr || p->left == visited)&&p->right!=nullptr)
			{
				//中序遍历位置
				pushlefttree(p->right);
			}
			if (p->right == nullptr || p->right == visited)
			{
				//后序遍历位置
				visited = p;
				stk.pop();
			}
		}
	}
};