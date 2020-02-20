#ifndef __AUTOTEST_H__
#define __AUTOTEST_H__

#include<vector>
#include<functional>

bool VerifySort(std::function<void(std::vector<int>&)> testSort, 
				std::vector<int> onecase = std::vector<int>());

void printVector(const std::vector<int>& nums); 

#endif
