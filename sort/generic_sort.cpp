#include <iostream>
#include <vector>
#include <algorithm>

#include "generic_sort.h"
#include "autotest.h"
#include "heap.h"


using namespace std;

/*********************************************************************/
// 1.冒泡排序(Bubble sort)
//  思想：每次拿出找出一个最大的，放到数组后面
//    1. 外层循环（查找次数）：n个数，找n-1次
//    2. 内层循环（找到剩余数组中最大的数）：剩余n-i个数，比较n-i-1次。
void BubbleSort(vector<int>& nums)
{
	int len = nums.size();
	for(int i = 1; i < len; ++i) { //n-1次
		for(int j = 0; j < len - i; j++) {
			if(nums[j] > nums[j+1]) {
				std::swap(nums[j], nums[j+1]);
			}
		}
	}
}

/*********************************************************************/
// 2.插入排序
//  思想：从第二个开始逐个与前面排好的比较，要是小就往前移，要是比前面大，就是跳出循环，继续排下一个树。
//    1. 外层循环（插入次数）；从第2个开始，逐个向前插入，所以是 2->n, n-1次循环
//    2. 内层循环（向前插入的比较次数）：第i个数，向前找位置，就是 i -> 0,最多 i-1次
void InsertSort(vector<int>& nums)
{
	int len = nums.size();
	for(int i = 1; i < len; ++i){
		for(int j = i; j > 0; --j){
			if (nums[j] < nums[j-1]) {
				std::swap(nums[j], nums[j-1]);
			} else {
				break;
			}
		}
	}
}

/*********************************************************************/
// 3.希尔排序
//	思想：带间隔的插入排序。
//	1.外层: 按间隔来的，n/k、n/(k*k) ... 1
//	2.内层：插入排序
void ShellSort(vector<int>& nums)
{
	int len = nums.size();
	for(int k = len>>1; k >= 1; k = k>>1) {
		std::cout<<"k= "<<k<<std::endl;
		for(int i = k; i < len; i += k) {
			for(int j = i; j > 0; j -= k){
				if(nums[j] < nums[j-k]) {
					std::swap(nums[j-k], nums[j]);
				} else {
					break;
				}
			}
		}
	}
}

//更具有希尔排序特点的写法：
// dt表示一个增量的数组（n/k -> 1）
// void ShellSort(vector<int>& nums, vector<int>& dt){
//     for(auto k : dt){
//			ShellInsertSort(nums, k);
//     } 
//
// }
//
// void ShellInsertSort(vector<int>& nums, int k){
//     for(int i = k; i<n; i+=k)
//		   for(int j=i; j>0; j-=k)
// }
//

/*********************************************************************/

// 4.选择排序
//  思想：每次找剩下中最小的。
//    1.外层循环：从0位到n-2位，总共n-1次选择，最后一位就不用选了
//    2.内层循环：第i位依次与后面的n-i位比较，找到剩下最小的，放到i位上。
void SelectSort(vector<int>& nums)
{
	int len = nums.size();
	for(int i = 0; i < len - 1; i++){
		int minindex = i; //减少交换次数
		for(int j = i+1; j < len; j++){
			if(nums[minindex] > nums[j]) {
				minindex = j;
			}
		}
		if(minindex != i){
			std::swap(nums[i], nums[minindex]);
		}
	}
}

/*********************************************************************/
// 5.归并排序
//  思想：
//    1.分成两块 左 右
//    2.左边 递归排好， 右边 递归排好
//    3.整合
void Merge(vector<int>& res, vector<int>& left, vector<int>& right)
{
	int ls = left.size();
	int rs = right.size();
	int sum = res.size();
	
	int i = 0;
	int j = 0;
	int k = 0;
	while(i < sum) {
		if (j == ls && k < rs){
			res[i++] = right[k++];
		} else if(k == rs && j < ls){
			res[i++] = left[j++];
		} else { // j<ls &&k<rs
			if(left[j] <= right[k]){
				res[i++] = left[j++];
			} else {
				res[i++] = right[k++];
			}
		}
	}
}

