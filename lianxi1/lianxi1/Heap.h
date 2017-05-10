//#pragma once
#ifndef _HEAP_H
#define _HEAP_H

//STL堆算法实现（大顶堆）  
//包含容器vector的头文件：Heap用vector来存储元素  
#include <vector>  
using std::vector;
using std::less;

//堆类定义,元素ElemType,默认比较规则less
template <typename ElemType, typename Storage = vector<ElemType>, typename Compare = less<ElemType> >
class MyHeap {
private:
	Storage heapDataVec;//存放元素的容器  
	int numCounts;//堆中元素个数  
	Compare comp;//比较规则
	bool isHeap;//heapDataVec中的数据是否为堆
	const int StartIndex = 0;//容器中堆元素起始索引  
public:
	MyHeap();
	MyHeap(const Storage &data);
	inline Storage getVec() { return heapDataVec; }
	inline int getNumCounts() { return numCounts; }
	void printHeap();//输出堆元素  
	void makeHeap();//建堆  
	Storage sortHeap();//堆排序算法  
	void pushHeap(ElemType elem);//向堆中插入元素  
	inline ElemType getHeap() { return heapDataVec.front(); }
	void popHeap();//从堆中取出堆顶的元素  
private:
	void siftDown(int childTree);//调整子树  
	void siftUp(int holeIndex);//上溯操作  
};

#include"Heap.inl"

#endif