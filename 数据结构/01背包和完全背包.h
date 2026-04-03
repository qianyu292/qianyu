#include <vector>
#include <algorithm>
using namespace std;
// 01背包：二维数组版本（易于理解）
int knapsack_01_2d(int V, vector<int>& v, vector<int>& w) {
    int n = v.size();
    vector<vector<int>> dp(n + 1, vector<int>(V + 1, 0));

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= V; j++) {
            if (j < v[i - 1]) {
                dp[i][j] = dp[i - 1][j];
            }
            else {
                dp[i][j] = max(dp[i - 1][j], dp[i - 1][j - v[i - 1]] + w[i - 1]);
            }
        }
    }
    return dp[n][V];
}

// 01背包：一维数组优化版本（空间优化）
int knapsack_01_1d(int V, vector<int>& v, vector<int>& w) {
    int n = v.size();
    vector<int> dp(V + 1, 0);

    for (int i = 0; i < n; i++) {
        // 注意：必须逆序遍历，确保每个物品只被使用一次
        for (int j = V; j >= v[i]; j--) {
            dp[j] = max(dp[j], dp[j - v[i]] + w[i]);
        }
    }
    return dp[V];
}
int complete_knapsack_2d(int V, vector<int>& v, vector<int>& w) {
    int n = v.size();
    vector<vector<int>> dp(n + 1, vector<int>(V + 1, 0));

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= V; j++) {
            if (j < v[i - 1]) {
                dp[i][j] = dp[i - 1][j];
            }
            else {
                // 与01背包的区别：可以从dp[i][j-v[i-1]]转移，表示可以重复选择当前物品
                dp[i][j] = max(dp[i - 1][j], dp[i][j - v[i - 1]] + w[i - 1]);
            }
        }
    }
    return dp[n][V];
}

// 完全背包：一维数组优化版本
int complete_knapsack_1d(int V, vector<int>& v, vector<int>& w) {
    int n = v.size();
    vector<int> dp(V + 1, 0);

    for (int i = 0; i < n; i++) {
        // 注意：必须正序遍历，允许物品被重复选择
        for (int j = v[i]; j <= V; j++) {
            dp[j] = max(dp[j], dp[j - v[i]] + w[i]);
        }
    }
    return dp[V];
}
