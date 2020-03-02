#include <iostream>
#include <string>
#include <vector>

using namespace std;

/*
 * 求模板的next数组
 */
vector<int> NextPos(string str)
{
	int len = str.size();
	vector<int> next;
	if(len == 0){
		return next;
	}
	next.push_back(-1);

	int i = 1;
	int j = 0;
	while(i < len){
		if(next[j] == -1 || str[next[j]] == str[i-1]){
			next.push_back(next[j]+1);
			j = i;
			i++;
		}else{
			j = next[j];
		}
	}

	return next;
}

/*
 * KMP算法：从主串中找到pattern串的位置
 * pat: pattern串
 * str: 主串
 * return: -1 没找到， 其他：pat在主串中的位置
 */
int Kmp(string pat, string str)
{
	int i = 0;
	int j = 0;
	vector<int> next = NextPos(pat);
	while(i < pat.size() && j < str.size()){
		if(pat[i] == str[j]){
			i++;
			j++;
		}else{
			if (i == 0) {
				j++;
			} else {
				i = next[i]; 
			}
		}
	}

	return i == pat.size() ? j - i : -1;
}

/*
 * 暴力brute force匹配算法 
 */
int BruteForce(string pat, string str)
{
	unsigned int i = 0;
	unsigned int j = 0;
	while(i < pat.size() && j < str.size()) {
		if(pat[i] == str[j]){
			i++;
			j++;
		}else{
			j = j - i + 1;//主串从下个位置开始匹配
			i = 0;
		}
	}
	// 跳出循环 
	// 1）i == pat.size(),说明子串全部已匹配
	// 或 i != pat.size(),说明没找到，此时j == str.size()已经到最后了。

	return i == pat.size() ? j - i : -1;
}


void printVector(vector<int>& nums)
{
	for(auto a:nums){
		cout<<a<<" ";
	}
	cout<<endl;
}

int main()
{
	string str("abababd");
	string pat("abd");

	cout<<Kmp(pat, str)<<endl;
	cout<<BruteForce(pat, str)<<endl;	

	string test("abdabaa");
	vector<int> next = NextPos(test);
	printVector(next);

	return 0;
}

