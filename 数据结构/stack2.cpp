#include<vector>
template<typename E>
class Myvectorstack
{
private:
	std::vector<E>stack;
public:
	void push(const E &e)
	{
		stack.push_back(e);
	}
	E pop()
	{
		E back = stack.back();
		stack.pop_back();
		return back;
	}
	E peek()const
	{
		return stack.back();
	}
	int size()const
	{
		return stack.size();
	}
};
