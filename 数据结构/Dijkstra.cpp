#include <iostream>
#include <vector>
#include <queue>
#include <climits>
using namespace std;

typedef pair<int, int> pii; // (距离, 顶点)

class Graph {
private:
    int V; // 顶点数
    vector<vector<pii>> adj; // 邻接表: 每个顶点存储(邻居顶点, 边权重)

public:
    Graph(int vertices) : V(vertices) {
        adj.resize(V);
    }

    // 添加有向边
    void addEdge(int u, int v, int weight) {
        adj[u].push_back({ v, weight });
    }

    // 添加无向边
    void addUndirectedEdge(int u, int v, int weight) {
        addEdge(u, v, weight);
        addEdge(v, u, weight);
    }
    vector<int>dijkstra(int src)
    {
        vector<int>dist(V, INT_MAX);

        priority_queue<pii, vector<pii>, greater<pii>>pq;

        dist[src] = 0;
        pq.push({0,src});
        while (!pq.empty())
        {
            int u = pq.top().second;
            int current_dist = pq.top().first;
            pq.pop();
            if(current_dist>dist[u])
            {
                continue;
            }
            for (const auto& neighbor : adj[u])
            {
                int v = neighbor.first;
                int weight = neighbor.second;
                if (dist[u] + weight < dist[v])
                {
                    dist[v] = dist[u] + weight;
                    pq.push({ dist[v],v });
                }
            }
        }
        return dist;
    }
    void printShortestPaths(int src) {
        vector<int> dist = dijkstra(src);

        cout << "从顶点 " << src << " 到各顶点的最短距离:\n";
        for (int i = 0; i < V; i++) {
            if (dist[i] == INT_MAX) {
                cout << "顶点 " << i << ": 不可达\n";
            }
            else {
                cout << "顶点 " << i << ": " << dist[i] << "\n";
            }
        }
    }
};