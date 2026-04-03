//图的BFS模板
/*
class State {
public:
    // 当前节点 ID
    int node;
    // 从起点 s 到当前节点的遍历步数
    int step;

    State(int node, int step) : node(node), step(step) {}
};

void bfs(const Graph& graph, int s) {
    vector<bool> visited(graph.size(), false); // [!code highlight]
    queue<State> q;

    q.push(State(s, 0));
    visited[s] = true; // [!code highlight]

    while (!q.empty()) {
        State state = q.front();
        q.pop();
        int cur = state.node;
        int step = state.step;
        cout << "visit " << cur << " with step " << step << endl;
        for (const Edge& e : graph.neighbors(cur)) {
            if (visited[e.to]) { // [!code highlight:5]
                continue;
            }
            q.push(State(e.to, step + 1));
            visited[e.to] = true;
        }
    }
}
*/