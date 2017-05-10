#pragma once
#include"Heap.h"

template <typename ElemType, typename Storage, typename Compare>
MyHeap<ElemType, Storage, Compare>::MyHeap() : numCounts(0), isHeap(false) {
	return;
}//MyHeap

template <typename ElemType, typename Storage, typename Compare>
MyHeap<ElemType, Storage, Compare>::MyHeap(const Storage &data) {
	//拷贝元素数据到vector中
	heapDataVec = data;
	numCounts = data.size();
	makeHeap();
	return;
}//MyHeap

template <typename ElemType, typename Storage, typename Compare>
void MyHeap<ElemType, Storage, Compare>::printHeap() {
	cout << "Heap : ";
	for (int i(0); i < numCounts; ++i) {
		cout << heapDataVec[i] << " ";
	}//for i
	cout << endl;
	return;
}//printHeap

template <typename ElemType, typename Storage, typename Compare>
void MyHeap<ElemType, Storage, Compare>::makeHeap() {
	//建堆的过程就是一个不断调整堆的过程，循环调用函数adjustHeap依次调整子树
	if (isHeap == true)return;
	isHeap = true;
	if (numCounts < 2)return;
	for (int i((numCounts - 1 - 1) >> 1); i >= StartIndex; --i) {
		siftDown(i);
	}//for parent
	return;
}//makeHeap

template <typename ElemType, typename Storage, typename Compare>
Storage MyHeap<ElemType, Storage, Compare>::sortHeap() {
	//堆排序思路//每执行一次popHeap操作，堆顶的元素被放置在尾端，然后针对前面的一次再执行popHeap操作
	//依次下去，最后即得到排序结果
	if (isHeap == false)makeHeap();
	Storage retVecElem(numCounts);
	for (int i(numCounts - 1); i >= 0; --i) {
		retVecElem[i] = getHeap();
		popHeap();
	}//for i
	isHeap = false;
	return retVecElem;
}//sortHeap

template <typename ElemType, typename Storage, typename Compare>
void MyHeap<ElemType, Storage, Compare>::pushHeap(ElemType elem) {
	if (isHeap == false)makeHeap();
	//将新元素添加到vector中
	heapDataVec.push_back(elem);
	++numCounts;
	//执行一次上溯操作，调整堆，以使其满足最大堆的性质  
	siftUp(numCounts - 1);
	return;
}//pushHeap

template <typename ElemType, typename Storage, typename Compare>
void MyHeap<ElemType, Storage, Compare>::popHeap() {
	//将堆顶的元素放在容器的最尾部，然后将尾部的原元素作为调整值，重新生成堆
	if (isHeap == false)makeHeap();
	heapDataVec[StartIndex] = heapDataVec[numCounts - 1];
	heapDataVec.pop_back();
	--numCounts;//堆中元素数目减一
	siftDown(StartIndex);
	return;
}//popHeap


 //调整以childTree为根的子树为堆
template <typename ElemType, typename Storage, typename Compare>
void MyHeap<ElemType, Storage, Compare>::siftDown(int siftIndex) {
	//洞节点索引
	if (numCounts == 0)return;
	int siftValue(heapDataVec[siftIndex]);
	int childIndex = (siftIndex << 1) + 1;
	while (childIndex <= numCounts - 1) {
		if (childIndex + 1 <= numCounts - 1 && comp(heapDataVec[childIndex], heapDataVec[childIndex + 1]))++childIndex;//表示两个子节点中值较大的那个
		if (comp(siftValue, heapDataVec[childIndex]) == false) {
			heapDataVec[siftIndex] = siftValue;
			return;
		}//if
		heapDataVec[siftIndex] = heapDataVec[childIndex];//令较大值为洞值  
		siftIndex = childIndex;//洞节点索引下移  
		childIndex = (childIndex << 1) + 1;//重新计算洞节点右子节点  
	}//while
	heapDataVec[siftIndex] = siftValue;
	return;
}//siftDown

 //上溯操作
template <typename ElemType, typename Storage, typename Compare>
void MyHeap<ElemType, Storage, Compare>::siftUp(int holeIndex) {
	//将新节点与其父节点进行比较，如果键值比其父节点大，就父子交换位置。
	//如此，知道不需要对换或直到根节点为止
	int tmp(heapDataVec[holeIndex]);
	int parentIndex = (holeIndex - 1) >> 1;
	while (holeIndex > StartIndex && comp(heapDataVec[parentIndex], tmp)) {
		heapDataVec[holeIndex] = heapDataVec[parentIndex];
		holeIndex = parentIndex;
		parentIndex = (parentIndex - 1) >> 1;
	}//while
	heapDataVec[holeIndex] = tmp;//将新值放置在正确的位置  
	return;
}//siftUp