void MergeSort(vector<int>& nums)
{
	int len = nums.size();
	if(len <= 1){
		return;
	}
	int mid = (len-1)/2;
	vector<int> left(nums.begin(), nums.begin() + mid + 1);
	vector<int> right(nums.begin() + mid + 1, nums.end());

	MergeSort(left);
	MergeSort(right);
	Merge(nums, left, right);
} 

/*********************************************************************/
// 6.快速排序
//  思想：任选其中一个数，把小于它的，放在左边，大于它的，放在它右边，然后递归。。。
//
//
void QuickSort(vector<int>& nums)
{
	int len = nums.size();
	if(len <= 1) {
		return;
	}
	int i = 1;
	int j = len - 1;

	int pivot = 0;

	while (i != j) {
		while(j > i && nums[j] >= nums[pivot]){
			j--;
		}
		while(i < j && nums[i] <= nums[pivot]){
			i++;
		}
		if (i < j) {
			std::swap(nums[i], nums[j]);
		}
	}
	if(nums[i] > nums[pivot]) {
		i--;
	}
	std::swap(nums[pivot], nums[i]);
	pivot = i;

	if(pivot != 0){
		vector<int> left(nums.begin(), nums.begin() + i);
		QuickSort(left);
		for(int i = 0; i < static_cast<int>(left.size()); i++) {
			nums[i] = left[i];
		}
	}
	if(pivot != len -1 ) {
		vector<int> right(nums.begin()+pivot+1, nums.end());
		QuickSort(right);
		for(vector<int>::size_type i = 0; i < right.size(); i++) {
			nums[pivot+1+i] = right[i];
		}
	}
}


/*********************************************************************/
// 7.堆排序
//
/*利用stl标准库实现堆排序*/
void HeapSort(vector<int>& nums)
{
// 需要先用make_heap把vector变成一个堆，然后再用sort_heap进行排序。
	std::make_heap(nums.begin(), nums.end(), [](int& x, int& y){return x<y;});
	std::sort_heap(nums.begin(), nums.end(), [](int& x, int& y){return x<y;});
}

/*自己实现堆*/
void HeapSort2(vector<int>& nums)
{
	BuildHeap(nums, static_cast<int>(nums.size()));
	SortHeap(nums);
	
	// 构建大顶堆，降序排列
	// BuildHeap(nums, static_cast<int>(nums.size()), 1);
	// SortHeap(nums, 1);
}


/*非比较排序*/
/*********************************************************************/
// 8.计数排序
// 适用于目标数据比较集中在一个范围的情况。
//   1）find min 和 max, 创建一个max-min+1的数组，表示这个范围上各个数出现的次数
//   2）遍历数组，填充count数组。
//   3）按count数组，重新填充目标数组，实现排序。
void CountingSort(vector<int>& nums)
{
	int len = nums.size();
	if(len <= 1){
		return;
	}
	// 1. find max and min nums
	int maxNums = nums[0];
	int minNums = nums[0];

	for(int i = 1; i < len; i++) {
		maxNums = (nums[i] > maxNums) ? nums[i] : maxNums;
		minNums = nums[i] < minNums ? nums[i] : minNums;
	} 

	if(maxNums == minNums){
		return;
	}

	// 2. count 数组 记录每个数出现的次数
	vector<int> count(maxNums - minNums + 1, 0);
	for(int i = 0; i < len; i++){
		count[nums[i] - minNums]++;
	}

	// 3. 计算每个数的结束位置，方便下面进一步把数放到对应的位置
	for(unsigned int i = 1; i < count.size(); i++) {
		count[i] += count[i-1];
	}

	vector<int> tmp(nums);	
	for(unsigned int i = 0; i < len; i++) {
		nums[--count[tmp[i]-minNums]] = tmp[i];
	}
}



/*********************************************************************/
// 9.桶排序



/*********************************************************************/
// 10.基数排序






