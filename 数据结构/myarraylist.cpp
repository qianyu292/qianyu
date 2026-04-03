//动态数组
#include<iostream>
#include<stdexcept>
#include<vector>
template<typename E>
class myarraylist
{
private:
	E* data;//真正记录数据的底层数组

	int size;//当前元素个数

	int cap;//最大容量

	static const int INIT_CAP = 1;
public:
	myarraylist()//初始化
	{
		this->data = new E[INIT_CAP];
		this->size = 0;
		this->cap = INIT_CAP;
	}
	myarraylist(int initcapacity)//分配内存
	{
		this->data = new E[initcapacity];
		this->size = 0;
		this->cap = initcapacity;
	}
	//增
	void addlast(E e)
	{
		if (size == cap)
		{
			resize(cap * 2);
		}
		data[size] = e;
		size++;
	}
	void add(int index, E e)//指定位置插入
	{
		checkPositionIndex(index);
		if (size == cap)
		{
			resize(cap * 2);
		}
		for (int i = size - 1; i >=index; i--)
		{
			data[i + 1] = data[i];
		}
		data[index] = e;

		size++;
	}
	void addfirst(E e)
	{
		add(0, e);
	}
	//删
	E removelast()
	{
		if (size == 0) {
			throw std::out_of_range("NoSuchElementException");
		}

		if (size == cap / 4)
		{
			resize(cap / 2);
		}

		E deletedval = data[size - 1];

	// 删除最后一个元素
	// 必须给最后一个元素置为 null，否则会内存泄漏
		data[size - 1] = E();
		size--;

		return deletedval;
	}
	E remove(int index)
	{
		checkPositionIndex(index);

		if (size == cap / 4)
		{
			resize(cap / 2);
		}

		E deletedval = data[size - 1];

		for (int i = index + 1; i < size; i++)
		{
			data[i - 1] = data[i];
		}
		data[size - 1] = E();
		size--;
		
		return deletedval;
	}
	E removefirst()
	{
		return remove(0);
	}
	//查
	E get(int index)
	{
		checkPositionIndex(index);
		
		return data[index];
	}
	//改
	E set(int index, E element)
	{
		checkPositionIndex(index);

		E oldval = data[index];
		data[index] = element;
		return oldval;
	}
	//工具方法
	int getsize()
	{
		return size;
	}
	bool isEmpty() 
	{
		return size == 0;
	}
	void resize(int newcap)//重新分配内存
	{
		E* temp = new E[newcap];
		for (int i = 0; i < size; ++i)
		{
			temp[i] = data[i];
		}
		delete[]data;

		data = temp;
		cap = newcap;
	}
	bool isElementIndex(int index)
	{
		return index >= 0 && index < size;
	}
	bool isPositionIndex(int index) 
	{
		return index >= 0 && index <= size;
	}
	void checkElementIndex(int index)
	{
		if (!isElementIndex(index)) 
		{
			throw std::out_of_range("Index out of bounds");
		}
	}
	void checkPositionIndex(int index) 
	{
		if (!isPositionIndex(index)) 
		{
			throw std::out_of_range("Index out of bounds");
		}
	}
	void display()
	{
	std::cout << "size:" << size << "cap" << cap << std::endl;
	for (int i = 0; i < size; ++i)
	{
		std::cout << data[i] << " ";
	}
	std::cout << std::endl;
	}
	~myarraylist()
	{
		delete[]data;
	}
};
/*int main()
{
	myarraylist<int>arr(3);

	// 添加 5 个元素
	for (int i = 1; i <= 5; i++) {
		arr.addlast(i);
	}

	arr.remove(3);
	arr.add(1, 9);
	arr.addfirst(100);
	int val = arr.removelast();

	// 100 1 9 2 3
	for (int i = 0; i < arr.getsize(); i++)
	{
		std::cout << arr.get(i) << std::endl;
	}
	return 0;
}*/