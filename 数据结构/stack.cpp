#include<list>
#include<iostream>
template<typename E>
class mylinkedstack
{
private:
	std::list<E>list;
public:
	void push(const E& e)
	{
		list.push_back(e);
	}
	E pop()
	{
		E back = list.back();
		list.pop_back();
		return back;
	}
	E peek()
	{
		return list.back();
	}
	int size()const
	{
		return list.size();
	}
};
/*int main()
{
	mylinkedstack<int> stack;
	stack.push(1);
	stack.push(2);
	stack.push(3);
	stack.push(4);
	while (stack.size() > 0) {
		std::cout << stack.pop() << std::endl;
	}
	return 0;
}*/