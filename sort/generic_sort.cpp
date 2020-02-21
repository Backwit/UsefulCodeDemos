#include<iostream>
#include<vector>
#include<algorithm>
#include<string>

#include"autotest.h"
using namespace std;

// 1.冒泡排序(Bubble sort)
//   思想：每次拿出找出一个最大的，放到数组后面
//     1. 外层循环（查找次数）：n个数，找n-1次
//     2. 内层循环（找到剩余数组中最大的数）：剩余n-i个数，比较n-i-1次。
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

// 2.插入排序
//   思想：从第二个开始逐个与前面排好的比较，要是小就往前移，要是比前面大，就是跳出循环，继续排下一个树。
//     1. 外层循环（插入次数）；从第2个开始，逐个向前插入，所以是 2->n, n-1次循环
//     2. 内层循环（向前插入的比较次数）：第i个数，向前找位置，就是 i -> 0,最多 i-1次
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

// 3.选择排序
//  思想：每次找剩下中最小的。
//		1.外层循环：从0位到n-2位，总共n-1次选择，最后一位就不用选了
//		2.内层循环：第i位依次与后面的n-i位比较，找到剩下最小的，放到i位上。
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

// 4.归并排序
//	思想：
//		1.分成两块 左 右
//		2.左边 递归排好， 右边 递归排好
//		3.整合
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
// 5.快速排序
void QuickSort(vector<int>& nums)
{

}


// 6.堆排序
// 7.桶排序

// 8.希尔排序
//
//



int main()
{
	std::cout<<"*****************************************\n";
	string res = VerifySort(BubbleSort) ? "pass" : "fail";
	std::cout<<"verify BubbleSort: "<<res<<std::endl;

	std::cout<<"*****************************************\n";
	res = VerifySort(InsertSort) ? "pass" : "fail";
	std::cout<<"verify InsertSort: "<<res<<std::endl;

	std::cout<<"*****************************************\n";
	res = VerifySort(SelectSort) ? "pass" : "fail";
	std::cout<<"verify SelectSort: "<<res<<std::endl;

	std::cout<<"*****************************************\n";
	res = VerifySort(MergeSort) ? "pass" : "fail";
	std::cout<<"verify MergeSort: "<<res<<std::endl;

	return 0;
}
