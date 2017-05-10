#include"Heap.h"
#include <iostream>
using std::endl;
using std::cout;
#include<functional>
using std::greater;

template<typename ElemType>
struct cmp {
	bool operator()(const ElemType &x, const ElemType &y)const {
		return x < y;
	}//opearotr()
};

int main() {
	vector<int> data{ 0,1,2,3,4,8,9,3,5 };
	MyHeap<int> intHeapObj(data);
	//MyHeap<int,vector<int>,less<int> > intHeapObj(data);
	//MyHeap<int, vector<int>, greater<int> > intHeapObj(data);
	//MyHeap<int, vector<int> ,cmp<int> > intHeapObj(data);
	intHeapObj.printHeap();

	intHeapObj.makeHeap();
	intHeapObj.printHeap();

	intHeapObj.pushHeap(7);
	intHeapObj.printHeap();

	intHeapObj.popHeap();
	intHeapObj.printHeap();

	vector<int> nums = intHeapObj.sortHeap();
	int sizeOfNums = (int)nums.size();
	cout << "Sorted data :";
	for (int i(0); i < sizeOfNums - 1; ++i)cout << nums[i] << " ";
	if (sizeOfNums > 0)cout << nums[sizeOfNums - 1] << endl;
	return 0;
}//main
 /*less，自定义cmp<int>
 Heap : 9 5 8 3 4 0 2 1 3
 Heap : 9 5 8 3 4 0 2 1 3
 Heap : 9 7 8 3 5 0 2 1 3 4
 Heap : 8 7 4 3 5 0 2 1 3
 Sorted data :0 1 2 3 3 4 5 7 8
 Press any key to continue . . .
 */
 /*greater
 Heap: 0 1 2 3 4 8 9 3 5
 Heap : 0 1 2 3 4 8 9 3 5
 Heap : 0 1 2 3 4 8 9 3 5 7
 Heap : 1 3 2 3 4 8 9 7 5
 Sorted data : 9 8 7 5 4 3 3 2 1
 Press any key to continue . . .
 */
