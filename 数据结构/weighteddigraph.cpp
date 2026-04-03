//有向加权图(邻接表)
#include<iostream>
#include<stdexcept>
#include<vector>
using namespace std;

class weighteddigraph
{
public:
	struct edge
	{
		int to;
		int weight;
		edge(int to, int weight) 
		{
			this->to = to;
			this->weight = weight;
		}
	};
private:
	vector<vector<edge>>graph;
public:
	//创造节点
	weighteddigraph(int n)
	{
		graph = vector<vector<edge>>(n);
	}
	void addedge(int from,int to, int weight)
	{
		graph[from].emplace_back(to, weight);
	}
	void removeedge(int from,int to)
	{
		for (auto it = graph[from].begin(); it != graph[from].end(); ++it)
		{
			if (it->to == to)
			{
				graph[from].erase(it);
				break;
			}
		}
	}
	bool hasedge(int from, int to)
	{
		for (const auto& a : graph[from])
		{
			if (a.to == to)
				return true;
		}
		return false;
	}
	int weight(int from, int to)
	{
		for (const auto& e : graph[from])
		{
			if (e.to == to)
			{
				return e.weight;
			}
		}
		throw invalid_argument("No such edge");
	}
	const vector<edge>neighbors(int v)
	{
		return graph[v];
	}
};
/*int main() {
	weighteddigraph graph(3);
	graph.addedge(0, 1, 1);
	graph.addedge(1, 2, 2);
	graph.addedge(2, 0, 3);
	graph.addedge(2, 1, 4);

	cout << boolalpha << graph.hasedge(0, 1) << endl; // true
	cout << boolalpha << graph.hasedge(1, 0) << endl; // false

	for (const auto& edge : graph.neighbors(2)) {
		cout << "2 -> " << edge.to << ", wight: " << edge.weight << endl;
	}
	// 2 -> 0, wight: 3
	// 2 -> 1, wight: 4

	graph.removeedge(0, 1);
	cout << boolalpha << graph.hasedge(0, 1) << endl; // false

	return 0;
}*/