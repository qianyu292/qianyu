#include<iostream>
#include<vector>
using namespace std;
vector<int>temp;
int partition(vector<int>& nums, int lo, int hi);
void merge(vector<int>& nums, int lo, int mid, int hi);
void sort(vector<int>& res, int lo, int hi)
{
	if (lo >= hi)return;

	int p = partition(res, lo, hi);

	sort(res, lo, p - 1);
	sort(res, p + 1, hi);
}
int partition(vector<int>& nums, int lo, int hi)
{
	int pivot = nums[lo];
	int i = lo + 1, j = hi;
	while (i <= j)
	{
		while (i<=hi&&nums[i]<=pivot)
		{
			i++;
		}
		while (j >lo && nums[j] >= pivot)
		{
			j--;
		}
		if(i<=j)
		swap(nums[i], nums[j]);
	}
	swap(nums[lo], nums[j]);
	return j;
}
void sort2(vector<int>& nums, int lo, int hi)
{
	if(lo>=hi)
	{
		return;
	}
	int mid = (lo + hi) / 2;
	sort2(nums, lo, mid);
	sort2(nums, mid + 1, hi);

	merge(nums, lo, mid, hi);
}
void merge(vector<int>& nums, int lo, int mid, int hi)
{
	if (temp.size() < nums.size()) {
		temp.resize(nums.size());
	}
	for (int i = lo; i <= hi; i++) 
	{
		temp[i] = nums[i];
	}
	int i = lo, j = mid+1;
	for (int p = lo; p <= hi; ++p)
	{
		if (i == mid + 1)
		{
			nums[p] = temp[j++];
		}
		else if (j == hi+1)
		{
			nums[p] = temp[i++];
		}
		else if (temp[i] > temp[j])
		{
			nums[p] = temp[j++];
		}
		else
		{
			nums[p] = temp[i++];
		}
	}
}
int main()
{
	return 0;
}