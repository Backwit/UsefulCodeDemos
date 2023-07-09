#include <algorithm>
#include <cmath>
#include <iostream>
#include <vector>

#include "autotest.h"
#include "generic_sort.h"
#include "heap.h"


using namespace std;

/*********************************************************************/
// 1.冒泡排序(Bubble sort)
//  思想：相邻的数依次比较，比后面的大 就交换。
//    1. 外层循环: 0 -> n-2， n-1次循环，每次把最大的数换到最后面
//    2. 内层循环（找到剩余数组中最大的数）：剩余n-i个数，比较n-i-1次。
void BubbleSort(vector<int>& nums)
{
	int len = nums.size();
	for(int i = 0; i < len - 1; ++i) { //n-1次
		int flag = 0; // 用于优化冒泡排序，当一趟排序没有交换时，说明已经排好了。
		for(int j = 0; j < len - i -1; j++) {
			if(nums[j] > nums[j+1]) {
				std::swap(nums[j], nums[j+1]);
				flag = 1;
			}
		}
		if (!flag) {
			return;
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
//  思想：每次找剩下中最小的, 与当前位交换。
//    1.外层循环：从0位到n-2位，总共n-1次选择，最后一位就不用选了
//    2.内层循环：第i位依次与后面的n-i位比较，找到剩下最小的，放到i位上。
void SelectSort(vector<int>& nums)
{
	int len = nums.size();
	for(int i = 0; i < len - 1; i++){
		int minindex = i; 
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
	for(int i = 0; i < len; i++) {
		nums[--count[tmp[i]-minNums]] = tmp[i];
	}
}



/*********************************************************************/
// 9.桶排序
//	假设数据均匀分布，将数据按一定范围均匀分开，放在几个桶中，
//	然后在分别对每个桶排序（可以用其他的排序方法，或者递归的桶排序）。
//	最后再把排好的各个桶的数据 合起来。
//
//	各个数在哪个桶：
//	 deta = (max - min)/bucketNum + 1; //避免桶的大小为0
//	 whichbucket = (num - min)/deta;
//
//	 1 2 3 4 5 6 7 8 9 10; 
//	 bucketNum = 5
//   deta = 2
//   (1-1)/2 = 0; (2-1)/2 = 0
//   1 2 | 3 4 | 5 6 | 7 8 | 9 10
//
//	bucketNum:指定桶的个数，默认为10
//
void BucketSort(vector<int>& nums, int bucketNum/*= 10(default)*/)
{
	int len =  nums.size();
	if (len <= 1) {
		return;
	}

	int maxNum = nums[0];
	int minNum = nums[0];

	for (int i = 1; i < len; i++) {
		maxNum = nums[i] > maxNum ? nums[i] : maxNum;
		minNum = nums[i] < minNum ? nums[i] : minNum;
	}

	int deta = (maxNum - minNum) / bucketNum + 1;
	
	// set Bucket = 10
	vector<vector<int> > bucket(bucketNum, vector<int>());
	for (int i = 0; i < len; i++) {
		int index = (nums[i] - minNum) / deta;
		bucket[index].push_back(nums[i]);
	}

	vector<int> tmpres;
	for (auto &v : bucket) {
		// 选一种方式对每个桶排序，然后在填回nums
		// 这里直接用sort排了算了
		if (!v.empty()) {
			std::sort(v.begin(), v.end());
		}
		tmpres.insert(tmpres.end(), v.begin(), v.end());
	}
	
	nums = tmpres;
}



/*********************************************************************/
// 10.基数排序
//   比较适合数组中的各数的位数差不多的情况
//

// pow函数可以用来求次方，可以快速求出各个位上的数，所以不需要这个函数了
// /*
//  * n:表示分割为多少位
//  */
// vector<vector<int> > SplitInt(vector<int> nums, int n)
// {
// 	vector<vector<int> > res;
// 	for (unsigned i = 0; i < nums.size(); i++) {
// 		vector<int> tmp(n, 0);
// 		for (int j = n-1; j >= 0; j--) {
// 			tmp[j] = nums[i] % 10;
// 			nums[i] /= 10;
// 		}
// 		res.push_back(tmp);
// 	}
// 	return res;
// }

void RadixSort(vector<int>& nums)
{
	int len =  nums.size();
	if (len <= 1) {
		return;
	}

	int maxNum = nums[0];
	int minNum = nums[0];

	for (int i = 1; i < len; i++) {
		maxNum = nums[i] > maxNum ? nums[i] : maxNum;
		minNum = nums[i] < minNum ? nums[i] : minNum;
	}

	// negative number (将负数变为正数)
	if (minNum < 0) {
		for_each(nums.begin(), nums.end(), [&](int x){return x-minNum;});
		maxNum -= minNum; 
	}

	int n = 0;
	int tmp = maxNum;
	while (tmp) {
		tmp /= 10;
		n++;
	}

	if (n == 0) {
		return;
	}
	
	// 按各个位排序	
	for (int i = 1; i <= n; i++) {
		//vector<vector<int> > spnum = SplitInt(nums, n);
		vector<vector<int> > tmpVec(10, vector<int>());
		for (int j = 0; j < len; j++) {
			//tmpVec[spnum[j][i]].push_back(nums[j]);
			int count = nums[j]%(static_cast<int>(pow(10, i)))/(static_cast<int>(pow(10, i-1)));
			tmpVec[count].push_back(nums[j]);
		}
		int index = 0;
		for(int k = 0; k < 10; k++) {
			if(!tmpVec[k].empty()) {
				for(auto & a : tmpVec[k]) {
					nums[index++] = a;
				}
			}
		}
	}
	
	if (minNum < 0) {
		for_each(nums.begin(), nums.end(), [&](int x){return x+minNum;});
	}
}


