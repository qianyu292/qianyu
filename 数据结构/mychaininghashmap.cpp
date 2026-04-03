#include<iostream>
#include<list>
#include<vector>
#include<string>
template<typename K,typename V>
class MyChainingHashMap
{
	struct KVnode
	{
		K key;
		V value;
		KVnode(K key, V val) :key(key), value(std::move(val)) {};
	};
	std::vector<std::list<KVnode>>table;

	int size;

	static constexpr int INIT_CAP = 4;

	int hash(K key)
	{
		return (std::hash<K>{}(key) & 0x7fffffff) % table.size();
	}
	void resize(int newcap)
	{
		newcap = std::max(newcap, 1);
		MyChainingHashMap<K, V> newMap(newcap);
		// 穷举当前 HashMap 中的所有键值对
		for (auto& list : table) {
			for (auto& node : list) {
				// 将键值对转移到新的 HashMap 中
				newMap.put(node.key, node.value);
			}
		}
		// 将当前 HashMap 的底层 table 换掉
		this->table = newMap.table;
	}
public:
	MyChainingHashMap() : MyChainingHashMap(INIT_CAP) {
	}
	explicit MyChainingHashMap(int capacity)
	{
		size= 0;
		capacity = std::max(capacity, 1);
		table.resize(capacity);
	}
	//增
	void put(K key, V val)
	{
		auto& list = table[hash(key)];
		for (auto& node : list)
		{
			if (node.key == key)
			{
				node.value = val;
				return;
			}
		}
		list.emplace_back(key, val);
		size++;
		if (size >= table.size() * 0.75)
			resize(table.size() * 2);
	}
	//删
	void remove(K key)
	{
		auto& list = table[hash(key)];
		for (auto it = list.begin(); it != list.end();it++)
		{
			if (it->key == key)
			{
				list.erase(it);
				size--;

				if (size < table.size() / 8)
				{
					resize(table.size() / 4);
				}
				return;
			}
		}
	}
	//查
	V get(K key)
	{
		auto& list = table[hash(key)];
		for (const auto& node : list)
		{
			if (node.key == key)
			{
				return node.value;
			}
		}
		return V();
	}
	//返回所有key
	std::list<K>keys()
	{
		std::list<K>keys;
		for (const auto& list : table)
		{
			for (const auto& node : list)
			{
				keys.push_back(node.key);
			}
		}
		return keys;
	}
	int size_()const
	{
		return size;
	}
};
/*int main() {
	MyChainingHashMap<int, std::shared_ptr<int> > map;
	map.put(1, std::make_shared<int>(1));
	map.put(2, std::make_shared<int>(2));
	map.put(3, std::make_shared<int>(3));
	std::cout << *map.get(1) << std::endl; // 1
	std::cout << *map.get(2) << std::endl; // 2

	map.put(1, std::make_shared<int>(100));
	std::cout << *map.get(1) << std::endl; // 100

	map.remove(2);
	std::cout << (map.get(2) == nullptr ? "null" : std::to_string(*map.get(2))) << std::endl; // null

	for (const auto key : map.keys()) {
		std::cout << key << " ";
	}
	// [1, 3]（顺序可能不同）
	std::cout << std::endl;

	map.remove(1);
	map.remove(2);
	map.remove(3);
	std::cout << (map.get(1) == nullptr ? "null" : std::to_string(*map.get(1))) << std::endl; // null

	return 0;
}*/