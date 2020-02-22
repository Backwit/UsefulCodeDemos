#include <algorithm>
#include <iostream>
#include <fstream>
#include <string>

#include"autotest.h"

using namespace std;

#define TESTCASEPATH "./testcase.config"

bool ReadTestCase(vector<vector<int> >& testcase) {
	std::ifstream ifs(TESTCASEPATH, ios::in);
	if (!ifs) {
		std::cout<<"testcaseConfig don't exit\n";
		return false;
	}
	
	char buf[1024];
	while(!ifs.eof()) {
		ifs.getline(buf, 1024);
		//std::cout<<"readfile: "<<buf<<std::endl;
		string tmp(buf);
		
		int k = 0;
		while (k < static_cast<int>(tmp.size()) && tmp[k] != ']') {
			if(tmp[k] == ' ') { 
				tmp.erase(k, 1);
			}else{
				k++;
			}
		}
		//std::cout<<"remove space: "<<tmp<<std::endl;

		if(static_cast<int>(tmp.size()) <= 0 || tmp[0] != '[') {
			continue;
		}

		vector<int> tmpcase;
		bool vaild = true;
		int i = 1;
		//std::cout<<"tmp.size = "<<tmp.size()<<std::endl;
		while(i < static_cast<int>(tmp.size())) {
			int j = i;
			while(j < static_cast<int>(tmp.size()) && tmp[j] != ']') {
				if (tmp[j] >= '0' && tmp[j] <= '9') {
					j++;
					continue;
				} else if(tmp[j] == ',') {
					break;
				} else {
					std::cout<<"invaild :"<<tmp[j]<<"xxxxx"<<" j="<<j<<std::endl;
					vaild = false;
					break;
				}
			}
			if(!vaild) {
				break;
			}else{
				string tmpstr = tmp.substr(i, j-i);
				//std::cout<<"tmpstr = "<<tmpstr<<std::endl;
				tmpcase.push_back(std::stoi(tmpstr));
			}
			if (tmp[j] == ']') {
				break;
			} 
			i = j + 1;
		}
		if(vaild) {
			//std::cout<<"add one case\n";
			testcase.push_back(tmpcase);
		}

	}	

	std::cout<<"testcase size : "<<testcase.size()<<std::endl;
/*	if (!testcase.empty()) {
		for(auto &a : testcase) {
			std::cout<<"case: ";
			for(auto &b : a) {
				std::cout<<b<<",";
			}
			std::cout<<"\n";
		}
	}
*/
	return true;
}


void printVector(const vector<int>& nums) {
	std::cout<<"[ ";
	for(auto &n : nums){
		std::cout<<n<<" ";
	}
	std::cout<<"]"<<std::endl;
}


bool VerifySort(std::function<void(vector<int>&)> testSort, vector<int> onecase/* = vector<int>()*/) {
	vector<vector<int> > testcase;
	if(onecase.size() > 0) {
		testcase.push_back(onecase);
	} else {
		if(!ReadTestCase(testcase) && testcase.size() <= 0)	{
			std::cout<<"read testcase from config file is failed, verify fail\n";
			return false;
		}
	}

	int failNums = 0;
	for(int i = 0; i < static_cast<int>(testcase.size()); i++) {
		vector<int> verifyRes(testcase[i]);
		vector<int> rightRes(testcase[i]);
		testSort(verifyRes);
		std::sort(rightRes.begin(), rightRes.end());

		std::cout<<"## Test Case " << i <<" : ";
		printVector(testcase[i]);
		std::cout<<"  My result  : ";
		printVector(verifyRes);
		std::cout<<"  Right Sort : ";
		printVector(rightRes);
		
		if(verifyRes != rightRes) {
			std::cout<<"!!!! Test Result: fail\n";
			failNums++;
		}
	}
	std::cout<<"## Test Nums: "<<testcase.size()<<", fail: "<<failNums<<std::endl;
	return (failNums > 0) ? false : true;
}

