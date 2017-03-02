#include<stdio.h>
#include<vector>
using std::vector;

bool check(const vector<int> &A_) {
	vector<int> A(A_);
	A.insert(A.begin(), 0);
	vector<long long> Sum;
	long long sum(0);
	int lenA = (int)A.size();
	for (int i(0); i < lenA; ++i) {
		sum += A[i];
		Sum.push_back(sum);
	}//for i
	int mid(1), right(lenA - 1);
	long long rSum(0), miSum1(0), miSum2(0);
	for (int left(1); left < lenA; ++left) {
		int lSum = Sum[left - 1];
		while (right > mid&&rSum < lSum) {
			--right;
			rSum = Sum[lenA - 1] - Sum[right];
		}//while
		while (mid < right&&miSum1 < lSum) {
			++mid;
			miSum1 = Sum[mid - 1] - Sum[left];
		}//while
		//while (mid<right&&miSum2>lSum) {
		//	//++mid;
		//	--right;
		//	miSum2 = Sum[right - 1] - Sum[mid];
		//}//while
		miSum2 = Sum[right - 1] - Sum[mid];
		if (lSum == miSum1 && miSum1 == miSum2 && miSum2 == rSum) {
			printf("%lld,%lld,%lld,%lld\n", lSum, miSum1, miSum2, rSum);
			return true;
		}//if
	}//for i
	return false;
}//check

int main() {
	//vector<int> nums{ 2,5,1,1,1,1,4,1,7,3,7 };
	//vector<int> nums{ 10, 2, 11, 13, 1, 1, 1, 1, 1 };
	vector<int> nums{ 0, 0, 0, 0, 1, 1, 1 };
	check(nums) ? puts("true") : puts("false");
	return 0;
}//main