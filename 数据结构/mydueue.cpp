#include<iostream>
#include<list>
template<typename E>
class myqueue
{
private:
	std::list<E>list;
public:
	void push_back(const E &e)
	{
		return list.push_back(e);
	}
	void push_front(const E& e)
	{
		return list.push_front(e);
	}
	E pop_front()
	{
		E front = list.front();
		list.pop_front();
		return front;
	}
	E pop_back()
	{
		E back = list.back();
		list.pop_back();
		return back;
	}
	E peek_front()
	{
		return list.front();
	}
	E peek_back()
	{
		return list.back();
	}
};
