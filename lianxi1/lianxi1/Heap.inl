#pragma once
#include"Heap.h"

template <typename ElemType, typename Storage, typename Compare>
MyHeap<ElemType, Storage, Compare>::MyHeap() : numCounts(0), isHeap(false) {
	return;
}//MyHeap

template <typename ElemType, typename Storage, typename Compare>
MyHeap<ElemType, Storage, Compare>::MyHeap(const Storage &data) {
	//����Ԫ�����ݵ�vector��
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
	//���ѵĹ��̾���һ�����ϵ����ѵĹ��̣�ѭ�����ú���adjustHeap���ε�������
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
	//������˼·//ÿִ��һ��popHeap�������Ѷ���Ԫ�ر�������β�ˣ�Ȼ�����ǰ���һ����ִ��popHeap����
	//������ȥ����󼴵õ�������
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
	//����Ԫ����ӵ�vector��
	heapDataVec.push_back(elem);
	++numCounts;
	//ִ��һ�����ݲ����������ѣ���ʹ���������ѵ�����  
	siftUp(numCounts - 1);
	return;
}//pushHeap

template <typename ElemType, typename Storage, typename Compare>
void MyHeap<ElemType, Storage, Compare>::popHeap() {
	//���Ѷ���Ԫ�ط�����������β����Ȼ��β����ԭԪ����Ϊ����ֵ���������ɶ�
	if (isHeap == false)makeHeap();
	heapDataVec[StartIndex] = heapDataVec[numCounts - 1];
	heapDataVec.pop_back();
	--numCounts;//����Ԫ����Ŀ��һ
	siftDown(StartIndex);
	return;
}//popHeap


 //������childTreeΪ��������Ϊ��
template <typename ElemType, typename Storage, typename Compare>
void MyHeap<ElemType, Storage, Compare>::siftDown(int siftIndex) {
	//���ڵ�����
	if (numCounts == 0)return;
	int siftValue(heapDataVec[siftIndex]);
	int childIndex = (siftIndex << 1) + 1;
	while (childIndex <= numCounts - 1) {
		if (childIndex + 1 <= numCounts - 1 && comp(heapDataVec[childIndex], heapDataVec[childIndex + 1]))++childIndex;//��ʾ�����ӽڵ���ֵ�ϴ���Ǹ�
		if (comp(siftValue, heapDataVec[childIndex]) == false) {
			heapDataVec[siftIndex] = siftValue;
			return;
		}//if
		heapDataVec[siftIndex] = heapDataVec[childIndex];//��ϴ�ֵΪ��ֵ  
		siftIndex = childIndex;//���ڵ���������  
		childIndex = (childIndex << 1) + 1;//���¼��㶴�ڵ����ӽڵ�  
	}//while
	heapDataVec[siftIndex] = siftValue;
	return;
}//siftDown

 //���ݲ���
template <typename ElemType, typename Storage, typename Compare>
void MyHeap<ElemType, Storage, Compare>::siftUp(int holeIndex) {
	//���½ڵ����丸�ڵ���бȽϣ������ֵ���丸�ڵ�󣬾͸��ӽ���λ�á�
	//��ˣ�֪������Ҫ�Ի���ֱ�����ڵ�Ϊֹ
	int tmp(heapDataVec[holeIndex]);
	int parentIndex = (holeIndex - 1) >> 1;
	while (holeIndex > StartIndex && comp(heapDataVec[parentIndex], tmp)) {
		heapDataVec[holeIndex] = heapDataVec[parentIndex];
		holeIndex = parentIndex;
		parentIndex = (parentIndex - 1) >> 1;
	}//while
	heapDataVec[holeIndex] = tmp;//����ֵ��������ȷ��λ��  
	return;
}//siftUp