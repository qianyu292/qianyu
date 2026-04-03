#include <iostream>
#include <vector>
// 加权有向图的通用实现（邻接矩阵）
class WeightedDigraph {
public:
    // 存储相邻节点及边的权重
    struct Edge {
        int to;
        int weight;

        Edge(int to, int weight) : to(to), weight(weight) {}
    };

    WeightedDigraph(int n) {
        matrix = std::vector<std::vector<int>>(n, std::vector<int>(n, 0));
    }

    // 增，添加一条带权重的有向边，复杂度 O(1)
    void addEdge(int from, int to, int weight) {
        matrix[from][to] = weight;
    }

    // 删，删除一条有向边，复杂度 O(1)
    void removeEdge(int from, int to) {
        matrix[from][to] = 0;
    }

    // 查，判断两个节点是否相邻，复杂度 O(1)
    bool hasEdge(int from, int to) {
        return matrix[from][to] != 0;
    }

    // 查，返回一条边的权重，复杂度 O(1)
    int weight(int from, int to) {
        return matrix[from][to];
    }

    // 查，返回某个节点的所有邻居节点，复杂度 O(V)
    std::vector<Edge> neighbors(int v) {
        std::vector<Edge> res;
        for (int i = 0; i < matrix[v].size(); i++) {
            if (matrix[v][i] != 0) {
                res.push_back(Edge(i, matrix[v][i]));
            }
        }
        return res;
    }

private:
    // 邻接矩阵，matrix[from][to] 存储从节点 from 到节点 to 的边的权重
    // 0 表示没有连接
    std::vector<std::vector<int>> matrix;
};