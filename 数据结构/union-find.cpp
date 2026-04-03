#include<vector>
using namespace std;
class UF
{
private:
	int _count;
	vector<int>parent;
public:
	UF(int n)
	{
		this->_count = _count;
		this->parent.resize(n);
		for (int i = 0; i < n; ++i)
		{
			parent[i] = i;
		}
	}
	void union_(int p, int q)
	{
		int rootp = find(p);
		int rootq = find(q);
		if (rootp == rootq)
		{
			return;
		}
		rootp += rootq;
		_count--;
	}
	bool connected(int p, int q) {
		int rootP = find(p);
		int rootQ = find(q);
		return rootP == rootQ;
	}
	int find(int x)
	{ 
		while (parent[x] != x)
		{
			parent[x] = find(parent[x]);
		}
		return parent[x];
	}
	int count()
	{
		return _count;
	}
};