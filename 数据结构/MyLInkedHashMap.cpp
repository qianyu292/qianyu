#include<iostream>
#include<unordered_map>
#include<list>
using namespace std;
template<typename K,typename V>
struct Node
{
	K key;
	V val;
	Node* next;
	Node* prev;
	Node(K key, V val) :key(key),val(val),next(nullptr),prev(nullptr){}
};
template<typename K, typename V>
class MyLinkedHashMap
{
public:
	MyLinkedHashMap()
	{
		head = new Node<K, V>(K(), V());
		tail = new Node<K, V>(K(), V());
		head->next = tail;
		tail->prev = head;
	}
	~MyLinkedHashMap()
	{
		Node<K, V>* current = head->next;
		while (current != tail) {
			Node<K, V>* next = current->next;
			delete current;
			current = next;
		}
		// 释放头尾节点
		delete head;
		delete tail;
	}
	MyLinkedHashMap(const MyLinkedHashMap&) = delete;
	MyLinkedHashMap& operator=(const MyLinkedHashMap&) = delete;

	V get(K key)
	{
		if (map.find(key) == map.end())
		{
			return V();
		}
		return map[key]->val;
	}
	void put(V val, K key)
	{
		if(map.find(key)==map.end())
		{	Node<K, V>* node = new Node<K, V>(key, val);
		addLastNode(node);
		map[key] = node;
		return;
	    }
		return map[key]->val;
	}
	void remove(K key) 
	{
		// 若 key 本不存在，直接返回
		if (map.find(key) == map.end()) 
		{
			return;
		}
		// 若 key 存在，则需要同时在哈希表和链表中删除
		Node<K, V>* node = map[key];
		map.erase(key);
		removeNode(node);
		// 释放节点内存
		delete node;
	}

	bool containsKey(K key) 
	{
		return map.find(key) != map.end();
	}

	vector<K> keys() {
		vector<K> keyList;
		for (Node<K, V>* p = head->next; p != tail; p = p->next) {
			keyList.push_back(p->key);
		}
		return keyList;
	}

	// 获取元素数量
	size_t size() {
		return map.size();
	}

	// 判断是否为空
	bool empty() {
		return map.empty();
	}
private:
	Node<K, V>* head;
	Node<K, V>* tail;
	unordered_map<K, Node<K, V>*>map;
	void addlastNode(Node<K,V>* x)
	{
		Node<K, V>* temp = tail->prev;
		x->next = tail;
		x->prev = temp;

		temp->next = x;
		tail->prev = x;
	}
	void removeNode(Node<K,V>*x)
	{
		Node<K, V>* prev = x->prev;
		Node<K, V>* next = x->next;

		prev->next = next;
		next->prev = prev;

		x->next = x->prev = nullptr;
	}
};
/*int main() {
	MyLinkedHashMap<string, int> map;
	map.put("a", 1);
	map.put("b", 2);
	map.put("c", 3);
	map.put("d", 4);
	map.put("e", 5);

	// output: a b c d e
	for (const auto& key : map.keys()) {
		cout << key << " ";
	}
	cout << endl;

	map.remove("c");
	cout << map.containsKey("c") << endl;

	// output: a b d e
	for (const auto& key : map.keys()) {
		cout << key << " ";
	}
	cout << endl;

	return 0;
}*/
