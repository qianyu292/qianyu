#include <functional>
#include <iostream>
#include <stdexcept>
#include <vector>
#include<string>
//链式segmentTree
// 线段树节点
class SegmentNode
{
public:
	int l, r;
	int mergeVal;
	SegmentNode* left;
	SegmentNode* right;
	SegmentNode(int mergeVal, int l, int r)
		: mergeVal(mergeVal), l(l), r(r), left(nullptr), right(nullptr) {
	}
};
class SegmentTree
{
private:
	SegmentNode* root;
	std::function<int(int, int)> merger;
	SegmentNode* build(const std::vector<int>& nums, int l, int r)
	{
		if (l == r)
		{
			return new SegmentNode(nums[l], l, r);
		}
		int mid = l + (r - l) / 2;
		SegmentNode* left = build(nums, l, mid);
		SegmentNode* right = build(nums, mid+1, r);
		SegmentNode* node = new SegmentNode(merger(left->mergeVal, right->mergeVal), l, r);
		node->left = left;
		node->right = right;
		return node;
	}
	void update(SegmentNode* node, int index, int value)
	{
		if (node->l == node->r)
		{
			node->mergeVal = value;
			return;
		}
		int mid = node->l + (node->r - node->l)/2;
		if (index <= mid)
		{
			update(node->left, index, value);
		}
		else
		{
			update(node->right, index, value);
		}
		node->mergeVal= merger(node->left->mergeVal, node->right->mergeVal);
	}
	int query(SegmentNode* node, int qL, int qR)
	{
		if (qL > qR) {
			throw std::invalid_argument("Invalid query range");
		}
		if (node->l == qL && node->r == qR)
		{
			return node->mergeVal;
		}
		int mid = node->l + (node->r - node->l) / 2;
		if (qR <= mid)
		{
			return query(node->left, qL, qR);
		}
		else if(qL>mid)
		{
			return query(node->right, qL, qR);
		}
		else
		{
			return merger(query(node->left, qL, mid),
				query(node->right, mid + 1, qR));
		}
	}
public:
	SegmentTree(const std::vector<int>& nums, std::function<int(int, int)> merger)
		: merger(merger) {
		root = build(nums, 0, nums.size() - 1);
	}

	void update(int index, int value) {
		update(root, index, value);
	}

	int query(int qL, int qR) {
		return query(root, qL, qR);
	}
};
/*int main()
{
	std::vector<int> arr = { 1, 3, 5, 7, 9 };
	// 示例，创建一棵求和线段树
	SegmentTree st(arr, [](int a, int b) { return a + b; });

	std::cout << st.query(1, 3) << std::endl; // 3 + 5 + 7 = 15
	st.update(2, 10);
	std::cout << st.query(1, 3) << std::endl; // 3 + 10 + 7 = 20

	return 0;
}*/
//数组实现线段树
#include <iostream>
#include <vector>
#include <functional>
#include <stdexcept>

class ArraySegmentTree {
    // 用数组存储线段树结构
    std::vector<int> tree;
    // 元素个数
    int n;
    std::function<int(int, int)> merger;

    // 定义：对 nums[l..r] 区间的元素构建线段树，rootIndex 是根节点
    void build(const std::vector<int>& nums, int l, int r, int rootIndex) {
        if (l == r) {
            // 区间内只有一个元素，设置为叶子节点
            tree[rootIndex] = nums[l];
            return;
        }

        // 从中间切分，递归构建左右子树
        int mid = l + (r - l) / 2;
        int leftRootIndex = leftChild(rootIndex);
        int rightRootIndex = rightChild(rootIndex);
        // 递归构建 nums[l..mid]，根节点为 leftRootIndex
        build(nums, l, mid, leftRootIndex);
        // 递归构建 nums[mid+1..r]，根节点为 rightRootIndex
        build(nums, mid + 1, r, rightRootIndex);

        // 后序位置，左右子树已经构建完毕，更新当前节点的聚合值
        tree[rootIndex] = merger(tree[leftRootIndex], tree[rightRootIndex]);
    }

    void update(int l, int r, int rootIndex, int index, int value) {
        // 当前节点为 rootIndex，对应的区间为 [l, r]
        // 去子树更新 nums[index] 为 value
        if (l == r) {
            // 找到了目标叶子节点，更新值
            tree[rootIndex] = value;
            return;
        }

        int mid = l + (r - l) / 2;
        if (index <= mid) {
            // 若 index 较小，则去左子树更新
            update(l, mid, leftChild(rootIndex), index, value);
        }
        else {
            // 若 index 较大，则去右子树更新
            update(mid + 1, r, rightChild(rootIndex), index, value);
        }

        // 后序位置，左右子树已经更新完毕，更新当前节点的聚合值
        tree[rootIndex] = merger(tree[leftChild(rootIndex)], tree[rightChild(rootIndex)]);
    }

    int query(int l, int r, int rootIndex, int qL, int qR) {
        if (qL == l && r == qR) {
            // 命中了目标区间，直接返回
            return tree[rootIndex];
        }

        int mid = l + (r - l) / 2;
        int leftRootIndex = leftChild(rootIndex);
        int rightRootIndex = rightChild(rootIndex);
        if (qR <= mid) {
            // node.l <= qL <= qR <= mid
            // 目标区间完全在左子树中
            return query(l, mid, leftRootIndex, qL, qR);
        }
        else if (qL > mid) {
            // mid < qL <= qR <= node.r
            // 目标区间完全在右子树中
            return query(mid + 1, r, rightRootIndex, qL, qR);
        }
        else {
            // node.l <= qL <= mid < qR <= node.r
            // 目标区间横跨左右子树
            // 将查询区间拆分成 [qL, mid] 和 [mid + 1, qR] 两部分，分别向左右子树查询
            return merger(query(l, mid, leftRootIndex, qL, mid),
                query(mid + 1, r, rightRootIndex, mid + 1, qR));
        }
    }
    //关键（因为线段树为满二叉树）
    int leftChild(int pos) {
        return 2 * pos + 1;
    }

    int rightChild(int pos) {
        return 2 * pos + 2;
    }

public:
    ArraySegmentTree(const std::vector<int>& nums, std::function<int(int, int)> mergeFunc)
        : n(nums.size()), merger(mergeFunc) {
        // 分配 4 倍数组长度的空间，存储线段树
        tree.resize(4 * n);
        build(nums, 0, n - 1, 0);
    }

    void update(int index, int value) {
        update(0, n - 1, 0, index, value);
    }

    int query(int qL, int qR) {
        if (qL < 0 || qR >= n || qL > qR) {
            throw std::invalid_argument("Invalid range: [" + std::to_string(qL) + ", " + std::to_string(qR) + "]");
        }
        return query(0, n - 1, 0, qL, qR);
    }
};

/*int main() {
    std::vector<int> arr = { 1, 3, 5, 7, 9 };
    // 示例，创建一棵求和线段树
    ArraySegmentTree st(arr, [](int a, int b) { return a + b; });

    std::cout << st.query(1, 3) << std::endl; // 3 + 5 + 7 = 15
    st.update(2, 10);
    std::cout << st.query(1, 3) << std::endl; // 3 + 10 + 7 = 20
    return 0;
}*/