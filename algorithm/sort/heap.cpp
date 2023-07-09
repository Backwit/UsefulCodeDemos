#include "heap.h"

#include <iostream>
#include <vector>
#include <algorithm>

using std::vector;

/*
 * Max Heap adjustify.
 */
void MaxHeapify(vector<int>& nums, int size, int parent)
{
	if(parent >= size) {
		return;
	}
	
	int max = parent;
	int lc = parent*2 + 1;
	int rc = parent*2 + 2;
	if (lc < size && nums[max] < nums[lc]) {
		max = lc;
	}
	if (rc < size && nums[max] < nums[rc]) {
		max = rc;
	}
	if (max != parent) {
		std::swap(nums[max], nums[parent]);
		MaxHeapify(nums, size, max);
	}
}

/*
 * Min Heap adjustify
 */
void MinHeapify(vector<int>& nums, int size, int parent)
{
	if(parent >= size) {
		return;
	}
	
	int min = parent;
	int lc = parent*2 + 1;
	int rc = parent*2 + 2;
	if (lc < size && nums[min] > nums[lc]) {
		min = lc;
	}
	if (rc < size && nums[min] > nums[rc]) {
		min = rc;
	}
	if (min != parent) {
		std::swap(nums[min], nums[parent]);
		MinHeapify(nums, size, min);
	}
}

/*
 * build heap:
 *  nums: data
 *  size：heap size.
 *  flag: 0: min heap(defeat)  1: max heap.   (这种方式不怎么好，应该像stl一样，设置一个comp)
 */
void BuildHeap(vector<int>& nums, int size, int flag)
{
	for(int i = (size-1)/2; i >= 0; i--) {
		if (flag == 0) {
			MinHeapify(nums, size, i);
		} else {
			MaxHeapify(nums, size, i);
		}
	}
}

/*
 * sort heap.
 * nums: is a heap
 */
void SortHeap(vector<int>& nums, int flag)
{
	int len = nums.size();
	for (int i = 1; i < len; i++) {
		if(flag == 0) {
			MinHeapify(nums, len + 1 - i, 0);
		} else {
			MaxHeapify(nums, len + 1 - i, 0);
		}
		std::swap(nums[0], nums[len-i]);
	}
	std::reverse(nums.begin(), nums.end());
}




