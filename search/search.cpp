#include <iostream>
#include <string>
#include <vector>

using namespace std;


/*
 * 1.顺序查找
 *	return: -1 : find none, >=0: index of find.
 */
int SequenceSearch(vector<int> nums, int value)
{
	for (unsigned i = 0; i < nums.size(); i++) {
		if (nums[i] == value) {
			return i;
		}
	}
	return -1;
}

/*
 * 2.二分查找
 *	需要待排序列是有序的。
 *	return: -1(find none); other index of the find.
 */
int BinarySearch(vector<int> nums, int value)
{
	int i = 0;
	int j = nums.size() - 1;
	
	while (i <= j) {
		int mid  = i + (j - i)/2;
		if (nums[mid] == value) {
			return mid;
		} else if (value < nums[mid]) {
			j = mid - 1; //存在j = -1的情况，当mid=0时，但此时 j<i了，不满足条件，就return了。
		} else if (value > nums[mid]) {
			i = mid + 1;
		}
	}
	return -1;
}

/*
 * 3.二分查找（左边界）
 *	找第一个满足的
 *  
 */
int BinarySearchFirst(vector<int> nums, int value)
{
	int i = 0;
	int j = nums.size() - 1;
	int res = -1;
	while (i <= j) {
		int mid  = i + (j - i)/2;
		if (nums[mid] == value) {
			res = mid;
			j = mid -1;
		} else if (value < nums[mid]) {
			j = mid - 1;
		} else if (value > nums[mid]) {
			i = mid + 1;
		}
	}
	return res;
}

/*
 * 4.二分查找(右边界）
 *	找最后一个满足的
 *  
 */
int BinarySearchLast(vector<int> nums, int value)
{
	int i = 0;
	int j = nums.size() - 1;
	int res = -1;
	while (i <= j) {
		int mid  = i + (j - i)/2;
		if (nums[mid] == value) {
			res = mid;
			i = mid + 1;
		} else if (value < nums[mid]) {
			j = mid - 1;
		} else if (value > nums[mid]) {
			i = mid + 1;
		}
	}
	return res;
}



int main()
{
	vector<vector<int> > test{{},{1},{2,3},{4,5,6},{7,8,9,10},{11,12,13,14,15,16,17}};
	vector<int> res1;
	vector<int> res2;
	for(int i = 0; i < 20; i++) {
		for(unsigned j = 0; j < test.size(); j++) {
			int index = BinarySearch(test[j], i);
			if(index <= 0 || index >= test[j].size()) {
				res1.push_back(-1);
			} else if(test[j][index] == i) {
				res1.push_back(0);
			}
			//cout<<"index = "<<index;	
			int index2 = SequenceSearch(test[j], i);
			if(index2 <= 0 || index2 >= test[j].size()) {
				res2.push_back(-1);
			} else if(test[j][index2] == i) {
				res2.push_back(0);
			}
			//cout<<"; index2 = "<<index2<<endl;
		}
	}

	if(res1 == res2){
		std::cout<<"BinarySearch test pass\n";
	}else{
		std::cout<<"BinarySearch test fail\n";
	}

	vector<vector<int> > test2{{},{1,1,1},{2,3,3},{4,5,5,5,5,6},{7,7,7,7,8,9,10},{11,12,13,14,15,16,17,17,17,17}};
	vector<int> value{1,1,3,5,7,17};
	vector<int> res3{-1,0,1,1,0,6};
	for(unsigned i = 0; i < test2.size(); i++){
		if(res3[i] != BinarySearchFirst(test2[i], value[i])){
			std::cout<<"BinarySearchFirst test fail\n";
			return 0;
		}
	}
	std::cout<<"BinarySearchFirst test pass\n";

	vector<int> res4{-1,2,2,4,3,9};
	for(unsigned i = 0; i < test2.size(); i++){
		if(res4[i] != BinarySearchLast(test2[i], value[i])){
			std::cout<<"BinarySearchLast test fail\n";
			return 0;
		}
	}
	std::cout<<"BinarySearchLast test pass\n";


	return 0;
}
