//#pragma once
#ifndef _HEAP_H
#define _HEAP_H

//STL���㷨ʵ�֣��󶥶ѣ�  
//��������vector��ͷ�ļ���Heap��vector���洢Ԫ��  
#include <vector>  
using std::vector;
using std::less;

//���ඨ��,Ԫ��ElemType,Ĭ�ϱȽϹ���less
template <typename ElemType, typename Storage = vector<ElemType>, typename Compare = less<ElemType> >
class MyHeap {
private:
	Storage heapDataVec;//���Ԫ�ص�����  
	int numCounts;//����Ԫ�ظ���  
	Compare comp;//�ȽϹ���
	bool isHeap;//heapDataVec�е������Ƿ�Ϊ��
	const int StartIndex = 0;//�����ж�Ԫ����ʼ����  
public:
	MyHeap();
	MyHeap(const Storage &data);
	inline Storage getVec() { return heapDataVec; }
	inline int getNumCounts() { return numCounts; }
	void printHeap();//�����Ԫ��  
	void makeHeap();//����  
	Storage sortHeap();//�������㷨  
	void pushHeap(ElemType elem);//����в���Ԫ��  
	inline ElemType getHeap() { return heapDataVec.front(); }
	void popHeap();//�Ӷ���ȡ���Ѷ���Ԫ��  
private:
	void siftDown(int childTree);//��������  
	void siftUp(int holeIndex);//���ݲ���  
};

#include"Heap.inl"

#endif