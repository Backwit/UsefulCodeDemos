#include <iostream>
#include <string>
#include "autotest.h"
#include "generic_sort.h"
#include<functional>

using std::cout;
using std::endl;
using std::string;

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

	std::cout<<"*****************************************\n";
	res = VerifySort(QuickSort) ? "pass" : "fail";
	std::cout<<"verify QuickSort: "<<res<<std::endl;

	std::cout<<"*****************************************\n";
	res = VerifySort(ShellSort) ? "pass" : "fail";
	std::cout<<"verify ShellSort: "<<res<<std::endl;

	std::cout<<"*****************************************\n";
	res = VerifySort(HeapSort) ? "pass" : "fail";
	std::cout<<"verify HeapSort: "<<res<<std::endl;

	std::cout<<"*****************************************\n";
	res = VerifySort(HeapSort2) ? "pass" : "fail";
	std::cout<<"verify HeapSort2: "<<res<<std::endl;

	std::cout<<"*****************************************\n";
	res = VerifySort(CountingSort) ? "pass" : "fail";
	std::cout<<"verify CountingSort: "<<res<<std::endl;

	std::cout<<"*****************************************\n";
	res = VerifySort(RadixSort) ? "pass" : "fail";
	std::cout<<"verify RadixSort: "<<res<<std::endl;
	
	std::cout<<"*****************************************\n";
	int bucketnums = 10;
	res = VerifySort(std::bind(BucketSort, std::placeholders::_1, bucketnums)) ? "pass" : "fail";
	std::cout<<"verify BucketSort: "<<res<<std::endl;
	return 0;

}
