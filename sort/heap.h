#ifndef __HEAP_H__
#define __HEAP_H__

#include <vector>
#include <iostream>

using std::vector;

void BuildHeap(vector<int>& nums, int size, int flag = 0);

void SortHeap(vector<int>& nums, int flag = 0);

#endif
