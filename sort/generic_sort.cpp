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
// 4.归并排序
// 5.快速排序
// 6.堆排序
// 7.桶排序




int main()
{
	std::cout<<"*****************************************\n";
	string res = VerifySort(BubbleSort) ? "pass" : "fail";
	std::cout<<"verify BubbleSort: "<<res<<std::endl;

	std::cout<<"*****************************************\n";
	res = VerifySort(InsertSort) ? "pass" : "fail";
	std::cout<<"verify InsertSort: "<<res<<std::endl;

	return 0;
}
